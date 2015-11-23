# step-1
from libcloud.compute.types import Provider
from libcloud.compute.providers import get_driver

auth_username = 'your_auth_username'
auth_password = 'your_auth_password'
auth_url = 'http://controller:5000'
project_name = 'your_project_name_or_id'
region_name = 'your_region_name'

provider = get_driver(Provider.OPENSTACK)
connection = provider(auth_username,
                      auth_password,
                      ex_force_auth_url=auth_url,
                      ex_force_auth_version='2.0_password',
                      ex_tenant_name=project_name,
                      ex_force_service_region=region_name)

# step-2
volume = connection.create_volume(1, 'test')
print(volume)

# step-3
volumes = connection.list_volumes()
print(volumes)


# step-4
db_group = connection.ex_create_security_group('database', 'for database service')
connection.ex_create_security_group_rule(db_group, 'TCP', 3306, 3306)
instance = connection.create_node(name='app-database',
                                  image=image,
                                  size=flavor,
                                  ex_keyname=keypair_name,
                                  ex_security_groups=[db_group])

# step-5
volume = connection.ex_get_volume('755ab026-b5f2-4f53-b34a-6d082fb36689')
connection.attach_volume(instance, volume, '/dev/vdb')

# step-6
connection.detach_volume(volume)
connection.destroy_volume(volume)

# step-7
snapshot_name = 'test_backup_1'
connection.create_volume_snapshot('test', name=snapshot_name)

# step-8
