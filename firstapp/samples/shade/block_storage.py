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
conn.create_security_group_rule(db_group['name'], 3306, 3306, 'TCP')

instance = conn.create_server(wait=True, auto_ip=False,
    name=name,
    image=image['id'],
    flavor=flavor['id'],
    security_groups=[db_group['name']])

# step-5
conn.attach_volume(instance, volume, '/dev/vdb')

# step-6
conn.detach_volume(instance, volume)
conn.delete_volume(volume['id'])

# step-7
# step-8
