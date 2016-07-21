# step-1
for instance in conn.list_servers():
    if instance.name in ['all-in-one','app-worker-1', 'app-worker-2', 'app-controller']:
        print('Destroying Instance: %s' % instance.name)
        conn.delete_server(instance.id, wait=True)

for group in conn.list_security_groups():
    if group['name'] in ['control', 'worker', 'api', 'services']:
        print('Deleting security group: %s' % group['name'])
        conn.delete_security_group(group['name'])

# step-2
api_group = conn.create_security_group('api', 'for API services only')
conn.create_security_group_rule(api_group['name'], 80, 80, 'TCP')
conn.create_security_group_rule(api_group['name'], 22, 22, 'TCP')

worker_group = conn.create_security_group('worker', 'for services that run on a worker node')
conn.create_security_group_rule(worker_group['name'], 22, 22, 'TCP')

services_group = conn.create_security_group('services', 'for DB and AMQP services only')
conn.create_security_group_rule(services_group['name'], 22, 22, 'TCP')
conn.create_security_group_rule(services_group['name'], 3306, 3306, 'TCP', remote_group_id=api_group['id'])
conn.create_security_group_rule(services_group['name'], 5672, 5672, 'TCP', remote_group_id=worker_group['id'])
conn.create_security_group_rule(services_group['name'], 5672, 5672, 'TCP', remote_group_id=api_group['id'])

# step-3
def get_floating_ip(conn):
    '''A helper function to re-use available Floating IPs'''
    return conn.available_floating_ip()

# step-4
userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i database -i messaging
'''

instance_services = conn.create_server(wait=True, auto_ip=False,
    name='app-services',
    image=image_id,
    flavor=flavor_id,
    key_name='demokey',
    security_groups=[services_group['name']],
    userdata=userdata)

services_ip = conn.get_server_private_ip(instance_services)

# step-5
userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r api -m 'amqp://guest:guest@%(services_ip)s:5672/' \
    -d 'mysql+pymysql://faafo:password@%(services_ip)s:3306/faafo'
''' % { 'services_ip': services_ip }

instance_api_1 = conn.create_server(wait=True, auto_ip=False,
    name='app-api-1',
    image=image_id,
    flavor=flavor_id,
    key_name='demokey',
    security_groups=[api_group['name']],
    userdata=userdata)
instance_api_2 = conn.create_server(wait=True, auto_ip=False,
    name='app-api-2',
    image=image_id,
    flavor=flavor_id,
    key_name='demokey',
    security_groups=[api_group['name']],
    userdata=userdata)

api_1_ip = conn.get_server_private_ip(instance_api_1)
api_2_ip = conn.get_server_private_ip(instance_api_2)

for instance in [instance_api_1,  instance_api_2]:
    floating_ip = get_floating_ip(conn)
    conn.add_ip_list(instance, [floating_ip['floating_ip_address']])
    print('allocated %(ip)s to %(host)s' % {'ip': floating_ip['floating_ip_address'], 'host': instance['name']})

# step-6
userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r worker -e 'http://%(api_1_ip)s' -m 'amqp://guest:guest@%(services_ip)s:5672/'
''' % {'api_1_ip': api_1_ip, 'services_ip': services_ip}

instance_worker_1 = conn.create_server(wait=True, auto_ip=False,
    name='app-worker-1',
    image=image_id,
    flavor=flavor_id,
    key_name='demokey',
    security_groups=[worker_group['name']],
    userdata=userdata)

instance_worker_2 = conn.create_server(wait=True, auto_ip=False,
    name='app-worker-2',
    image=image_id,
    flavor=flavor_id,
    key_name='demokey',
    security_groups=[worker_group['name']],
    userdata=userdata)

instance_worker_3 = conn.create_server(wait=True, auto_ip=False,
    name='app-worker-3',
    image=image_id,
    flavor=flavor_id,
    key_name='demokey',
    security_groups=[worker_group['name']],
    userdata=userdata)
