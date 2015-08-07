# step-1
userdata = '''#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -i messaging -r api -r worker -r demo
'''

instance_name = 'all-in-one'
testing_instance = conn.create_node(name=instance_name,
                                   image=image,
                                   size=flavor,
                                   ex_keyname=keypair_name,
                                   ex_userdata=userdata,
                                   ex_security_groups=[all_in_one_security_group])

# step-2
userdata = '''#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i messaging -i faafo -r api -r worker -r demo
'''

# step-3
all_in_one_security_group = conn.ex_create_security_group('all-in-one', 'network access for all-in-one application.')
conn.ex_create_security_group_rule(all_in_one_security_group, 'TCP', 80, 80)
conn.ex_create_security_group_rule(all_in_one_security_group, 'TCP', 22, 22)

# step-4
conn.ex_list_security_groups()

# step-5
conn.ex_delete_security_group_rule(rule)
conn.ex_delete_security_group(security_group)

# step-6
conn.ex_get_node_security_groups(testing_instance)

# step-7
unused_floating_ip = None
for floating_ip in conn.ex_list_floating_ips():
    if not floating_ip.node_id:
        unused_floating_ip = floating_ip
        print("Found an unused Floating IP: %s" % floating_ip)
        break

# step-8
pool = conn.ex_list_floating_ip_pools()[0]

# step-9
unused_floating_ip = pool.create_floating_ip()

# step-10
conn.ex_attach_floating_ip_to_node(instance, unused_floating_ip)

# step-11
worker_group = conn.ex_create_security_group('worker', 'for services that run on a worker node')
conn.ex_create_security_group_rule(worker_group, 'TCP', 22, 22)

controller_group = conn.ex_create_security_group('control', 'for services that run on a control node')
conn.ex_create_security_group_rule(controller_group, 'TCP', 22, 22)
conn.ex_create_security_group_rule(controller_group, 'TCP', 80, 80)
conn.ex_create_security_group_rule(controller_group, 'TCP', 5672, 5672, source_security_group=worker_group)

userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i messaging -i faafo -r api
'''

instance_controller_1 = conn.create_node(name='app-controller',
                                         image=image,
                                         size=flavor,
                                         ex_keyname='demokey',
                                         ex_userdata=userdata,
                                         ex_security_groups=[controller_group])

conn.wait_until_running([instance_controller_1])
print('Checking for unused Floating IP...')
unused_floating_ip = None
for floating_ip in conn.ex_list_floating_ips():
    if not floating_ip.node_id:
        unused_floating_ip = floating_ip
        break


if not unused_floating_ip:
    pool = conn.ex_list_floating_ip_pools()[0]
    print('Allocating new Floating IP from pool: {}'.format(pool))
    unused_floating_ip = pool.create_floating_ip()


conn.ex_attach_floating_ip_to_node(instance_controller_1, unused_floating_ip)
print('Application will be deployed to http://%s' % unused_floating_ip.ip_address)

# step-12
instance_controller_1 = conn.ex_get_node_details(instance_controller_1.id)
if instance_controller_1.public_ips:
    ip_controller = instance_controller_1.private_ips[0]
else:
    ip_controller = instance_controller_1.public_ips[0]

userdata = '''#!/usr/bin/env bash
curl -L -s http://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -r worker -e 'http://%(ip_controller)s' -m 'amqp://guest:guest@%(ip_controller)s:5672/'
''' % {'ip_controller': ip_controller}
instance_worker_1 = conn.create_node(name='app-worker-1',
                                        image=image,
                                        size=flavor,
                                        ex_keyname='demokey',
                                        ex_userdata=userdata,
                                        ex_security_groups=[worker_group])

conn.wait_until_running([instance_worker_1])
print('Checking for unused Floating IP...')
unused_floating_ip = None
for floating_ip in conn.ex_list_floating_ips():
    if not floating_ip.node_id:
        unused_floating_ip = floating_ip
        break


if not unused_floating_ip:
    pool = conn.ex_list_floating_ip_pools()[0]
    print('Allocating new Floating IP from pool: {}'.format(pool))
    unused_floating_ip = pool.create_floating_ip()


conn.ex_attach_floating_ip_to_node(instance_worker_1, unused_floating_ip)
print('The worker will be available for SSH at %s' % unused_floating_ip.ip_address)


# step-13
ip_instance_worker_1 = instance_worker_1.private_ips[0]
print(ip_instance_worker_1)

# step-14
