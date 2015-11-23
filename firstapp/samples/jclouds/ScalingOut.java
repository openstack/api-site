import com.google.common.collect.ImmutableSet;
import com.google.common.io.Closeables;
import com.google.inject.Module;
import org.jclouds.ContextBuilder;
import org.jclouds.logging.slf4j.config.SLF4JLoggingModule;
import org.jclouds.net.domain.IpProtocol;
import org.jclouds.openstack.nova.v2_0.NovaApi;
import org.jclouds.openstack.nova.v2_0.domain.FloatingIP;
import org.jclouds.openstack.nova.v2_0.domain.Ingress;
import org.jclouds.openstack.nova.v2_0.domain.SecurityGroup;
import org.jclouds.openstack.nova.v2_0.domain.ServerCreated;
import org.jclouds.openstack.nova.v2_0.extensions.FloatingIPApi;
import org.jclouds.openstack.nova.v2_0.extensions.SecurityGroupApi;
import org.jclouds.openstack.nova.v2_0.features.ServerApi;
import org.jclouds.openstack.nova.v2_0.options.CreateServerOptions;
import org.jclouds.openstack.nova.v2_0.predicates.ServerPredicates;

import java.io.Closeable;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.Scanner;
import java.util.stream.Collectors;

import static java.lang.System.out;

/**
 * A class that shows the jclouds implementation for the scaling out chapter of the
 * "Writing your first OpenStack application" book
 * (http://developer.openstack.org/firstapp-libcloud/scaling_out.html)
 */
public class ScalingOut implements Closeable {


    private final NovaApi novaApi;
    private final String region;
    private final ServerApi serverApi;

    // change the following to fit your OpenStack installation
    private static final String KEY_PAIR_NAME = "demokey";
    private static final String PROVIDER = "openstack-nova";
    private static final String OS_AUTH_URL = "http://controller:5000/v2.0";
    // format for identity is tenantName:userName
    private static final String IDENTITY = "your_project_name_or_id:your_auth_username";
    private static final String IMAGE_ID = "2cccbea0-cea9-4f86-a3ed-065c652adda5";
    private static final String FLAVOR_ID = "2";

    public ScalingOut(final String password) {
        Iterable<Module> modules = ImmutableSet.<Module>of(new SLF4JLoggingModule());
        novaApi = ContextBuilder.newBuilder(PROVIDER)
                .endpoint(OS_AUTH_URL)
                .credentials(IDENTITY, password)
                .modules(modules)
                .buildApi(NovaApi.class);
        region = novaApi.getConfiguredRegions().iterator().next();
        serverApi = novaApi.getServerApi(region);
        out.println("Running in region: " + region);
    }

// step-1

    private void deleteInstances() {
        List instances = Arrays.asList(
                "all-in-one", "app-worker-1", "app-worker-2", "app-controller");
        serverApi.listInDetail().concat().forEach(instance -> {
            if (instances.contains(instance.getName())) {
                out.println("Destroying Instance: " + instance.getName());
                serverApi.delete(instance.getId());
            }
        });
    }

    private void deleteSecurityGroups() {
        List securityGroups = Arrays.asList(
                "all-in-one", "control", "worker", "api", "services");
        if (novaApi.getSecurityGroupApi(region).isPresent()) {
            SecurityGroupApi securityGroupApi = novaApi.getSecurityGroupApi(region).get();
            securityGroupApi.list().forEach(securityGroup -> {
                if (securityGroups.contains(securityGroup.getName())) {
                    out.println("Deleting Security Group: " + securityGroup.getName());
                    securityGroupApi.delete(securityGroup.getId());
                }
            });
        } else {
            out.println("No security group extension present; skipping security group delete.");
        }
    }

// step-2

    private Ingress getIngress(int port) {
        return Ingress
                .builder()
                .ipProtocol(IpProtocol.TCP)
                .fromPort(port)
                .toPort(port)
                .build();
    }

    private void createSecurityGroups() {
        if (novaApi.getSecurityGroupApi(region).isPresent()) {
            SecurityGroupApi securityGroupApi = novaApi.getSecurityGroupApi(region).get();
            SecurityGroup apiGroup = securityGroupApi.createWithDescription("api",
                    "for API services only");
            ImmutableSet.of(22, 80).forEach(port ->
                    securityGroupApi.createRuleAllowingCidrBlock(
                            apiGroup.getId(), getIngress(port), "0.0.0.0/0"));

            SecurityGroup workerGroup = securityGroupApi.createWithDescription("worker",
                    "for services that run on a worker node");
            securityGroupApi.createRuleAllowingCidrBlock(
                    workerGroup.getId(), getIngress(22), "0.0.0.0/0");

            SecurityGroup controllerGroup = securityGroupApi.createWithDescription("control",
                    "for services that run on a control node");
            ImmutableSet.of(22, 80).forEach(port ->
                    securityGroupApi.createRuleAllowingCidrBlock(
                            controllerGroup.getId(), getIngress(port), "0.0.0.0/0"));
            securityGroupApi.createRuleAllowingSecurityGroupId(
                    controllerGroup.getId(), getIngress(5672), workerGroup.getId());

            SecurityGroup servicesGroup = securityGroupApi.createWithDescription("services",
                    "for DB and AMQP services only");
            securityGroupApi.createRuleAllowingCidrBlock(
                    servicesGroup.getId(), getIngress(22), "0.0.0.0/0");
            securityGroupApi.createRuleAllowingSecurityGroupId(
                    servicesGroup.getId(), getIngress(3306), apiGroup.getId());
            securityGroupApi.createRuleAllowingSecurityGroupId(
                    servicesGroup.getId(), getIngress(5672), workerGroup.getId());
            securityGroupApi.createRuleAllowingSecurityGroupId(
                    servicesGroup.getId(), getIngress(5672), apiGroup.getId());
        } else {
            out.println("No security group extension present; skipping security group create.");
        }
    }

// step-3

    private Optional<FloatingIP> getOrCreateFloatingIP() {
        FloatingIP unusedFloatingIP = null;
        if (novaApi.getFloatingIPApi(region).isPresent()) {
            FloatingIPApi floatingIPApi = novaApi.getFloatingIPApi(region).get();
            List<FloatingIP> freeIP = floatingIPApi.list().toList().stream()
                    .filter(floatingIP1 -> floatingIP1.getInstanceId() == null)
                    .collect(Collectors.toList());
            unusedFloatingIP = freeIP.size() > 0 ? freeIP.get(0) : floatingIPApi.create();
        } else {
            out.println("No floating ip extension present; skipping floating ip creation.");
        }
        return Optional.ofNullable(unusedFloatingIP);
    }

// step-4

    /**
     * A helper function to create an instance
     *
     * @param name    The name of the instance that is to be created
     * @param options Keypairs, security groups etc...
     * @return the id of the newly created instance.
     */
    private String createInstance(String name, CreateServerOptions... options) {
        out.println("Creating server " + name);
        ServerCreated serverCreated = serverApi.create(name, IMAGE_ID, FLAVOR_ID, options);
        String id = serverCreated.getId();
        ServerPredicates.awaitActive(serverApi).apply(id);
        return id;
    }

    /**
     * @return the id of the newly created instance.
     */
    private String createAppServicesInstance() {
        String userData = "#!/usr/bin/env bash\n" +
                "curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \\\n" +
                "-i database -i messaging\n";
        CreateServerOptions options = CreateServerOptions.Builder
                .keyPairName(KEY_PAIR_NAME)
                .securityGroupNames("services")
                .userData(userData.getBytes());
        return createInstance("app-services", options);
    }

// step-5

    /**
     * @return the id of the newly created instance.
     */
    private String createApiInstance(String name, String servicesIp) {
        String userData = String.format("#!/usr/bin/env bash\n" +
                "curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \\\n" +
                "    -i faafo -r api -m 'amqp://guest:guest@%1$s:5672/' \\\n" +
                "    -d 'mysql+pymysql://faafo:password@%1$s:3306/faafo'", servicesIp);
        CreateServerOptions options = CreateServerOptions.Builder
                .keyPairName(KEY_PAIR_NAME)
                .securityGroupNames("api")
                .userData(userData.getBytes());
        return createInstance(name, options);
    }

    /**
     * @return the id's of the newly created instances.
     */
    private String[] createApiInstances(String servicesIp) {
        return new String[]{
                createApiInstance("app-api-1", servicesIp),
                createApiInstance("app-api-2", servicesIp)
        };
    }

// step-6

    /**
     * @return the id of the newly created instance.
     */
    private String createWorkerInstance(String name, String apiIp, String servicesIp) {
        String userData = String.format("#!/usr/bin/env bash\n" +
                "curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \\\n" +
                "    -i faafo -r worker -e 'http://%s' -m 'amqp://guest:guest@%s:5672/'",
                apiIp, servicesIp);
        CreateServerOptions options = CreateServerOptions.Builder
                .keyPairName(KEY_PAIR_NAME)
                .securityGroupNames("worker")
                .userData(userData.getBytes());
        return createInstance(name, options);
    }

    private void createWorkerInstances(String apiIp, String servicesIp) {
        createWorkerInstance("app-worker-1", apiIp, servicesIp);
        createWorkerInstance("app-worker-2", apiIp, servicesIp);
        createWorkerInstance("app-worker-3", apiIp, servicesIp);
    }

// step-7

    private String getPublicIp(String serverId) {
        String publicIP = serverApi.get(serverId).getAccessIPv4();
        if (publicIP == null) {
            Optional<FloatingIP> optionalFloatingIP = getOrCreateFloatingIP();
            if (optionalFloatingIP.isPresent()) {
                publicIP = optionalFloatingIP.get().getIp();
                novaApi.getFloatingIPApi(region).get().addToServer(publicIP, serverId);
            }
        }
        return publicIP;
    }

    private String getPublicOrPrivateIP(String serverId) {
        String result = serverApi.get(serverId).getAccessIPv4();
        if (result == null) {
            // then there must be private one...
            result = serverApi.get(serverId).getAddresses().values().iterator().next().getAddr();
        }
        return result;
    }

    private void setupFaafo() {
        deleteInstances();
        deleteSecurityGroups();
        createSecurityGroups();
        String serviceId = createAppServicesInstance();
        String servicesIp = getPublicOrPrivateIP(serviceId);
        String[] apiIds = createApiInstances(servicesIp);
        String apiIp = getPublicIp(apiIds[0]);
        createWorkerInstances(apiIp, servicesIp);
        out.println("The Fractals app will be deployed to http://" + apiIp);
    }

    @Override
    public void close() throws IOException {
        Closeables.close(novaApi, true);
    }

    public static void main(String... args) throws IOException {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.println("Please enter your password: ");
            String password = scanner.next();
            try (ScalingOut gs = new ScalingOut(password)) {
                gs.setupFaafo();
            }
        }
    }
}
