# step-1
instance_names = ["all-in-one","app-worker-1", "app-worker-2", "app-controller"]

conn.servers.select {|instance| instance_names.include?(instance.name)}.each do |instance|
  puts "Destroying Instance: #{instance.name}"
  instance.destroy
end

security_group_names = ["control", "worker", "api", "services"]

conn.security_groups.select {|security_group| security_group_names.include?(security_group.name)}.each do |security_group|
  puts "Deleting security group: #{security_group.name}"
  security_group.destroy
end

# step-2
api_group        = conn.security_groups.create name:        "api",
                                               description: "for API services only"

worker_group     = conn.security_groups.create name:        "worker",
                                               description: "for services that run on a worker node"

controller_group = conn.security_groups.create name:        "control",
                                               description: "for services that run on a control node"

services_group   = conn.security_groups.create name:        "services",
                                               description: "for DB and AMQP services only"

rules = [
  {
    parent_group_id: api_group.id,
    ip_protocol:     "tcp",
    from_port:       80,
    to_port:         80
  },
  {
    parent_group_id: api_group.id,
    ip_protocol:     "tcp",
    from_port:       22,
    to_port:         22
  },
  {
    parent_group_id: worker_group.id,
    ip_protocol:     "tcp",
    from_port:       22,
    to_port:         22
  },
  {
    parent_group_id: controller_group.id,
    ip_protocol:     "tcp",
    from_port:       22,
    to_port:         22
  },
  {
    parent_group_id: controller_group.id,
    ip_protocol:     "tcp",
    from_port:       80,
    to_port:         80
  },
  {
    parent_group_id: controller_group.id,
    ip_protocol:     "tcp",
    from_port:       5672,
    to_port:         5672,
    group:           worker_group.id
  },
  {
    parent_group_id: services_group.id,
    ip_protocol:     "tcp",
    from_port:       22,
    to_port:         22
  },
  {
    parent_group_id: services_group.id,
    ip_protocol:     "tcp",
    from_port:       3306,
    to_port:         3306,
    group:           api_group.id
  },
  {
    parent_group_id: services_group.id,
    ip_protocol:     "tcp",
    from_port:       5672,
    to_port:         5672,
    group:           worker_group.id
  },
  {
    parent_group_id: services_group.id,
    ip_protocol:     "tcp",
    from_port:       5672,
    to_port:         5672,
    group:           api_group.id
  }
]
rules.each {|rule| conn.security_group_rules.create rule }

# step-3
def get_floating_ip_address(conn)
  unless unused_floating_ip_address = conn.addresses.find {|address| address.instance_id.nil?}
    pool_name = conn.addresses.get_address_pools[0]["name"]
    puts "Allocating new Floating IP from pool: #{pool_name}"
    unused_floating_ip_address = conn.addresses.create pool: pool_name
  end

  unused_floating_ip_address
end

# step-4
user_data = <<END
#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
-i database -i messaging
END

instance_services = conn.servers.create name:            "app-services",
                                        image_ref:       image.id,
                                        flavor_ref:      flavor.id,
                                        key_name:        "demokey",
                                        user_data:       user_data,
                                        security_groups: services_group

Fog.wait_for {instance_services.ready?}
services_ip_address = instance_services.private_ip_address

# step-5
user_data = <<END
#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
-i faafo -r api -m "amqp://guest:guest@#{services_ip_address}:5672/" -d "mysql+pymysql://faafo:password@#{services_ip_address}:3306/faafo"
END

instance_api_1 = conn.servers.create name:            "app-api-1",
                                     image_ref:       image.id,
                                     flavor_ref:      flavor.id,
                                     key_name:        "demokey",
                                     user_data:       user_data,
                                     security_groups: api_group

instance_api_2 = conn.servers.create name:            "app-api-2",
                                     image_ref:       image.id,
                                     flavor_ref:      flavor.id,
                                     key_name:        "demokey",
                                     user_data:       user_data,
                                     security_groups: api_group

Fog.wait_for {instance_api_1.ready?}
api_1_ip_address = instance_api_1.private_ip_address
Fog.wait_for {instance_api_2.ready?}
api_2_ip_address = instance_api_2.private_ip_address

[instance_api_1, instance_api_2].each do |instance|
  floating_ip_address        = get_floating_ip_address(conn)
  floating_ip_address.server = instance
  puts "allocated #{floating_ip_address.ip} to #{instance.name}"
end

# step-6
user_data = <<END
#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
-i faafo -r worker -e "http://#{api_1_ip_address}" -m "amqp://guest:guest@#{services_ip_address}:5672/"
END

instance_worker_1 = conn.servers.create name:            "app-worker-1",
                                        image_ref:       image.id,
                                        flavor_ref:      flavor.id,
                                        key_name:        "demokey",
                                        user_data:       user_data,
                                        security_groups: worker_group

instance_worker_2 = conn.servers.create name:            "app-worker-2",
                                        image_ref:       image.id,
                                        flavor_ref:      flavor.id,
                                        key_name:        "demokey",
                                        user_data:       user_data,
                                        security_groups: worker_group

instance_worker_3 = conn.servers.create name:            "app-worker-3",
                                        image_ref:       image.id,
                                        flavor_ref:      flavor.id,
                                        key_name:        "demokey",
                                        user_data:       user_data,
                                        security_groups: worker_group

# step-7
