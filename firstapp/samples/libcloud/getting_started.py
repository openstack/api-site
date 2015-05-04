# step-1
from libcloud.compute.types import Provider
from libcloud.compute.providers import get_driver

auth_username = 'your_auth_username'
auth_password = 'your_auth_password'
auth_url = 'http://controller:5000'
project_name = 'your_project_name_or_id'
region_name = 'your_region_name'

provider = get_driver(Provider.OPENSTACK)
conn = provider(auth_username,
                auth_password,
                ex_force_auth_url=auth_url,
                ex_force_auth_version='2.0_password',
                ex_tenant_name=project_name,
                ex_force_service_region=region_name)

# step-2
images = conn.list_images()
for image in images:
    print(image)

# step-3
flavors = conn.list_sizes()
for flavor in flavors:
    print(flavor)

# step-4
image_id = '2cccbea0-cea9-4f86-a3ed-065c652adda5'
image = conn.get_image(image_id)
print(image)

# step-5
flavor_id = '3'
flavor = conn.ex_get_size(flavor_id)
print(flavor)

# step-6
instance_name = 'testing'
testing_instance = conn.create_node(name=instance_name, image=image, size=flavor)
print(testing_instance)

# step-7
instances = conn.list_nodes()
for instance in instances:
    print(instance)

# step-8
conn.destroy_node(testing_instance)

# step-9
print('Checking for existing SSH key pair...')
keypair_name = 'demokey'
pub_key_file = '~/.ssh/id_rsa.pub'
keypair_exists = False
for keypair in conn.list_key_pairs():
    if keypair.name == keypair_name:
        keypair_exists = True

if keypair_exists:
    print('Keypair already exists.  Skipping import.')
else:
    print('adding keypair...')
    conn.import_key_pair_from_file(keypair_name, pub_key_file)

for keypair in conn.list_key_pairs():
    print(keypair)


# step-10
security_group_exists = False
for security_group in conn.ex_list_security_groups():
    if security_group.name =='all-in-one':
        all_in_one_security_group = security_group
        security_group_exists = True

if security_group_exists:
    print('Security Group already exists.  Skipping creation.')
else:
    all_in_one_security_group = conn.ex_create_security_group('all-in-one', 'network access for all-in-one application.')
    conn.ex_create_security_group_rule(all_in_one_security_group, 'TCP', 80, 80)
    conn.ex_create_security_group_rule(all_in_one_security_group, 'TCP', 22, 22)

# step-11
userdata = '''#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -i messaging -r api -r worker -r demo
'''

# step-12
instance_name = 'all-in-one'
testing_instance = conn.create_node(name=instance_name,
                                    image=image,
                                    size=flavor,
                                    ex_keyname=keypair_name,
                                    ex_userdata=userdata,
                                    ex_security_groups=[all_in_one_security_group])
conn.wait_until_running([testing_instance])

# step-13
print('Checking for unused Floating IP...')
unused_floating_ip = None
for floating_ip in conn.ex_list_floating_ips():
    if floating_ip.node_id:
        unused_floating_ip = floating_ip
        break


if not unused_floating_ip:
    pool = conn.ex_list_floating_ip_pools()[0]
    print('Allocating new Floating IP from pool: {}'.format(pool))
    unused_floating_ip = pool.create_floating_ip()

# step-14
conn.ex_attach_floating_ip_to_node(testing_instance, unused_floating_ip)

# step-15
print('The Fractals app will be deployed to http://%s' % unused_floating_ip.ip_address)
