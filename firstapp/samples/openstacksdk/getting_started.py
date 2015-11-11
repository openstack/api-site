# step-1
import base64
from os.path import expanduser

from openstack import connection
from openstack import exceptions

auth_username = 'your_auth_username'
auth_password = 'your_auth_password'
auth_url = 'http://controller:5000/v2.0'
project_name = 'your_project_name_or_id'
region_name = 'your_region_name'

conn = connection.Connection(auth_url=auth_url,
                             project_name=project_name,
                             username=auth_username,
                             password=auth_password,
                             region=region_name)

# step-2
images = conn.image.images()
for image in images:
    print(image)

# step-3
flavors = conn.compute.flavors()
for flavor in flavors:
    print(flavor)

# step-4
image_id = 'cb6b7936-d2c5-4901-8678-c88b3a6ed84c'
image = conn.compute.get_image(image_id)
print(image)

# step-5
flavor_id = '2'
flavor = conn.compute.get_flavor(flavor_id)
print(flavor)

# step-6
instance_name = 'testing'
image_args = {
    'name': instance_name,
    'imageRef': image,
    'flavorRef': flavor
}

testing_instance = conn.compute.create_server(**image_args)
print(testing_instance)

# step-7
instances = conn.compute.servers()
for instance in instances:
    print(instance)

# step-8
conn.compute.delete_server(testing_instance)

# step-9
print('Checking for existing SSH key pair...')
keypair_name = 'demokey'
keypair_exists = False
for keypair in conn.compute.keypairs():
    if keypair.name == keypair_name:
        keypair_exists = True

if keypair_exists:
    print('Keypair ' + keypair_name + ' already exists. Skipping import.')
else:
    print('adding keypair...')
    pub_key_file = open(expanduser('~/.ssh/id_rsa.pub')).read()
    keypair_args = {
        "name": keypair_name,
        "public_key": pub_key_file
    }
    conn.compute.create_keypair(**keypair_args)

for keypair in conn.compute.keypairs():
    print(keypair)

# step-10
print('Checking for existing security group...')
security_group_name = 'all-in-one'
security_group_exists = False
for security_group in conn.network.security_groups():
    if security_group.name == security_group_name:
        all_in_one_security_group = security_group
        security_group_exists = True

if security_group_exists:
    print('Security Group ' + all_in_one_security_group.name + ' already exists. Skipping creation.')
else:
    security_group_args = {
        'name' : security_group_name,
        'description': 'network access for all-in-one application.'
    }
    all_in_one_security_group = conn.network.create_security_group(**security_group_args)

    security_rule_args = {
        'security_group_id': all_in_one_security_group,
        'direction': 'ingress',
        'protocol': 'tcp',
        'port_range_min': '80',
        'port_range_max': '80'
    }
    conn.network.create_security_group_rule(**security_rule_args)

    security_rule_args['port_range_min'] = '22'
    security_rule_args['port_range_max'] = '22'
    conn.network.create_security_group_rule(**security_rule_args)

for security_group in conn.network.security_groups():
    print(security_group)

# step-11
userdata = '''#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -i messaging -r api -r worker -r demo
'''
userdata_b64str = base64.b64encode(userdata)

# step-12
print('Checking for existing instance...')
instance_name = 'all-in-one'
instance_exists = False
for instance in conn.compute.servers():
    if instance.name == instance_name:
        testing_instance = instance
        instance_exists = True

if instance_exists:
    print('Instance ' + testing_instance.name + ' already exists. Skipping creation.')
else:

    testing_instance_args = {
        'name': instance_name,
        'imageRef': image,
        'flavorRef': flavor,
        'key_name': keypair_name,
        'user_data': userdata_b64str,
        'security_groups': [{'name': all_in_one_security_group.name}]
    }

    testing_instance = conn.compute.create_server(**testing_instance_args)
    conn.compute.wait_for_server(testing_instance)

for instance in conn.compute.servers():
    print(instance)

# step-13
print('Checking if Floating IP is already assigned to testing_instance...')
testing_instance_floating_ip = None
for values in testing_instance.addresses.itervalues():
    for address in values:
        if address['OS-EXT-IPS:type'] == 'floating':
            testing_instance_floating_ip = conn.network.find_ip(address['addr'])

unused_floating_ip = None
if not testing_instance_floating_ip:
    print('Checking for unused Floating IP...')
    for floating_ip in conn.network.ips():
        if not floating_ip.fixed_ip_address:
            unused_floating_ip = floating_ip
            break

if not testing_instance_floating_ip and not unused_floating_ip:
    print('No free unused Floating IPs. Allocating new Floating IP...')
    public_network_id = conn.network.find_network('public').id
    try:
        unused_floating_ip = conn.network.create_ip(floating_network_id=public_network_id)
        unused_floating_ip = conn.network.get_ip(unused_floating_ip)
        print(unused_floating_ip)
    except exceptions.HttpException as e:
        print(e)

# step-14
if testing_instance_floating_ip:
    print('Instance ' + testing_instance.name + ' already has a public ip. Skipping attachment.')
else:
    for port in conn.network.ports():
        if port.device_id == testing_instance.id:
            testing_instance_port = port

    testing_instance_floating_ip = unused_floating_ip
    conn.network.add_ip_to_port(testing_instance_port, testing_instance_floating_ip)

# step-15
print('The Fractals app will be deployed to http://%s' % testing_instance_floating_ip.floating_ip_address)
