import com.google.common.base.Optional;
import org.jclouds.ContextBuilder;
import org.jclouds.net.domain.IpProtocol;
import org.jclouds.openstack.nova.v2_0.NovaApi;
import org.jclouds.openstack.nova.v2_0.domain.*;
import org.jclouds.openstack.nova.v2_0.extensions.FloatingIPApi;
import org.jclouds.openstack.nova.v2_0.extensions.KeyPairApi;
import org.jclouds.openstack.nova.v2_0.extensions.SecurityGroupApi;
import org.jclouds.openstack.nova.v2_0.features.FlavorApi;
import org.jclouds.openstack.nova.v2_0.features.ImageApi;
import org.jclouds.openstack.nova.v2_0.features.ServerApi;
import org.jclouds.openstack.nova.v2_0.options.CreateServerOptions;
import org.jclouds.openstack.nova.v2_0.predicates.ServerPredicates;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

import static java.lang.System.out;


class GettingStarted {

    public static void main(String[] args) throws IOException {
        out.println("=============================");

// # step-1

        String provider = "openstack-nova";
        String identity = "your_project_name_or_id:your_auth_username";
        // NB: Do not check this file into source control with a real password in it!
        String credential = "your_auth_password";
        String authUrl = "http://controller:5000/v2.0/";

        NovaApi conn = ContextBuilder.newBuilder(provider)
                .endpoint(authUrl)
                .credentials(identity, credential)
                .buildApi(NovaApi.class);
        String region = conn.getConfiguredRegions().iterator().next();
        out.println("Running in region: " + region);

// # step-2

        ImageApi imageApi = conn.getImageApi(region);
        out.println("Images in region:");
        imageApi.list().concat().forEach(image -> out.println("  " + image.getName()));

// # step-3

        FlavorApi flavorApi = conn.getFlavorApi(region);
        out.println("Flavors in region:");
        flavorApi.list().concat().forEach(flavor -> out.println("  " + flavor.getName()));

// # step-4

        String imageId = "778e7b2e-4e67-44eb-9565-9c920e236dfd";
        Image retrievedImage = conn.getImageApi(region).get(imageId);
        out.println(retrievedImage.toString());

// # step-5

        String flavorId = "639b8b2a-a5a6-4aa2-8592-ca765ee7af63";
        Flavor flavor = conn.getFlavorApi(region).get(flavorId);
        out.println(flavor.toString());

// # step-6

        String testingInstance = "testingInstance";
        ServerCreated testInstance = conn.getServerApi(region).create(testingInstance, imageId, flavorId);
        out.println("Server created. ID: " + testInstance.getId());

// # step-7

        ServerApi serverApi = conn.getServerApi(region);
        out.println("Instances in region:");
        serverApi.list().concat().forEach(instance -> out.println("  " + instance));

// # step-8

        if (serverApi.delete(testInstance.getId())) {
            out.println("Server " + testInstance.getId() + " being deleted, please wait.");
            ServerPredicates.awaitStatus(serverApi, Server.Status.DELETED, 600, 5).apply(testInstance.getId());
            serverApi.list().concat().forEach(instance -> out.println("  " + instance));
        } else {
            out.println("Server not deleted.");
        }

// # step-9

        String pub_key_file = "id_rsa";
        String privateKeyFile = "~/.ssh/" + pub_key_file;

        Optional<? extends KeyPairApi> keyPairApiExtension = conn.getKeyPairApi(region);
        if (keyPairApiExtension.isPresent()) {
            out.println("Checking for existing SSH keypair...");
            KeyPairApi keyPairApi = keyPairApiExtension.get();
            boolean keyPairFound = keyPairApi.get(pub_key_file) != null;
            if (keyPairFound) {
                out.println("Keypair " + pub_key_file + " already exists.");
            } else {
                out.println("Creating keypair.");
                KeyPair keyPair = keyPairApi.create(pub_key_file);
                try {
                    Files.write(Paths.get(privateKeyFile), keyPair.getPrivateKey().getBytes());
                    out.println("Wrote " + privateKeyFile + ".");
                    // set file permissions to 600
                    Set<PosixFilePermission> permissions = new HashSet<>();
                    permissions.add(PosixFilePermission.OWNER_READ);
                    permissions.add(PosixFilePermission.OWNER_WRITE);
                    Files.setPosixFilePermissions(Paths.get(privateKeyFile), permissions);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            out.println("Existing keypairs:");
            keyPairApi.list().forEach(keyPair -> out.println("  " + keyPair));
        } else {
            out.println("No keypair extension present; skipping keypair checks.");
        }

// # step-10

        String securityGroupName = "all-in-one";

        Optional<? extends SecurityGroupApi> securityGroupApiExtension = conn.getSecurityGroupApi(region);
        if (securityGroupApiExtension.isPresent()) {
            out.println("Checking security groups.");

            SecurityGroupApi securityGroupApi = securityGroupApiExtension.get();
            boolean securityGroupFound = false;
            for (SecurityGroup securityGroup : securityGroupApi.list()) {
                securityGroupFound = securityGroupFound || securityGroup.getName().equals(securityGroupName);
            }
            if (securityGroupFound) {
                out.println("Security group " + securityGroupName + " already exists.");
            } else {
                out.println("Creating " + securityGroupName + "...");

                SecurityGroup securityGroup = securityGroupApi.createWithDescription(securityGroupName,
                        securityGroupName + " network access for all-in-one application.");

                Ingress sshIngress = Ingress.builder().fromPort(22).ipProtocol(IpProtocol.TCP).toPort(22).build();
                Ingress webIngress = Ingress.builder().fromPort(80).ipProtocol(IpProtocol.TCP).toPort(80).build();
                securityGroupApi.createRuleAllowingCidrBlock(securityGroup.getId(), sshIngress, "0.0.0.0/0");
                securityGroupApi.createRuleAllowingCidrBlock(securityGroup.getId(), webIngress, "0.0.0.0/0");
            }
            out.println("Existing Security Groups: ");
            for (SecurityGroup thisSecurityGroup : securityGroupApi.list()) {
                out.println("  " + thisSecurityGroup);
                thisSecurityGroup.getRules().forEach(rule -> out.println("    " + rule));
            }
        } else {
            out.println("No security group extension present; skipping security group checks.");
        }

// # step-11

        String ex_userdata = "#!/usr/bin/env bash\n" +
                " curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \\\n" +
                "         -i faafo -i messaging -r api -r worker -r demo\n";

// # step-12

        out.println("Checking for existing instance...");
        String instanceName = "all-in-one";
        Server allInOneInstance = null;

        for (Server thisInstance : serverApi.listInDetail().concat()) {
            if (thisInstance.getName().equals(instanceName)) {
                allInOneInstance = thisInstance;
            }
        }

        if (allInOneInstance != null) {
            out.println("Instance " + instanceName + " already exists. Skipping creation.");
        } else {
            out.println("Creating instance...");
            CreateServerOptions allInOneOptions = CreateServerOptions.Builder
                    .keyPairName(pub_key_file)
                    .securityGroupNames(securityGroupName)
                    // If not running in a single-tenant network this where you add your network...
                    // .networks("79e8f822-99e1-436f-a62c-66e8d3706940")
                    .userData(ex_userdata.getBytes());
            ServerCreated allInOneInstanceCreated = serverApi.create(instanceName, imageId, flavorId, allInOneOptions);
            ServerPredicates.awaitActive(serverApi).apply(allInOneInstanceCreated.getId());
            allInOneInstance = serverApi.get(allInOneInstanceCreated.getId());
            out.println("Instance created: " + allInOneInstance.getId());
        }
        out.println("Existing instances:");
        serverApi.listInDetail().concat().forEach(instance -> out.println("  " + instance.getName()));

// # step-13

        out.println("Checking for unused floating IP's...");
        FloatingIP unusedFloatingIP = null;
        if (conn.getFloatingIPApi(region).isPresent()) {
            FloatingIPApi floatingIPApi = conn.getFloatingIPApi(region).get();

            List<FloatingIP> freeIP = floatingIPApi.list().toList().stream().filter(
                    floatingIp -> floatingIp.getInstanceId() == null).collect(Collectors.toList());

            if (freeIP.size() > 0) {
                out.println("The following IPs are available:");
                freeIP.forEach(floatingIP -> out.println("  " + floatingIP.getIp()));
                unusedFloatingIP = freeIP.get(0);
            } else {
                out.println("Creating new floating IP.... ");
                unusedFloatingIP = floatingIPApi.create();
            }
            if (unusedFloatingIP != null) {
                out.println("Using: " + unusedFloatingIP.getIp());
            }
        } else {
            out.println("No floating ip extension present; skipping floating ip creation.");
        }

// # step-14

        out.println(allInOneInstance.getAddresses());
        if (allInOneInstance.getAccessIPv4() != null) {
            out.println("Public IP already assigned. Skipping attachment.");
        } else if (unusedFloatingIP != null) {
            out.println("Attaching new IP, please wait...");
            // api must be present if we have managed to allocate a floating IP
            conn.getFloatingIPApi(region).get().addToServer(unusedFloatingIP.getIp(), allInOneInstance.getId());
            //This operation takes some indeterminate amount of time; don't move on until it's done.
            while (allInOneInstance.getAccessIPv4() != null) {
                //Objects are not updated "live" so keep checking to make sure it's been added
                try {
                    TimeUnit.SECONDS.sleep(1);
                } catch(InterruptedException ex) {
                    out.println( "Awakened prematurely." );
                }
                allInOneInstance = serverApi.get(allInOneInstance.getId());
            }
        }

// # step-15

        out.print("Be patient: all going well, the Fractals app will soon be available at http://" + allInOneInstance.getAccessIPv4());

// # step-16
    }
}