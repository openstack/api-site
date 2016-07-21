#!/usr/bin/env ruby
require 'fog/openstack'

# step-1
auth_username = "your_auth_username"
auth_password = "your_auth_password"
auth_url      = "http://controller:5000"
project_name  = "your_project_name_or_id"

conn = Fog::Compute::OpenStack.new openstack_auth_url:     auth_url + "/v3/auth/tokens",
                                   openstack_domain_id:    "default",
                                   openstack_username:     auth_username,
                                   openstack_api_key:      auth_password,
                                   openstack_project_name: project_name

# step-2
p conn.images.summary

# step-3
p conn.flavors.summary

# step-4
image = conn.images.get "2cccbea0-cea9-4f86-a3ed-065c652adda5"
p image

# step-5
flavor = conn.flavors.get "2"
p flavor

# step-6
instance_name    = "testing"
testing_instance = conn.servers.create name:       instance_name,
                                       image_ref:  image.id,
                                       flavor_ref: flavor.id

testing_instance.wait_for { ready? }

p testing_instance

# step-7
p conn.servers.summary

# step-8
testing_instance.destroy

# step-9
puts "Checking for existing SSH key pair..."
key_pair_name     = "demokey"
pub_key_file_path = "~/.ssh/id_rsa.pub"

if key_pair = conn.key_pairs.get(key_pair_name)
  puts "Keypair #{key_pair_name} already exists. Skipping import."
else
  puts "adding keypair..."
  key_pair = conn.key_pairs.create name:       key_pair_name,
                                   public_key: File.read(File.expand_path(pub_key_file_path))
end

p conn.key_pairs.all

# step-10
puts "Checking for existing security group..."
security_group_name = "all-in-one"

all_in_one_security_group = conn.security_groups.find do |security_group|
  security_group.name == security_group_name
end

if all_in_one_security_group
  puts "Security Group #{security_group_name} already exists. Skipping creation."
else
  all_in_one_security_group = conn.security_groups.create name:        security_group_name,
                                                          description: "network access for all-in-one application."

  conn.security_group_rules.create parent_group_id: all_in_one_security_group.id,
                                   ip_protocol:     "tcp",
                                   from_port:       80,
                                   to_port:         80

  conn.security_group_rules.create parent_group_id: all_in_one_security_group.id,
                                   ip_protocol:     "tcp",
                                   from_port:       22,
                                   to_port:         22

end

p conn.security_groups.all

# step-11
user_data = <<END
#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
-i faafo -i messaging -r api -r worker -r demo
END

# step-12
puts "Checking for existing instance..."
instance_name = "all-in-one"

if testing_instance = conn.servers.find {|instance| instance.name == instance_name}
  puts "Instance #{instance_name} already exists. Skipping creation."
else
  testing_instance = conn.servers.create name:            instance_name,
                                         image_ref:       image.id,
                                         flavor_ref:      flavor.id,
                                         key_name:        key_pair.name,
                                         user_data:       user_data,
                                         security_groups: all_in_one_security_group

  testing_instance.wait_for { ready? }
end

testing_instance.reload
p conn.servers.summary

# step-13
puts "Private IP found: #{private_ip_address}" if private_ip_address = testing_instance.private_ip_address

# step-14
puts "Public IP found: #{floating_ip_address}" if floating_ip_address = testing_instance.floating_ip_address

# step-15
puts "Checking for unused Floating IP..."
unless unused_floating_ip_address = conn.addresses.find {|address| address.instance_id.nil?}
  pool_name = conn.addresses.get_address_pools[0]["name"]
  puts "Allocating new Floating IP from pool: #{pool_name}"
  unused_floating_ip_address = conn.addresses.create pool: pool_name
end

# step-16
if floating_ip_address
  puts "Instance #{testing_instance.name} already has a public ip. Skipping attachment."
elsif unused_floating_ip_address
  unused_floating_ip_address.server = testing_instance
end

# step-17
actual_ip_address = floating_ip_address || unused_floating_ip_address.ip || private_ip_address
puts "The Fractals app will be deployed to http://#{actual_ip_address}"
