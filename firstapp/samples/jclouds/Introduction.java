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
import com.google.common.base.Optional;
import com.google.common.collect.ImmutableSet;
import com.google.common.io.Closeables;
import com.google.inject.Module;
import org.jclouds.ContextBuilder;
import org.jclouds.logging.slf4j.config.SLF4JLoggingModule;
import org.jclouds.net.domain.IpProtocol;
import org.jclouds.openstack.nova.v2_0.NovaApi;
import org.jclouds.openstack.nova.v2_0.domain.*;
import org.jclouds.openstack.nova.v2_0.extensions.FloatingIPApi;
import org.jclouds.openstack.nova.v2_0.extensions.FloatingIPPoolApi;
import org.jclouds.openstack.nova.v2_0.extensions.SecurityGroupApi;
import org.jclouds.openstack.nova.v2_0.extensions.ServerWithSecurityGroupsApi;
import org.jclouds.openstack.nova.v2_0.features.ServerApi;
import org.jclouds.openstack.nova.v2_0.options.CreateServerOptions;
import org.jclouds.openstack.nova.v2_0.predicates.ServerPredicates;

import java.io.Closeable;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.stream.Collectors;

import static java.lang.System.out;

public class Introduction implements Closeable {


    private static final String PROVIDER = "openstack-nova";

    private static final String OS_AUTH_URL = "http://controller:5000/v2.0";
    // format for identity is tenantName:userName
    private static final String IDENTITY = "your_project_name_or_id:your_auth_username";
    private static final String IMAGE_ID = "2cccbea0-cea9-4f86-a3ed-065c652adda5";
    private static final String FLAVOR_ID = "2";

    private static final String ALL_IN_ONE_SECURITY_GROUP_NAME = "all-in-one";
    public static final String ALL_IN_ONE_INSTANCE_NAME = "all-in-one";

    private static final String WORKER_SECURITY_GROUP_NAME = "worker";
    private static final String CONTROLLER_SECURITY_GROUP_NAME = "control";

    private final NovaApi novaApi;
    private final String region;
    private final ServerApi serverApi;
    private final String ex_keypair = "demokey";

    public Introduction(final String password) {
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

    // step-3
    private Ingress getIngress(int port) {
        return Ingress
                .builder()
                .ipProtocol(IpProtocol.TCP)
                .fromPort(port)
                .toPort(port)
                .build();
    }

    private void createAllInOneSecurityGroup() {
        Optional<? extends SecurityGroupApi> optional = novaApi.getSecurityGroupApi(region);
        if (optional.isPresent()) {
            SecurityGroupApi securityGroupApi = optional.get();
            if (isSecurityGroup(ALL_IN_ONE_SECURITY_GROUP_NAME, securityGroupApi)) {
                out.println("Security Group " + ALL_IN_ONE_SECURITY_GROUP_NAME + " already exists");
            } else {
                out.println("Creating Security Group " + ALL_IN_ONE_SECURITY_GROUP_NAME + "...");
                SecurityGroup securityGroup =
                        securityGroupApi.createWithDescription(ALL_IN_ONE_SECURITY_GROUP_NAME,
                                "Network access for all-in-one application.");
                securityGroupApi.createRuleAllowingCidrBlock(
                        securityGroup.getId(), getIngress(22), "0.0.0.0/0");
                securityGroupApi.createRuleAllowingCidrBlock(
                        securityGroup.getId(), getIngress(80), "0.0.0.0/0");
            }
        } else {
            out.println("No Security Group extension present; skipping security group demo.");
        }
    }
    // step-3-end

    private SecurityGroup getSecurityGroup(String securityGroupName, SecurityGroupApi securityGroupApi) {
        for (SecurityGroup securityGroup : securityGroupApi.list()) {
            if (securityGroup.getName().equals(securityGroupName)) {
                return securityGroup;
            }
        }
        return null;
    }

    private boolean isSecurityGroup(String securityGroupName, SecurityGroupApi securityGroupApi) {
        return getSecurityGroup(securityGroupName, securityGroupApi) != null;
    }

    // step-4
    private void listAllSecurityGroups() {
        if (novaApi.getSecurityGroupApi(region).isPresent()) {
            SecurityGroupApi securityGroupApi = novaApi.getSecurityGroupApi(region).get();
            out.println("Existing Security Groups:");
            for (SecurityGroup securityGroup : securityGroupApi.list()) {
                out.println("  " + securityGroup.getName());
            }
        } else {
            out.println("No Security Group extension present; skipping listing of security groups.");
        }
    }
    // step-4-end

    // step-5
    private void deleteSecurityGroupRule(SecurityGroupRule rule) {
        if (novaApi.getSecurityGroupApi(region).isPresent()) {
            SecurityGroupApi securityGroupApi = novaApi.getSecurityGroupApi(region).get();
            out.println("Deleting Security Group Rule " + rule.getIpProtocol());
            securityGroupApi.deleteRule(rule.getId());
        } else {
            out.println("No Security Group extension present; can't delete Rule.");
        }
    }

    private void deleteSecurityGroup(SecurityGroup securityGroup) {
        if (novaApi.getSecurityGroupApi(region).isPresent()) {
            SecurityGroupApi securityGroupApi = novaApi.getSecurityGroupApi(region).get();
            out.println("Deleting Security Group " + securityGroup.getName());
            securityGroupApi.delete(securityGroup.getId());
        } else {
            out.println("No Security Group extension present; can't delete Security Group.");
        }
    }
    // step-5-end

    private void deleteSecurityGroups(String... groups) {
        if (novaApi.getSecurityGroupApi(region).isPresent()) {
            SecurityGroupApi securityGroupApi = novaApi.getSecurityGroupApi(region).get();
            securityGroupApi.list().forEach(securityGroup -> {
                if (Arrays.asList(groups).contains(securityGroup.getName())) {
                    deleteSecurityGroup(securityGroup);
                }
            });
        } else {
            out.println("No Security Group extension present; can't delete Security Groups.");
        }
    }

    private void deleteSecurityGroupRules(String securityGroupName) {
        if (novaApi.getSecurityGroupApi(region).isPresent()) {
            SecurityGroupApi securityGroupApi = novaApi.getSecurityGroupApi(region).get();
            for (SecurityGroup thisSecurityGroup : securityGroupApi.list()) {
                if (thisSecurityGroup.getName().equals(securityGroupName)) {
                    out.println("Deleting Rules for Security Group " + securityGroupName);
                    Set<SecurityGroupRule> rules = thisSecurityGroup.getRules();
                    if (rules != null) {
                        rules.forEach(this::deleteSecurityGroupRule);
                    }
                }
            }
        } else {
            out.println("No Security Group extension present; skipping deleting of Rules.");
        }
    }

    // step-2
    final String ex_userdata = "#!/usr/bin/env bash\n" +
            " curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh" +
            " | bash -s -- \\\n" +
            " -i faafo -i messaging -r api -r worker -r demo\n";
    // step-2-end

    // step-1

    /**
     * A helper function to create an instance
     *
     * @param name    The name of the instance that is to be created
     * @param options Keypairs, security groups etc...
     * @return the id of the newly created instance.
     */
    private String create_node(String name, CreateServerOptions... options) {
        out.println("Creating Instance " + name);
        ServerCreated serverCreated = serverApi.create(name, IMAGE_ID, FLAVOR_ID, options);
        String id = serverCreated.getId();
        ServerPredicates.awaitActive(serverApi).apply(id);
        return id;
    }


    private String createAllInOneInstance() {
        CreateServerOptions allInOneOptions = CreateServerOptions.Builder
                .keyPairName(ex_keyname)
                .securityGroupNames(ALL_IN_ONE_SECURITY_GROUP_NAME)
                .userData(ex_userdata.getBytes());
        return create_node(ALL_IN_ONE_INSTANCE_NAME, allInOneOptions);
    }
    // step-1-end

    // step-6
    private void listSecurityGroupsForServer(String serverId) {
        if (novaApi.getServerWithSecurityGroupsApi(region).isPresent()) {
            out.println("Listing Security Groups for Instance with id " + serverId);
            ServerWithSecurityGroupsApi serverWithSecurityGroupsApi =
                    novaApi.getServerWithSecurityGroupsApi(region).get();
            ServerWithSecurityGroups serverWithSecurityGroups =
                    serverWithSecurityGroupsApi.get(serverId);
            Set<String> securityGroupNames = serverWithSecurityGroups.getSecurityGroupNames();
            securityGroupNames.forEach(name -> out.println("   " + name));
        } else {
            out.println("No Server With Security Groups API found; can't list Security Groups for Instance.");
        }
    }
    // step-6-end

    private void deleteInstance(String instanceName) {
        serverApi.listInDetail().concat().forEach(instance -> {
            if (instance.getName().equals(instanceName)) {
                out.println("Deleting Instance: " + instance.getName());
                serverApi.delete(instance.getId());
                ServerPredicates.awaitStatus(serverApi, Server.Status.DELETED, 600, 5).apply(instance.getId());

            }
        });
    }

    // step-7
    private FloatingIP getFreeFloatingIp() {
        FloatingIP unusedFloatingIP = null;
        if (novaApi.getFloatingIPApi(region).isPresent()) {
            out.println("Checking for unused Floating IP's...");
            FloatingIPApi floatingIPApi = novaApi.getFloatingIPApi(region).get();
            List<FloatingIP> freeIP = floatingIPApi.list().toList().stream().filter(
                    floatingIp -> floatingIp.getInstanceId() == null).collect(Collectors.toList());
            if (freeIP.size() > 0) {
                unusedFloatingIP = freeIP.get(0);
            }
        } else {
            out.println("No Floating IP extension present; could not fetch Floating IP.");
        }
        return unusedFloatingIP;
    }
    // step-7-end

    // step-8
    private String getFirstFloatingIpPoolName() {
        String floatingIpPoolName = null;
        if (novaApi.getFloatingIPPoolApi(region).isPresent()) {
            out.println("Getting Floating IP Pool.");
            FloatingIPPoolApi poolApi = novaApi.getFloatingIPPoolApi(region).get();
            if (poolApi.list().first().isPresent()) {
                FloatingIPPool floatingIPPool = poolApi.list().first().get();
                floatingIpPoolName = floatingIPPool.getName();
            } else {
                out.println("There is no Floating IP Pool");
            }
        } else {
            out.println("No Floating IP Pool API present; could not fetch Pool.");
        }
        return floatingIpPoolName;
    }
    // step-8-end

    // step-9
    private FloatingIP allocateFloatingIpFromPool(String poolName) {
        FloatingIP unusedFloatingIP = null;
        if (novaApi.getFloatingIPApi(region).isPresent()) {
            out.println("Allocating IP from Pool " + poolName);
            FloatingIPApi floatingIPApi = novaApi.getFloatingIPApi(region).get();
            unusedFloatingIP = floatingIPApi.allocateFromPool(poolName);
        } else {
            out.println("No Floating IP extension present; could not allocate IP from Pool.");
        }
        return unusedFloatingIP;
    }
    // step-9-end

    // step-10
    private void attachFloatingIpToInstance(FloatingIP unusedFloatingIP, String targetInstanceId) {
        if (novaApi.getFloatingIPApi(region).isPresent()) {
            out.println("Attaching new IP, please wait...");
            FloatingIPApi floatingIPApi = novaApi.getFloatingIPApi(region).get();
            floatingIPApi.addToServer(unusedFloatingIP.getIp(), targetInstanceId);
        } else {
            out.println("No Floating IP extension present; cannot attach IP to Instance.");
        }
    }
    // step-10-end

    private void attachFloatingIp(String allInOneInstanceId) {
        FloatingIP freeFloatingIp = getFreeFloatingIp();
        if (freeFloatingIp == null) {
            String poolName = getFirstFloatingIpPoolName();
            if (poolName != null) {
                freeFloatingIp = allocateFloatingIpFromPool(poolName);
                if (freeFloatingIp != null) {
                    attachFloatingIpToInstance(freeFloatingIp, allInOneInstanceId);
                }
            }
        }
    }

    // step-11
    private void createApiAndWorkerSecurityGroups() {
        if (novaApi.getSecurityGroupApi(region).isPresent()) {
            SecurityGroupApi securityGroupApi = novaApi.getSecurityGroupApi(region).get();
            SecurityGroup workerGroup =
                    getSecurityGroup(WORKER_SECURITY_GROUP_NAME, securityGroupApi);
            if (workerGroup == null) {
                out.println("Creating Security Group " + WORKER_SECURITY_GROUP_NAME + "...");
                workerGroup = securityGroupApi.createWithDescription(WORKER_SECURITY_GROUP_NAME,
                        "For services that run on a worker node.");
                securityGroupApi.createRuleAllowingCidrBlock(
                        workerGroup.getId(), getIngress(22), "0.0.0.0/0");
            }
            SecurityGroup apiGroup =
                    getSecurityGroup(CONTROLLER_SECURITY_GROUP_NAME, securityGroupApi);
            if (apiGroup == null) {
                apiGroup = securityGroupApi.createWithDescription(CONTROLLER_SECURITY_GROUP_NAME,
                        "For services that run on a control node");
                securityGroupApi.createRuleAllowingCidrBlock(
                        apiGroup.getId(), getIngress(80), "0.0.0.0/0");
                securityGroupApi.createRuleAllowingCidrBlock(
                        apiGroup.getId(), getIngress(22), "0.0.0.0/0");
                securityGroupApi.createRuleAllowingSecurityGroupId(
                        apiGroup.getId(), getIngress(5672), workerGroup.getId());
            }
        } else {
            out.println("No Security Group extension present; skipping Security Group create.");
        }
    }

    private String createApiInstance() {
        String userData = "#!/usr/bin/env bash\n" +
                "curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh" +
                " | bash -s -- \\\n" +
                " -i messaging -i faafo -r api\n";
        String instanceName = "app-controller";
        CreateServerOptions allInOneOptions = CreateServerOptions.Builder
                .keyPairName(ex_keyname)
                .securityGroupNames(CONTROLLER_SECURITY_GROUP_NAME)
                .userData(userData.getBytes());
        return create_node(instanceName, allInOneOptions);
    }
    // step-11-end

    // step-12
    private String createWorkerInstance(String apiAccessIP) {
        String userData = "#!/usr/bin/env bash\n" +
                "curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh" +
                " | bash -s -- \\\n" +
                "   -i faafo -r worker -e 'http://%1$s' -m 'amqp://guest:guest@%1$s:5672/'";
        userData = String.format(userData, apiAccessIP);
        CreateServerOptions options = CreateServerOptions.Builder
                .keyPairName(ex_keyname)
                .securityGroupNames(WORKER_SECURITY_GROUP_NAME)
                .userData(userData.getBytes());
        return create_node("app-worker-1", options);
    }
    // step-12-end


    private void createApiAndWorkerInstances() {
        createApiAndWorkerSecurityGroups();
        String apiInstanceId = createApiInstance();
        attachFloatingIp(apiInstanceId);
        String apiAccessIP = serverApi.get(apiInstanceId).getAccessIPv4();
        out.println("Controller is deployed to http://" + apiAccessIP);
        String workerInstanceId = createWorkerInstance(apiAccessIP);
        attachFloatingIp(workerInstanceId);
        // step-13
        String workerAccessIP = serverApi.get(workerInstanceId).getAccessIPv4();
        out.println("Worker is deployed to " + workerAccessIP);
        // step-13-end
    }


    private void setupIntroduction() {
        createAllInOneSecurityGroup();
        String allInOneInstanceId = createAllInOneInstance();
        listAllSecurityGroups();
        listSecurityGroupsForServer(allInOneInstanceId);
        attachFloatingIp(allInOneInstanceId);
        deleteInstance(ALL_IN_ONE_INSTANCE_NAME);
        deleteSecurityGroupRules(ALL_IN_ONE_SECURITY_GROUP_NAME);
        deleteSecurityGroups(ALL_IN_ONE_SECURITY_GROUP_NAME);
        createApiAndWorkerInstances();
    }

    @Override
    public void close() throws IOException {
        Closeables.close(novaApi, true);
    }

    public static void main(String[] args) throws IOException {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.println("Please enter your password: ");
            String password = scanner.next();
            try (Introduction gs = new Introduction(password)) {
                gs.setupIntroduction();
            }
        }

    }
}
