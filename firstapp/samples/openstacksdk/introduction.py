# step-1
userdata = '''#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -i messaging -r api -r worker -r demo
'''
userdata_b64str = base64.b64encode(userdata)

instance_name = 'all-in-one'
testing_instance_args = {
    'name': instance_name,
    'imageRef': image,
    'flavorRef': flavor,
    'key_name': keypair_name,
    'user_data': userdata_b64str,
    'security_groups': [{'name': all_in_one_security_group.name}]
}

testing_instance = conn.compute.create_server(**testing_instance_args)

# step-2
userdata = '''#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -i messaging -r api -r worker -r demo
'''
userdata_b64str = base64.b64encode(userdata)

# step-3
security_group_args = {
    'name' : 'all-in-one',
    'description': 'network access for all-in-one application.'
}
all_in_one_security_group = conn.network.create_security_group(**security_group_args)

# HTTP access
security_rule_args = {
    'security_group_id': all_in_one_security_group,
    'direction': 'ingress',
    'protocol': 'tcp',
    'port_range_min': '80',
    'port_range_max': '80'
}
conn.network.create_security_group_rule(**security_rule_args)

# SSH access
security_rule_args['port_range_min'] = '22'
security_rule_args['port_range_max'] = '22'
conn.network.create_security_group_rule(**security_rule_args)

# step-4
for security_group in conn.network.security_groups():
    print(security_group)

# step-5
conn.network.delete_security_group_rule(rule)
conn.network.delete_security_group(security_group)

# step-6
testing_instance['security_groups']

# step-7
unused_floating_ip = None
for floating_ip in conn.network.ips():
    if not floating_ip.fixed_ip_address:
        unused_floating_ip = floating_ip
        print("Found an unused Floating IP: %s" % floating_ip)
        break

# step-8
public_network_id = conn.network.find_network('public').id

# step-9
unused_floating_ip = conn.network.create_ip(floating_network_id=public_network_id)
unused_floating_ip = conn.network.get_ip(unused_floating_ip)

# step-10
for port in conn.network.ports():
    if port.device_id == testing_instance.id:
        testing_instance_port = port
        break

testing_instance_floating_ip = unused_floating_ip
conn.network.add_ip_to_port(testing_instance_port, testing_instance_floating_ip)

# step-11
security_group_args = {
    'name' : 'worker',
    'description': 'for services that run on a worker node'
}
worker_group = conn.network.create_security_group(**security_group_args)

security_rule_args = {
    'security_group_id': worker_group,
    'direction': 'ingress',
    'protocol': 'tcp',
    'port_range_min': '22',
    'port_range_max': '22'
}
conn.network.create_security_group_rule(**security_rule_args)

security_group_args = {
    'name' : 'control',
    'description': 'for services that run on a control node'
}
controller_group = conn.network.create_security_group(**security_group_args)

# Switch to controller_group and readd SSH access rule
security_rule_args['security_group_id'] = controller_group
conn.network.create_security_group_rule(**security_rule_args)

# Add HTTP access rule
security_rule_args['port_range_min'] = '80'
security_rule_args['port_range_max'] = '80'
conn.network.create_security_group_rule(**security_rule_args)

# Add RabbitMQ access rule for all instances with
# 'worker' security group
security_rule_args['port_range_min'] = '5672'
security_rule_args['port_range_max'] = '5672'
security_rule_args['remote_group_id'] = worker_group
conn.network.create_security_group_rule(**security_rule_args)

userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i messaging -i faafo -r api
'''
userdata_b64str = base64.b64encode(userdata)

instance_controller_1_args = {
    'name': 'app-controller',
    'imageRef': image,
    'flavorRef': flavor,
    'key_name': 'demokey',
    'user_data': userdata_b64str,
    'security_groups': [{'name': controller_group.name}]
}

instance_controller_1 = conn.compute.create_server(**instance_controller_1_args)
conn.compute.wait_for_server(instance_controller_1)

print('Checking for unused Floating IP...')
unused_floating_ip = None
for floating_ip in conn.network.ips():
    if not floating_ip.fixed_ip_address:
        unused_floating_ip = floating_ip
        print("Found an unused Floating IP: %s" % floating_ip)
        break

if not unused_floating_ip:
    print('No free unused Floating IPs. Allocating new Floating IP...')
    public_network_id = conn.network.find_network('public').id
    unused_floating_ip = conn.network.create_ip(floating_network_id=public_network_id)
    unused_floating_ip = conn.network.get_ip(unused_floating_ip)

for port in conn.network.ports():
    if port.device_id == instance_controller_1.id:
        controller_instance_port = port
        break

controller_instance_floating_ip = unused_floating_ip
conn.network.add_ip_to_port(controller_instance_port, controller_instance_floating_ip)

# Retrieve all information about 'instance_controller_1'
instance_controller_1 = conn.compute.get_server(instance_controller_1)

print('Application will be deployed to http://%s' % controller_instance_floating_ip.floating_ip_address)

# step-12
for values in instance_controller_1.addresses.itervalues():
    for address in values:
        if address['OS-EXT-IPS:type'] == 'fixed':
            ip_controller = address['addr']
            break

userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r worker -e 'http://%(ip_controller)s' -m 'amqp://guest:guest@%(ip_controller)s:5672/'
''' % {'ip_controller': ip_controller}
userdata_b64str = base64.b64encode(userdata)

instance_worker_1_args = {
    'name': 'app-worker-1',
    'imageRef': image,
    'flavorRef': flavor,
    'key_name': 'demokey',
    'user_data': userdata_b64str,
    'security_groups': [{'name': worker_group.name}]
}

instance_worker_1 = conn.compute.create_server(**instance_worker_1_args)
conn.compute.wait_for_server(instance_worker_1)

print('Checking for unused Floating IP...')
unused_floating_ip = None
for floating_ip in conn.network.ips():
    if not floating_ip.fixed_ip_address:
        unused_floating_ip = floating_ip
        print("Found an unused Floating IP: %s" % floating_ip)
        break

if not unused_floating_ip:
    print('No free unused Floating IPs. Allocating new Floating IP...')
    public_network_id = conn.network.find_network('public').id
    unused_floating_ip = conn.network.create_ip(floating_network_id=public_network_id)
    unused_floating_ip = conn.network.get_ip(unused_floating_ip)

for port in conn.network.ports():
    if port.device_id == instance_worker_1.id:
        worker_instance_port = port
        break

worker_instance_floating_ip = unused_floating_ip
conn.network.add_ip_to_port(worker_instance_port, worker_instance_floating_ip)

# Retrieve all information about 'instance_worker_1'
instance_worker_1 = conn.compute.get_server(instance_worker_1)

print('The worker will be available for SSH at %s' % worker_instance_floating_ip.floating_ip_address)

# step-13
for values in instance_worker_1.addresses.itervalues():
    for address in values:
        if address['OS-EXT-IPS:type'] == 'floating':
            ip_instance_worker_1 = address['addr']
            break

print(ip_instance_worker_1)

# step-14
