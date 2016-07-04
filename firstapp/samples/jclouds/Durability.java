/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import com.google.common.collect.ImmutableMap;
import com.google.common.io.ByteSource;
import com.google.common.io.Closeables;
import com.google.common.io.Files;
import com.google.gson.Gson;
import org.jclouds.ContextBuilder;
import org.jclouds.blobstore.BlobStore;
import org.jclouds.blobstore.domain.Blob;
import org.jclouds.domain.Location;
import org.jclouds.io.Payload;
import org.jclouds.io.Payloads;
import org.jclouds.openstack.swift.v1.SwiftApi;
import org.jclouds.openstack.swift.v1.blobstore.RegionScopedBlobStoreContext;
import org.jclouds.openstack.swift.v1.domain.Container;
import org.jclouds.openstack.swift.v1.domain.SwiftObject;
import org.jclouds.openstack.swift.v1.features.ContainerApi;
import org.jclouds.openstack.swift.v1.features.ObjectApi;
import org.jclouds.openstack.swift.v1.options.CreateContainerOptions;
import org.jclouds.openstack.swift.v1.options.PutOptions;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.List;

import static com.google.common.collect.Iterables.getOnlyElement;
import static java.lang.System.out;
import static org.jclouds.io.Payloads.newFilePayload;
import static org.jclouds.io.Payloads.newInputStreamPayload;

public class Durability implements Closeable {

    // step-1
    private final SwiftApi swiftApi;
    private final String region;
    private static final String PROVIDER = "openstack-swift";

    private static final String OS_AUTH_URL = "http://controller:5000/v2.0/";
    // format for identity is projectName:userName
    private static final String IDENTITY = "your_project_name:your_auth_username";
    private static final String PASSWORD = "your_auth_password";


    public Durability() {
        swiftApi = ContextBuilder.newBuilder(PROVIDER)
                .endpoint(OS_AUTH_URL)
                .credentials(IDENTITY, PASSWORD)
                .buildApi(SwiftApi.class);
        region = swiftApi.getConfiguredRegions().iterator().next();
        out.println("Running in region: " + region);
    }

    // step-2
    private void createContainer(String containerName) {
        ContainerApi containerApi = swiftApi.getContainerApi(region);
        if (containerApi.create(containerName)) {
            out.println("Created container: " + containerName);
        } else {
            out.println("Container all ready exists: " + containerName);
        }
    }

    // step-3
    private void listContainers() {
        out.println("Containers:");
        ContainerApi containerApi = swiftApi.getContainerApi(region);
        containerApi.list().forEach(container -> out.println("  " + container));
    }

    // step-4
    private String uploadObject(String containerName, String objectName, String filePath) {
        Payload payload = newFilePayload(new File(filePath));
        ObjectApi objectApi = swiftApi.getObjectApi(region, containerName);
        String eTag = objectApi.put(objectName, payload);
        out.println(String.format("Uploaded %s as \"%s\" eTag = %s", filePath, objectName, eTag));
        return eTag;
    }

    // step-5
    private void listObjectsInContainer(String containerName) {
        out.println("Objects in " + containerName + ":");
        ObjectApi objectApi = swiftApi.getObjectApi(region, containerName);
        objectApi.list().forEach(object -> out.println("   " + object));
    }

    // step-6
    private SwiftObject getObjectFromContainer(String containerName, String objectName) {
        ObjectApi objectApi = swiftApi.getObjectApi(region, containerName);
        SwiftObject object = objectApi.get(objectName);
        out.println("Fetched: " + object.getName());
        return object;
    }

    // step-7
    private void calculateMd5ForFile(String filePath) {
        try (FileInputStream fis = new FileInputStream(new File(filePath))) {
            MessageDigest md5Digest = MessageDigest.getInstance("MD5");

            byte[] byteArray = new byte[1024];
            int bytesCount;
            while ((bytesCount = fis.read(byteArray)) != -1) {
                md5Digest.update(byteArray, 0, bytesCount);
            }
            byte[] digest = md5Digest.digest();

            // Convert decimal number to hex string
            StringBuilder sb = new StringBuilder();
            for (byte aByte : digest) {
                sb.append(Integer.toString((aByte & 0xff) + 0x100, 16).substring(1));
            }

            out.println("MD5 for file " + filePath + ": " + sb.toString());
        } catch (IOException | NoSuchAlgorithmException e) {
            out.println("Could not calculate md5: " + e.getMessage());
        }
    }

    // step-8
    private void deleteObject(String containerName, String objectName) {
        ObjectApi objectApi = swiftApi.getObjectApi(region, containerName);
        objectApi.delete(objectName);
        out.println("Deleted: " + objectName);
    }

    // step-10
    private Container getContainer(String containerName) {
        ContainerApi containerApi = swiftApi.getContainerApi(region);
        // ensure container exists
        containerApi.create(containerName);
        return containerApi.get(containerName);
    }

    // step-11
    static class Fractal {
        // only included elements we want to work with
        String uuid;
    }

    static class Fractals {
        // only included elements we want to work with
        List<Fractal> objects;
    }

    private void backupFractals(String containerName, String fractalsIp) {
        // just need to make sure that there is container
        getContainer(containerName);
        try {
            String response = "";
            String endpoint = "http://" + fractalsIp + "/v1/fractal";
            URLConnection connection = new URL(endpoint).openConnection();
            connection.setRequestProperty("'results_per_page", "-1");
            connection.getInputStream();
            try (BufferedReader in = new BufferedReader(new InputStreamReader(
                    connection.getInputStream()))) {
                String inputLine;
                while ((inputLine = in.readLine()) != null) {
                    response = response + inputLine;
                }
            }

            Gson gson = new Gson();
            Fractals fractals = gson.fromJson(response, Fractals.class);
            ObjectApi objectApi = swiftApi.getObjectApi(region, containerName);
            fractals.objects.forEach(fractal -> {
                try {
                    String fractalEndpoint = "http://" + fractalsIp + "/fractal/" + fractal.uuid;
                    URLConnection conn = new URL(fractalEndpoint).openConnection();
                    try (InputStream inputStream = conn.getInputStream()) {
                        Payload payload = newInputStreamPayload(inputStream);
                        String eTag = objectApi.put(fractal.uuid, payload);
                        out.println(String.format("Backed up %s eTag = %s", fractal.uuid, eTag));
                    }
                } catch (IOException e) {
                    out.println("Could not backup " + fractal.uuid + "! Cause: " + e.getMessage());
                }
            });
            out.println("Backed up:");
            objectApi.list().forEach(object -> out.println("   " + object));
        } catch (IOException e) {
            out.println("Could not backup fractals! Cause: " + e.getMessage());
        }
    }

    // step-12
    private boolean deleteContainer(String containerName) {
        ObjectApi objectApi = swiftApi.getObjectApi(region, containerName);
        objectApi.list().forEach(object -> objectApi.delete(object.getName()));
        ContainerApi containerApi = swiftApi.getContainerApi(region);
        return containerApi.deleteIfEmpty(containerName);
    }

    // step-13
    private void createWithMetadata(String containerName, String objectName, String filePath) {

        ContainerApi containerApi = swiftApi.getContainerApi(region);
        CreateContainerOptions options = CreateContainerOptions.Builder
                .metadata(ImmutableMap.of("photos", "of fractals"));

        if (containerApi.create(containerName, options)) {
            out.println("Uploading: " + objectName);

            ObjectApi objectApi = swiftApi.getObjectApi(region, containerName);
            Payload payload = newFilePayload(new File(filePath));
            PutOptions putOptions = PutOptions.Builder
                    .metadata(ImmutableMap.of(
                            "description", "a funny goat",
                            "created", "2015-06-02"));
            String eTag = objectApi.put(objectName, payload, putOptions);
            out.println(
                    String.format("Uploaded %s as \"%s\" eTag = %s", filePath, objectName, eTag));
        } else {
            out.println("Could not upload " + objectName);
        }
    }

    // step-14
    private void uploadLargeFile(String containerName, String pathNameOfLargeFile) {
        // Only works with jclouds V2 (in beta at the time of writing). See:
        // https://issues.apache.org/jira/browse/JCLOUDS-894
        try {
            RegionScopedBlobStoreContext context = ContextBuilder.newBuilder(PROVIDER)
                    .credentials(IDENTITY, PASSWORD)
                    .endpoint(OS_AUTH_URL)
                    .buildView(RegionScopedBlobStoreContext.class);
            String region = context.getConfiguredRegions().iterator().next();
            out.println("Running in region: " + region);
            BlobStore blobStore = context.getBlobStore(region);
            // create the container if it doesn't exist...
            Location location = getOnlyElement(blobStore.listAssignableLocations());
            blobStore.createContainerInLocation(location, containerName);
            File largeFile = new File(pathNameOfLargeFile);
            ByteSource source = Files.asByteSource(largeFile);
            Payload payload = Payloads.newByteSourcePayload(source);
            payload.getContentMetadata().setContentLength(largeFile.length());
            out.println("Uploading file. This may take some time!");
            Blob blob = blobStore.blobBuilder(largeFile.getName())
                    .payload(payload)
                    .build();
            org.jclouds.blobstore.options.PutOptions putOptions =
                    new org.jclouds.blobstore.options.PutOptions();

            String eTag = blobStore.putBlob(containerName, blob, putOptions.multipart());
            out.println(String.format("Uploaded %s eTag=%s", largeFile.getName(), eTag));
        } catch (UnsupportedOperationException e) {
            out.println("Sorry: large file uploads only work in jclouds V2...");
        }
    }

    // step-15
    @Override
    public void close() throws IOException {
        Closeables.close(swiftApi, true);
    }

    public static void main(String[] args) throws IOException {
        try (Durability tester = new Durability()) {
            String containerName = "fractals";
            String objectName = "an amazing goat";
            String goatImageFilePath = "goat.jpg";
            String fractalsIp = "IP_API_1";
            String pathNameOfLargeFile = "big.img";

            tester.createContainer(containerName);
            tester.listContainers();
            tester.uploadObject(containerName, objectName, goatImageFilePath);
            tester.listObjectsInContainer(containerName);
            tester.getObjectFromContainer(containerName, objectName);
            tester.calculateMd5ForFile(goatImageFilePath);
            tester.deleteObject(containerName, objectName);
            tester.getContainer(containerName);
            tester.backupFractals(containerName, fractalsIp);
            tester.deleteContainer(containerName);
            tester.createWithMetadata(containerName, objectName, goatImageFilePath);
            tester.listContainers();
            tester.uploadLargeFile("largeObject", pathNameOfLargeFile);
        }
    }
}
