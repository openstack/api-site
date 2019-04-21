# step-1
import shade

conn = shade.openstack_cloud(cloud='myfavoriteopenstack')

# step-2
volume = conn.create_volume(size=1, display_name='test')

# step-3
volumes = conn.list_volumes()
for vol in volumes:
    print(vol)

# step-4
db_group = conn.create_security_group('database', 'for database service')
conn.create_security_group_rule(db_group['name'], 22, 22, 'TCP')
conn.create_security_group_rule(db_group['name'], 3306, 3306, 'TCP')

userdata = '''#!/usr/bin/env bash
curl -L -s https://opendev.org/openstack/faafo/raw/contrib/install.sh | bash -s -- \
    -i database -i messaging
'''

instance = conn.create_server(wait=True, auto_ip=False,
    name='app-database',
    image=image_id,
    flavor=flavor_id,
    key_name='demokey',
    security_groups=[db_group['name']],
    userdata=userdata)

# step-5
conn.attach_volume(instance, volume, '/dev/vdb')

# step-6
conn.detach_volume(instance, volume)
conn.delete_volume(volume['id'])
