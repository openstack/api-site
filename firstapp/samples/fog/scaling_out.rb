# step-1
for instance in conn.servers
    if ['all-in-one','app-worker-1', 'app-worker-2', 'app-controller'].include?(instance.name)
        puts 'Destroying Instance: %s' % instance.name
        conn.delete_server(instance.id)
    end
end

for group in conn.list_security_groups.body["security_groups"]
    if ['control', 'worker', 'api', 'services'].include?(group["name"])
        puts 'Deleting security group: %s' % group['name']
        conn.delete_security_group(group['id'])
    end
end

# step-2
api_group_response = conn.create_security_group('api', 'for API services only')
api_group = api_group_response.body["security_group"]
conn.create_security_group_rule(api_group["id"], 'TCP', '80', '80', '0.0.0.0/0')
conn.create_security_group_rule(api_group["id"], 'TCP',  '22', '22', '0.0.0.0/0')

worker_group_response = conn.create_security_group('worker', 'for services that run on a worker node')
worker_group = worker_group_response.body["security_group"]
conn.create_security_group_rule(worker_group["id"], 'TCP',  '22', '22', '0.0.0.0/0')

services_group_response = conn.create_security_group('services', 'for DB and AMQP services only')
services_group = services_group_response.body["security_group"]
conn.create_security_group_rule(services_group["id"], 'TCP', '80', '80', '0.0.0.0/0')
conn.create_security_group_rule(services_group["id"], 'TCP',  '22', '22', '0.0.0.0/0')
conn.create_security_group_rule(services_group["id"], 'TCP',  '3306', '3306', '0.0.0.0/0', api_group["id"])
conn.create_security_group_rule(services_group["id"], 'TCP',  '5672', '5672', '0.0.0.0/0', worker_group["id"])
conn.create_security_group_rule(services_group["id"], 'TCP',  '5672', '5672', '0.0.0.0/0', api_group["id"])

# step-3
def get_floating_ip (conn)
    '''A helper function to re-use available Floating IPs'''
    unused_floating_ip = nil
    for floating_ip in conn.list_all_addresses.body["floating_ips"]
        if not floating_ip["instance_id"]
            unused_floating_ip = floating_ip
            break
        end
    end
    if not unused_floating_ip
        pool = conn.list_address_pools.body["floating_ip_pools"][0]
        puts 'Allocating new Floating IP from pool: {}'. pool
        unused_floating_ip = conn.allocate_address(pool)
    end
    return unused_floating_ip
end

# step-4
userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i database -i messaging
'''

instance_services= conn.servers.create(:name => 'app-services', :flavor_ref => flavor.id, :image_ref => image.id, :key_name => 'demokey', :user_data => userdata, :security_groups => [services_group["name"]])

instance_services.wait_for { ready? }
services_ip = instance_services.accessIPv4


# step-5
userdata = "#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r api -m 'amqp://guest:guest@#{services_ip}:5672/' \
    -d 'mysql://faafo:password@#{services_ip}:3306/faafo'
"

instance_api_1 = conn.servers.create(:name => 'app-api-1', :flavor_ref => flavor.id, :image_ref => image.id, :key_name => 'demokey', :user_data => userdata, :security_groups => [api_group["name"]])
instance_api_2 = conn.servers.create(:name => 'app-api-2', :flavor_ref => flavor.id, :image_ref => image.id, :key_name => 'demokey', :user_data => userdata, :security_groups => [api_group["name"]])


instance_api_1.wait_for { ready? }
api_1_ip = instance_api_1.accessIPv4
instance_api_2.wait_for { ready? }
api_2_ip = instance_api_2.accessIPv4



for instance in [instance_api_1,  instance_api_2]
    floating_ip = get_floating_ip(conn)
    instance.associate_address(floating_ip["ip"])
    puts "allocated #{floating_ip["ip"]} to #{instance.name}"
end

# step-6
userdata = "#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r worker -e 'http://#{api_1_ip}' -m 'amqp://guest:guest@#{services_ip}:5672/'
"

instance_worker_1 = conn.servers.create(:name => 'app-worker-1', :flavor_ref => flavor.id, :image_ref => image.id, :key_name => 'demokey', :user_data => userdata, :security_groups => [worker_group["name"]])
instance_worker_2 = conn.servers.create(:name => 'app-worker-2', :flavor_ref => flavor.id, :image_ref => image.id, :key_name => 'demokey', :user_data => userdata, :security_groups => [worker_group["name"]])
instance_worker_3 = conn.servers.create(:name => 'app-worker-3', :flavor_ref => flavor.id, :image_ref => image.id, :key_name => 'demokey', :user_data => userdata, :security_groups => [worker_group["name"]])

# step-7
