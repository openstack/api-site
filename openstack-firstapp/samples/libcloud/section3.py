# step-1
for instance in conn.list_nodes():
    if instance.name in ['all-in-one','app-worker-1', 'app-worker-2', 'app-controller']:
        print('Destroying Instance: %s' % instance.name)
        conn.destroy_node(instance)


for group in conn.ex_list_security_groups():
    if group.name in ['control', 'worker', 'api', 'services']:
        print('Deleting security group: %s' % group.name)
        conn.ex_delete_security_group(group)

# step-2
api_group = conn.ex_create_security_group('api', 'for API services only')
conn.ex_create_security_group_rule(api_group, 'TCP', 80, 80)
conn.ex_create_security_group_rule(api_group, 'TCP', 22, 22)

worker_group = conn.ex_create_security_group('worker', 'for services that run on a worker note')
conn.ex_create_security_group_rule(worker_group, 'TCP', 22, 22)

controller_group = conn.ex_create_security_group('control', 'for services that run on a control note')
conn.ex_create_security_group_rule(controller_group, 'TCP', 22, 22)
conn.ex_create_security_group_rule(controller_group, 'TCP', 80, 80)
conn.ex_create_security_group_rule(controller_group, 'TCP', 5672, 5672, source_security_group=worker_group)

services_group = conn.ex_create_security_group('services', 'for DB and AMQP services only')
conn.ex_create_security_group_rule(services_group, 'TCP', 22, 22)
conn.ex_create_security_group_rule(services_group, 'TCP', 3306, 3306, source_security_group=api_group)
conn.ex_create_security_group_rule(services_group, 'TCP', 5672, 5672, source_security_group=worker_group)
conn.ex_create_security_group_rule(services_group, 'TCP', 5672, 5672, source_security_group=api_group)

# step-3
def get_floating_ip(conn):
    '''A helper function to re-use available Floating IPs'''
    unused_floating_ip = None
    for floating_ip in conn.ex_list_floating_ips():
        if not floating_ip.node_id:
            unused_floating_ip = floating_ip
            break
    if not unused_floating_ip:
        pool = conn.ex_list_floating_ip_pools()[0]
        unused_floating_ip = pool.create_floating_ip()
    return unused_floating_ip

# step-4
userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i database -i messaging
'''

instance_services = conn.create_node(name='app-services',
                                     image=image,
                                     size=flavor,
                                     ex_keyname='demokey',
                                     ex_userdata=userdata,
                                     ex_security_groups=[services_group])
instance_services = conn.wait_until_running([instance_services])[0][0]
services_ip = instance_services.private_ips[0]


# step-5
userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r api -m 'amqp://guest:guest@%(services_ip)s:5672/' \
    -d 'mysql://faafo:password@%(services_ip)s:3306/faafo'
''' % { 'services_ip': services_ip }
instance_api_1 = conn.create_node(name='app-api-1',
                                  image=image,
                                  size=flavor,
                                  ex_keyname='demokey',
                                  ex_userdata=userdata,
                                  ex_security_groups=[api_group])
instance_api_2 = conn.create_node(name='app-api-2',
                                  image=image,
                                  size=flavor,
                                  ex_keyname='demokey',
                                  ex_userdata=userdata,
                                  ex_security_groups=[api_group])
instance_api_1 = conn.wait_until_running([instance_api_1])[0][0]
api_1_ip = instance_api_1.private_ips[0]
instance_api_2 = conn.wait_until_running([instance_api_2])[0][0]
api_2_ip = instance_api_2.private_ips[0]

for instance in [instance_api_1,  instance_api_2]:
    floating_ip = get_floating_ip(conn)
    conn.ex_attach_floating_ip_to_node(instance, floating_ip)
    print('allocated %(ip)s to %(host)s' % {'ip': floating_ip.ip_address, 'host': instance.name})

# step-6
userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r worker -e 'http://%(api_1_ip)s' -m 'amqp://guest:guest@%(services_ip)s:5672/'
''' % {'api_1_ip': api_1_ip, 'services_ip': services_ip}
instance_worker_1 = conn.create_node(name='app-worker-1',
                                     image=image, size=flavor,
                                     ex_keyname='demokey',
                                     ex_userdata=userdata,
                                     ex_security_groups=[worker_group])
instance_worker_2 = conn.create_node(name='app-worker-2',
                                     image=image, size=flavor,
                                     ex_keyname='demokey',
                                     ex_userdata=userdata,
                                     ex_security_groups=[worker_group])
instance_worker_3 = conn.create_node(name='app-worker-3',
                                     image=image, size=flavor,
                                     ex_keyname='demokey',
                                     ex_userdata=userdata,
                                     ex_security_groups=[worker_group])

# step-7
