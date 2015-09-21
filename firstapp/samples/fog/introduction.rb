# step-1
userdata = '''#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -i messaging -r api -r worker -r demo
'''

instance_name = 'all-in-one'
testing_instance = conn.servers.create(:name => instance_name, :flavor_ref => flavor.id, :image_ref => image.id, :key_name => keypair_name, :user_data => userdata, :security_groups => [all_in_one_security_group["name"]])

# step-2
userdata = '''#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i messaging -i faafo -r api -r worker -r demo
'''

# step-3
all_in_one_security_group_response = conn.create_security_group('all-in-one', 'network access for all-in-one application.')
all_in_one_security_group = all_in_one_security_group_response.body["security_group"]
conn.create_security_group_rule(all_in_one_security_group["id"], 'TCP', '80', '80', '0.0.0.0/0')
conn.create_security_group_rule(all_in_one_security_group["id"], 'TCP',  '22', '22', '0.0.0.0/0')

# step-4
conn.list_security_groups.body["security_groups"]

# step-5
conn.delete_security_group_rule(rule["id"])
conn.delete_security_group(security_group["id"])

# step-6
conn.list_security_groups(testing_instance["id"])

# step-7
unused_floating_ips = nil
for floating_ip in conn.list_all_addresses.body["floating_ips"]
    if not floating_ip.server_id
        unused_floating_ip = floating_ip
        puts "Found an unused Floating IP: %s" % floating_ip
        break
    end
end


# step-8
pool = conn.list_address_pools.body["floating_ip_pools"][0]

# step-9
unused_floating_ip = conn.allocate_address(pool)

# step-10
conn.associate_address(testing_instance, unused_floating_ip)

# step-11
# XXX TODO TBC
worker_group_response = conn.create_security_group('worker', 'for services that run on a worker node')
worker_group = worker_group_response.body["security_group"]
conn.create_security_group_rule(worker_group["id"], 'TCP',  '22', '22', '0.0.0.0/0')

controller_group_response = conn.create_security_group('control', 'for services that run on a control node')
controller_group = controller_group_response.body["security_group"]
conn.create_security_group_rule(controller_group["id"], 'TCP', '80', '80', '0.0.0.0/0')
conn.create_security_group_rule(controller_group["id"], 'TCP',  '22', '22', '0.0.0.0/0')
conn.create_security_group_rule(controller_group["id"], 'TCP', '5672', '5672', '0.0.0.0/0', worker_group["id"])

userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i messaging -i faafo -r api
'''

instance_controller_1 = conn.servers.create(:name => 'app-controller', :flavor_ref => flavor.id, :image_ref => image.id, :key_name => 'demokey', :user_data => userdata, :security_groups => [controller_group["name"]])

instance_controller_1.wait_for { ready? }

puts 'Checking for unused Floating IP...'
unused_floating_ip = nil
for floating_ip in conn.list_all_addresses.body["floating_ips"]
    if not floating_ip["instance_id"]
        unused_floating_ip = floating_ip
        break
    end
end


if not unused_floating_ip
    pool = conn.list_address_pools.body["floating_ip_pools"][0]
    puts "Allocating new Floating IP from pool: #{pool['name']}"
    unused_floating_ip = conn.allocate_address(pool["name"]).body["floating_ip"]
end

instance_controller_1.associate_address(unused_floating_ip["ip"])
puts 'Application will be deployed to http://%s' % unused_floating_ip["ip"]

# step-12
# XXX TODO TBC
instance_controller_addresses = instance_controller_1.all_addresses
if instance_controller_addresses[0]["ip"]
    ip_controller = instance_controller_addresses[0]["ip"]
else
    ip_controller = instance_controller_addresses[0]["fixed_ip"]
end

userdata = "#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r worker -e 'http://#{ip_controller}' -m 'amqp://guest:guest@#{ip_controller}:5672/'
"

instance_worker_1 = conn.servers.create(:name => 'app-worker-1', :flavor_ref => flavor.id, :image_ref => image.id, :key_name => 'demokey', :user_data => userdata, :security_groups => [worker_group["name"]])

instance_worker_1.wait_for { ready? }

puts 'Checking for unused Floating IP...'
unused_floating_ip = nil
for floating_ip in conn.list_all_addresses.body["floating_ips"]
    if not floating_ip["instance_id"]
        unused_floating_ip = floating_ip
        break
    end
end

if not unused_floating_ip
    pool = conn.list_address_pools.body["floating_ip_pools"][0]
    puts "Allocating new Floating IP from pool: #{pool['name']}"
    unused_floating_ip = conn.allocate_address(pool["name"]).body["floating_ip"]
end

instance_worker_1.associate_address(unused_floating_ip["ip"])
puts 'The worker will be available for SSH at %s' % unused_floating_ip["ip"]


# step-13
# XXX TODO TBC
ip_instance_worker_1 = instance_worker_1.all_addresses[0]["fixed_ip"]
puts ip_instance_worker_1

# step-14
