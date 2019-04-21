# step-1
userdata = '''#!/usr/bin/env bash

curl -L -s https://opendev.org/openstack/faafo/raw/contrib/install.sh | bash -s -- \
-i faafo -i messaging -r api -r worker -r demo
'''

instance_name = 'all-in-one'
testing_instance = conn.create_server(wait=True, auto_ip=False,
    name=instance_name,
    image=image_id,
    flavor=flavor_id,
    key_name=keypair_name,
    security_groups=[sec_group_name],
    userdata=userdata)

# step-2
userdata = '''#!/usr/bin/env bash

curl -L -s https://opendev.org/openstack/faafo/raw/contrib/install.sh | bash -s -- \
-i faafo -i messaging -r api -r worker -r demo
'''

# step-3
sec_group_name = 'all-in-one'
conn.create_security_group(sec_group_name, 'network access for all-in-one application.')
conn.create_security_group_rule(sec_group_name, 80, 80, 'TCP')
conn.create_security_group_rule(sec_group_name, 22, 22, 'TCP')

# step-4
sec_groups = conn.list_security_groups()
for sec_group in sec_groups:
    print(sec_group)

# step-5
conn.delete_security_group_rule(rule_id)
conn.delete_security_group(sec_group_name)

# step-6
conn.get_openstack_vars(testing_instance)['security_groups']

# step-7
unused_floating_ip = conn.available_floating_ip()

# step-8
# step-9

# step-10
conn.add_ip_list(testing_instance, [unused_floating_ip['floating_ip_address']])

# step-11
worker_group_name = 'worker'
if conn.search_security_groups(worker_group_name):
    print('Security group \'%s\' already exists. Skipping creation.' % worker_group_name)
else:
    worker_group = conn.create_security_group(worker_group_name, 'for services that run on a worker node')
    conn.create_security_group_rule(worker_group['name'], 22, 22, 'TCP')

controller_group_name = 'control'
if conn.search_security_groups(controller_group_name):
    print('Security group \'%s\' already exists. Skipping creation.' % controller_group_name)
else:
    controller_group = conn.create_security_group(controller_group_name, 'for services that run on a control node')
    conn.create_security_group_rule(controller_group['name'], 22, 22, 'TCP')
    conn.create_security_group_rule(controller_group['name'], 80, 80, 'TCP')
    conn.create_security_group_rule(controller_group['name'], 5672, 5672, 'TCP', remote_group_id=worker_group['id'])

userdata = '''#!/usr/bin/env bash
curl -L -s https://opendev.org/openstack/faafo/raw/contrib/install.sh | bash -s -- \
    -i messaging -i faafo -r api
'''

instance_controller_1 = conn.create_server(wait=True, auto_ip=False,
    name='app-controller',
    image=image_id,
    flavor=flavor_id,
    key_name=keypair_name,
    security_groups=[controller_group_name],
    userdata=userdata)

unused_floating_ip = conn.available_floating_ip()

conn.add_ip_list(instance_controller_1, [unused_floating_ip['floating_ip_address']])
print('Application will be deployed to http://%s' % unused_floating_ip['floating_ip_address'])

# step-12
instance_controller_1 = conn.get_server(instance_controller_1['id'])

if conn.get_server_public_ip(instance_controller_1):
    ip_controller = conn.get_server_public_ip(instance_controller_1)
else:
    ip_controller = conn.get_server_private_ip(instance_controller_1)

userdata = '''#!/usr/bin/env bash
curl -L -s https://opendev.org/openstack/faafo/raw/contrib/install.sh | bash -s -- \
    -i faafo -r worker -e 'http://%(ip_controller)s' -m 'amqp://guest:guest@%(ip_controller)s:5672/'
''' % {'ip_controller': ip_controller}

instance_worker_1 = conn.create_server(wait=True, auto_ip=False,
    name='app-worker-1',
    image=image_id,
    flavor=flavor_id,
    key_name=keypair_name,
    security_groups=[worker_group_name],
    userdata=userdata)

unused_floating_ip = conn.available_floating_ip()

conn.add_ip_list(instance_worker_1, [unused_floating_ip['floating_ip_address']])
print('The worker will be available for SSH at %s' % unused_floating_ip['floating_ip_address'])


# step-13
instance_worker_1 = conn.get_server(instance_worker_1['name'])
ip_instance_worker_1 = conn.get_server_public_ip(instance_worker_1)
print(ip_instance_worker_1)
