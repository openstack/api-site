# step-1
require 'fog'

auth_username = 'your_auth_username'
auth_password = 'your_auth_password'
auth_url = 'http://controller:5000'
project_name = 'your_project_name_or_id'
region_name = 'your_region_name'

conn = Fog::Compute.new({
    :provider            => 'openstack',
    :openstack_auth_url  => auth_url + '/v2.0/tokens',
    :openstack_username  => auth_username
    :openstack_tenant    => project_name
    :openstack_api_key   => auth_password
})

# step-2
images = conn.list_images
print images.body

# step-3
flavors = conn.list_flavors
print flavors.body

# step-4
image_id = '2cccbea0-cea9-4f86-a3ed-065c652adda5'
image = conn.images.get image_id
print image

# step-5
flavor_id = '3'
image = conn.flavor.get flavor_id
print flavor

# step-6
instance_name = 'testing'
testing_instance = conn.servers.create(:name => instance_name, :flavor_ref => flavor.id, :image_ref => image.id)

# step-7
conn.servers

# step-8
testing_instance.destroy

# step-9

# step-10
all_in_one_security_group = conn.create_security_group 'all-in-one'  'network access for all-in-one application.'
conn.create_security_group_rule all_in_one_security_group 'TCP' 80 80
conn.create_security_group_rule all_in_one_security_group 'TCP'  22 22

# step-11
# step-12
# step-13
