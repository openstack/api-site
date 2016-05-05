.. -*- rst -*-

============
Manage share
============

Configures Shared File Systems to manage or unmanage a share.

The share unmanage operation is not supported for shares that are
created on top of share servers (created with share networks).

You can unmanage a share that has no dependent snapshots.

These APIs are available for micro-versions 1.0-2.6

Starting with micro-version 2.7 these APIs are available under
'shares' API group.

Configures Shared File Systems to manage a share.


Unmanage share
==============

.. rest_method::  POST /v2/{tenant_id}/os-share-unmanage/{share_id}/unmanage

Configures Shared File Systems to stop managing a share.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - share_id: share_id
   - tenant_id: tenant_id






Manage share
============

.. rest_method::  POST /v2/{tenant_id}/os-share-manage




Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - protocol: protocol
   - description: description
   - share_type: share_type
   - share: share
   - driver_options: driver_options
   - is_public: is_public
   - export_path: export_path
   - service_host: service_host
   - name: name
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-manage-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - share_type_name: share_type_name
   - links: links
   - availability_zone: availability_zone
   - share: share
   - share_network_id: share_network_id
   - export_locations: export_locations
   - share_server_id: share_server_id
   - snapshot_id: snapshot_id
   - id: id
   - size: size
   - share_type: share_type
   - export_location: export_location
   - consistency_group_id: consistency_group_id
   - project_id: project_id
   - metadata: metadata
   - status: status
   - description: description
   - host: host
   - is_public: is_public
   - snapshot_support: snapshot_support
   - name: name
   - has_replicas: has_replicas
   - replication_type: replication_type
   - created_at: created_at
   - share_proto: share_proto
   - volume_type: volume_type
   - source_cgsnapshot_member_id: source_cgsnapshot_member_id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-manage-response.json
   :language: javascript



