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

import com.google.common.io.Closeables;
import org.jclouds.ContextBuilder;
import org.jclouds.net.domain.IpProtocol;
import org.jclouds.openstack.cinder.v1.CinderApi;
import org.jclouds.openstack.cinder.v1.domain.Snapshot;
import org.jclouds.openstack.cinder.v1.domain.Volume;
import org.jclouds.openstack.cinder.v1.features.SnapshotApi;
import org.jclouds.openstack.cinder.v1.features.VolumeApi;
import org.jclouds.openstack.cinder.v1.options.CreateSnapshotOptions;
import org.jclouds.openstack.cinder.v1.options.CreateVolumeOptions;
import org.jclouds.openstack.cinder.v1.predicates.SnapshotPredicates;
import org.jclouds.openstack.cinder.v1.predicates.VolumePredicates;
import org.jclouds.openstack.nova.v2_0.NovaApi;
import org.jclouds.openstack.nova.v2_0.domain.Ingress;
import org.jclouds.openstack.nova.v2_0.domain.SecurityGroup;
import org.jclouds.openstack.nova.v2_0.domain.ServerCreated;
import org.jclouds.openstack.nova.v2_0.extensions.SecurityGroupApi;
import org.jclouds.openstack.nova.v2_0.features.ServerApi;
import org.jclouds.openstack.nova.v2_0.options.CreateServerOptions;
import org.jclouds.openstack.nova.v2_0.predicates.ServerPredicates;

import java.io.Closeable;
import java.io.IOException;
import java.util.Optional;
import java.util.Scanner;
import java.util.concurrent.TimeoutException;

import static java.lang.System.out;


public class BlockStorage implements Closeable {

    // Set the following to match the values for your cloud
    private static final String IDENTITY = "your_project_name:your_auth_username"; // note: projectName:userName
    private static final String KEY_PAIR_NAME = "your_key_pair_name";
    private static final String AUTH_URL = "http://controller:5000";
    private static final String AVAILABILITY_ZONE = "your_availability_zone";
    private static final String IMAGE_ID = "your_desired_image_id";
    private static final String FLAVOR_ID = "your_desired_flavor_id";

    private static final String DATABASE_SECURITY_GROUP_NAME = "database";

    private final CinderApi cinderApi;
    private final VolumeApi volumeApi;
    private final NovaApi novaApi;
    private final ServerApi serverApi;
    private final String region;

    // step-1
    public BlockStorage(final String password) {
        cinderApi = ContextBuilder.newBuilder("openstack-cinder")
                .endpoint(AUTH_URL)
                .credentials(IDENTITY, password)
                .buildApi(CinderApi.class);
        region = cinderApi.getConfiguredRegions().iterator().next();
        out.println("Running in region: " + region);
        volumeApi = cinderApi.getVolumeApi(region);
        novaApi = ContextBuilder.newBuilder("openstack-nova")
                .endpoint(AUTH_URL)
                .credentials(IDENTITY, password)
                .buildApi(NovaApi.class);
        serverApi = novaApi.getServerApi(region);
    }

    // step-2
    private Volume createVolume() throws TimeoutException {
        String volumeName = "Test";
        CreateVolumeOptions options = CreateVolumeOptions.Builder
                .name(volumeName)
                .availabilityZone(AVAILABILITY_ZONE);
        out.println("Creating 1 Gig volume named '" + volumeName + "'");
        Volume volume = volumeApi.create(1, options);
        // Wait for the volume to become available
        if (!VolumePredicates.awaitAvailable(volumeApi).apply(volume)) {
            throw new TimeoutException("Timeout on volume create");
        }
        return volume;
    }

    // step-3
    private void listVolumes() {
        out.println("Listing volumes");
        cinderApi.getConfiguredRegions().forEach((region) -> {
            out.println("  In region: " + region);
            cinderApi.getVolumeApi(region).list().forEach((volume) -> {
                out.println("    " + volume.getName());
            });
        });
    }

    // step-4
    private boolean isSecurityGroup(String securityGroupName, SecurityGroupApi securityGroupApi) {
        for (SecurityGroup securityGroup : securityGroupApi.list()) {
            if (securityGroup.getName().equals(securityGroupName)) {
                return true;
            }
        }
        return false;
    }

    // A utility method to convert a google optional into a Java 8 optional
    private <T> Optional<T> optional(com.google.common.base.Optional<T> target) {
        return target.isPresent() ? Optional.of(target.get()) : Optional.empty();
    }

    private void createSecurityGroup(String securityGroupName) {
        optional(novaApi.getSecurityGroupApi(region)).ifPresent(securityGroupApi -> {
            if (isSecurityGroup(securityGroupName, securityGroupApi)) {
                out.println("Security group " + securityGroupName + " already exists");
            } else {
                out.println("Creating security group " + securityGroupName + "...");
                SecurityGroup securityGroup =
                        securityGroupApi.createWithDescription(securityGroupName,
                                "For database service");
                securityGroupApi.createRuleAllowingCidrBlock(
                        securityGroup.getId(), Ingress
                                .builder()
                                .ipProtocol(IpProtocol.TCP)
                                .fromPort(3306)
                                .toPort(3306)
                                .build(), "0.0.0.0/0");
            }
        });
    }

    private String createDbInstance() throws TimeoutException {
        String instanceName = "app-database";
        out.println("Creating instance " + instanceName);
        CreateServerOptions allInOneOptions = CreateServerOptions.Builder
                .keyPairName(KEY_PAIR_NAME)
                .availabilityZone(AVAILABILITY_ZONE)
                .securityGroupNames(DATABASE_SECURITY_GROUP_NAME);
        ServerCreated server = serverApi.create(instanceName, IMAGE_ID, FLAVOR_ID, allInOneOptions);
        String id = server.getId();
        // Wait for the server to become available
        if (!ServerPredicates.awaitActive(serverApi).apply(id)) {
            throw new TimeoutException("Timeout on server create");
        }
        return id;
    }

    // step-5
    private void attachVolume(Volume volume, String instanceId) throws TimeoutException {
        out.format("Attaching volume %s to instance %s%n", volume.getId(), instanceId);
        optional(novaApi.getVolumeAttachmentApi(region)).ifPresent(volumeAttachmentApi -> {
                    volumeAttachmentApi.attachVolumeToServerAsDevice(volume.getId(), instanceId, "/dev/vdb");
                }
        );
        // Wait for the volume to be attached
        if (!VolumePredicates.awaitInUse(volumeApi).apply(volume)) {
            throw new TimeoutException("Timeout on volume attach");
        }
    }

    // step-6
    private void detachVolume(Volume volume, String instanceId) throws TimeoutException {
        out.format("Detach volume %s from instance %s%n", volume.getId(), instanceId);
        optional(novaApi.getVolumeAttachmentApi(region)).ifPresent(volumeAttachmentApi -> {
            volumeAttachmentApi.detachVolumeFromServer(volume.getId(), instanceId);
        });
        // Wait for the volume to be detached
        if (!VolumePredicates.awaitAvailable(volumeApi).apply(Volume.forId(volume.getId()))) {
            throw new TimeoutException("Timeout on volume detach");
        }
    }

    private void destroyVolume(Volume volume) throws TimeoutException {
        out.println("Destroy volume " + volume.getName());
        volumeApi.delete(volume.getId());
        // Wait for the volume to be deleted
        if (!VolumePredicates.awaitDeleted(volumeApi).apply(volume)) {
            throw new TimeoutException("Timeout on volume delete");
        }
    }

    // step-7
    private Snapshot createVolumeSnapshot(Volume volume) throws TimeoutException {
        out.println("Create snapshot of volume " + volume.getName());
        SnapshotApi snapshotApi = cinderApi.getSnapshotApi(region);
        CreateSnapshotOptions options = CreateSnapshotOptions.Builder
                .name(volume.getName() + " snapshot")
                .description("Snapshot of " + volume.getId());
        Snapshot snapshot = snapshotApi.create(volume.getId(), options);
        // Wait for the snapshot to become available
        if (!SnapshotPredicates.awaitAvailable(snapshotApi).apply(snapshot)) {
            throw new TimeoutException("Timeout on volume snapshot");
        }
        return snapshot;
    }

    private void deleteVolumeSnapshot(Snapshot snapshot) throws TimeoutException {
        out.println("Delete volume snapshot " + snapshot.getName());
        SnapshotApi snapshotApi = cinderApi.getSnapshotApi(region);
        snapshotApi.delete(snapshot.getId());
        // Wait for the snapshot to be deleted
        if (!SnapshotPredicates.awaitDeleted(snapshotApi).apply(snapshot)) {
            throw new TimeoutException("Timeout on snapshot delete");
        }
    }
    // step-8

    @Override
    public void close() throws IOException {
        Closeables.close(novaApi, true);
        Closeables.close(cinderApi, true);
    }

    public static void main(String... args) throws TimeoutException, IOException {
        try (Scanner scanner = new Scanner(System.in, "UTF-8")) {
            out.println("Please enter your API password: ");
            String password = scanner.next();
            try (BlockStorage storage = new BlockStorage(password)) {
                Volume volume = storage.createVolume();
                storage.listVolumes();
                storage.createSecurityGroup(DATABASE_SECURITY_GROUP_NAME);
                String dbInstanceId = storage.createDbInstance();
                storage.attachVolume(volume, dbInstanceId);
                storage.detachVolume(volume, dbInstanceId);
                Snapshot snapshot = storage.createVolumeSnapshot(volume);
                // have to delete the snapshot before we can delete the volume...
                storage.deleteVolumeSnapshot(snapshot);
                storage.destroyVolume(volume);
            }
        }
    }
}
