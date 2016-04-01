#!/usr/bin/env ruby
require 'fog/openstack'

# step-1
auth_username = "your_auth_username"
auth_password = "your_auth_password"
auth_url      = "http://controller:5000"
project_name  = "your_project_name_or_id"

conn = Fog::Compute::OpenStack.new openstack_auth_url:     auth_url + "/v3/auth/tokens",
                                   openstack_domain_id:    "default",
                                   openstack_username:     auth_username,
                                   openstack_api_key:      auth_password,
                                   openstack_project_name: project_name

# step-2
volume = conn.volumes.create name:        "test",
                             description: "",
                             size:        1

p volume

# step-3
p conn.volumes.summary

# step-4
db_group = conn.security_groups.create name:        "database",
                                       description: "for database service"

conn.security_group_rules.create parent_group_id: db_group.id,
                                 ip_protocol:     "tcp",
                                 from_port:       3306,
                                 to_port:         3306

instance = conn.servers.create name:            "app-database",
                               image_ref:       image.id,
                               flavor_ref:      flavor.id,
                               key_name:        key_pair.name,
                               security_groups: db_group

Fog.wait_for { instance.ready? }

# step-5
volume = conn.volumes.get "755ab026-b5f2-4f53-b34a-6d082fb36689"
instance.attach_volume volume.id, "/dev/vdb"

# step-6
instance.detach_volume volume.id
volume.destroy

# step-7
conn.snapshots.create volume_id:   volume.id,
                      name:        "test_backup_1",
                      description: "test"

# step-8
