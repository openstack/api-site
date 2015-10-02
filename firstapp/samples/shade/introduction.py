# step-1
userdata = '''#!/usr/bin/env bash

curl -L -s https://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
-i faafo -i messaging -r api -r worker -r demo
'''

instance_name = 'all-in-one'
testing_instance = conn.create_server(wait=True, auto_ip=False,
    name=instance_name,
    image=image_id, flavor=flavor_id, key_name=keypair_name,
    security_groups=[sec_group_name],
    userdata=userdata)

# step-2
userdata = '''#!/usr/bin/env bash

curl -L -s https://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
-i faafo -i messaging -r api -r worker -r demo
'''

# step-3
sec_group_name = 'all-in-one'
conn.create_security_group(sec_group_name, 'network access for all-in-one application.')
conn.create_security_group_rule(sec_group_name, 80, 80, 'TCP')
conn.create_security_group_rule(sec_group_name, 22, 22, 'TCP')

conn.search_security_groups(sec_group_name)

# step-4
conn.list_security_groups()

# step-5
conn.delete_security_group_rule(rule['id'])
conn.delete_security_group(sec_group_name)

# step-6
conn.get_openstack_vars(testing_instance)['security_groups']

# step-7
unused_floating_ip = conn.available_floating_ip()

# step-8
# step-9

# step-10
conn.attach_ip_to_server(testing_instance['id'], unused_floating_ip['id'])

# step-11
worker_group = conn.create_security_group('worker', 'for services that run on a worker node')
conn.create_security_group_rule(worker_group['name'], 22, 22, 'TCP')

controller_group = conn.create_security_group('control', 'for services that run on a control node')
conn.create_security_group_rule(controller_group['name'], 22, 22, 'TCP')
conn.create_security_group_rule(controller_group['name'], 80, 80, 'TCP')
conn.create_security_group_rule(controller_group['name'], 5672, 5672, 'TCP', remote_group_id=worker_group['id'])

userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i messaging -i faafo -r api
'''

instance_controller_1 = conn.create_server(wait=True, auto_ip=False,
    name='app-controller',
    image=image_id,
    flavor=flavor_id,
    key_name=keypair_name,
    security_groups=[controller_group['name']],
    userdata=userdata)

unused_floating_ip = conn.available_floating_ip()

conn.attach_ip_to_server(instance_controller_1['id'], unused_floating_ip['id'])
print('Application will be deployed to http://%s' % unused_floating_ip['floating_ip_address'])

# step-12
instance_controller_1 = conn.get_server(instance_controller_1['id'])

if conn.get_server_public_ip(instance_controller_1):
    ip_controller = conn.get_server_public_ip(instance_controller_1)
else:
    ip_controller = conn.get_server_private_ip(instance_controller_1)

userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r worker -e 'http://%(ip_controller)s' -m 'amqp://guest:guest@%(ip_controller)s:5672/'
''' % {'ip_controller': ip_controller}

instance_worker_1 = conn.create_server(wait=True, auto_ip=False,
    name='app-worker-1',
    image=image_id,
    flavor=flavor_id,
    key_name=keypair_name,
    security_groups=[worker_group['name']],
    userdata=userdata)

unused_floating_ip = conn.available_floating_ip()

conn.attach_ip_to_server(instance_worker_1['id'], unused_floating_ip['id'], wait=True)
print('The worker will be available for SSH at %s' % unused_floating_ip['floating_ip_address'])


# step-13
instance_worker_1 = conn.get_server(instance_worker_1['name'])
ip_instance_worker_1 = conn.get_server_public_ip(instance_worker_1)
print(ip_instance_worker_1)

# step-14
