# step-1
user_data = <<END
#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
-i faafo -i messaging -r api -r worker -r demo
END

instance_name = "all-in-one"
testing_instance = conn.servers.create({
                                         name:            instance_name,
                                         image_ref:       image.id,
                                         flavor_ref:      flavor.id,
                                         key_name:        key_pair.name,
                                         user_data:       user_data,
                                         security_groups: all_in_one_security_group
                                       })
Fog.wait_for {testing_instance.ready?}

# step-2
user_data = <<END
#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
-i messaging -i faafo -r api -r worker -r demo
END

# step-3
all_in_one_security_group = conn.security_groups.create({
                                                          name:        "all-in-one",
                                                          description: "network access for all-in-one application."
                                                        })
conn.security_group_rules.create({
                                   parent_group_id: all_in_one_security_group.id,
                                   ip_protocol:     "tcp",
                                   from_port:       80,
                                   to_port:         80
                                 })
conn.security_group_rules.create({
                                   parent_group_id: all_in_one_security_group.id,
                                   ip_protocol:     "tcp",
                                   from_port:       22,
                                   to_port:         22
                                 })

# step-4
conn.security_groups.all

# step-5
rule.destroy
security_group.destroy

# step-6
testing_instance.security_groups

# step-7
puts "Found an unused Floating IP: #{unused_floating_ip_address.ip}" if unused_floating_ip_address = conn.addresses.find {|address| address.instance_id.nil?}

# step-8
pool_name = conn.addresses.get_address_pools[0]["name"]

# step-9
unused_floating_ip_address = conn.addresses.create({
                                                     pool: pool_name
                                                   })

# step-10
unused_floating_ip_address.server = instance

# step-11
worker_group = conn.security_groups.create({
                                             name:        "worker",
                                             description: "for services that run on a worker node"
                                           })
conn.security_group_rules.create({
                                   parent_group_id: worker_group.id,
                                   ip_protocol:     "tcp",
                                   from_port:       22,
                                   to_port:         22
                                 })

controller_group = conn.security_groups.create({
                                                 name:        "control",
                                                 description: "for services that run on a control node"
                                               })
conn.security_group_rules.create({
                                   parent_group_id: controller_group.id,
                                   ip_protocol:     "tcp",
                                   from_port:       22,
                                   to_port:         22
                                 })
conn.security_group_rules.create({
                                   parent_group_id: controller_group.id,
                                   ip_protocol:     "tcp",
                                   from_port:       80,
                                   to_port:         80
                                 })
conn.security_group_rules.create({
                                   parent_group_id: controller_group.id,
                                   ip_protocol:     "tcp",
                                   from_port:       5672,
                                   to_port:         5672,
                                   group:           worker_group.id
                                 })

user_data = <<END
#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
-i messaging -i faafo -r api
END

instance_controller_1 = conn.servers.create({
                                              name:            "app-controller",
                                              image_ref:       image.id,
                                              flavor_ref:      flavor.id,
                                              key_name:        "demokey",
                                              user_data:       user_data,
                                              security_groups: controller_group
                                            })
Fog.wait_for {instance_controller_1.ready?}

puts "Checking for unused Floating IP..."
unless unused_floating_ip_address = conn.addresses.find {|address| address.instance_id.nil?}
  pool_name = conn.addresses.get_address_pools[0]["name"]
  puts "Allocating new Floating IP from pool: #{pool_name}"
  unused_floating_ip_address = conn.addresses.create({
                                                       pool: pool_name
                                                     })
end

unused_floating_ip_address.server = instance_controller_1
puts "Application will be deployed to http://#{unused_floating_ip_address.ip}"

# step-12
instance_controller_1 = conn.servers.get(instance_controller_1.id)
ip_controller = instance_controller_1.floating_ip_address ? instance_controller_1.private_ip_address : instance_controller_1.floating_ip_address

user_data = <<END
#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
-i faafo -r worker -e "http://#{ip_controller}" -m "amqp://guest:guest@#{ip_controller}:5672/"
END

instance_worker_1 = conn.servers.create({
                                          name:            "app-worker-1",
                                          image_ref:       image.id,
                                          flavor_ref:      flavor.id,
                                          key_name:        "demokey",
                                          user_data:       user_data,
                                          security_groups: worker_group
                                        })
Fog.wait_for {instance_worker_1.ready?}

puts "Checking for unused Floating IP..."
unless unused_floating_ip_address = conn.addresses.find {|address| address.instance_id.nil?}
  pool_name = conn.addresses.get_address_pools[0]["name"]
  puts "Allocating new Floating IP from pool: #{pool_name}"
  unused_floating_ip_address = conn.addresses.create({
                                                       pool: pool_name
                                                     })
end

unused_floating_ip_address.server = instance_worker_1
puts "The worker will be available for SSH at #{unused_floating_ip_address.ip}"

# step-13
puts instance_worker_1.private_ip_address

# step-14
