.. -*- rst -*-

======
Shares
======

A share is a remote, mountable file system. You can mount a share
to and access a share from several hosts by several users at a
time.

You can create a share and associate it with a network, list
shares, and show information for, update, and delete a share.

To create a share, specify one of these supported protocols:

- ``NFS``. Network File System (NFS).

- ``CIFS``. Common Internet File System (CIFS).

- ``GLUSTERFS``. Gluster file system (GlusterFS).

- ``HDFS``. Hadoop Distributed File System (HDFS).

- ``CEPHFS``. Ceph File System (CephFS).

You can also create snapshots of shares. To create a snapshot, you
specify the ID of the share that you want to snapshot.

A share has one of these status values:

**Share statuses**

+----------------------------------------+--------------------------------------------------------+
| Status                                 | Description                                            |
+----------------------------------------+--------------------------------------------------------+
| ``creating``                           | The share is being created.                            |
+----------------------------------------+--------------------------------------------------------+
| ``deleting``                           | The share is being deleted.                            |
+----------------------------------------+--------------------------------------------------------+
| ``error``                              | An error occurred during share creation.               |
+----------------------------------------+--------------------------------------------------------+
| ``error_deleting``                     | An error occurred during share deletion.               |
+----------------------------------------+--------------------------------------------------------+
| ``available``                          | The share is ready to use.                             |
+----------------------------------------+--------------------------------------------------------+
| ``manage_starting``                    | Share manage started.                                  |
+----------------------------------------+--------------------------------------------------------+
| ``manage_error``                       | Share manage failed.                                   |
+----------------------------------------+--------------------------------------------------------+
| ``unmanage_starting``                  | Share unmanage started.                                |
+----------------------------------------+--------------------------------------------------------+
| ``unmanage_error``                     | Share cannot be unmanaged.                             |
+----------------------------------------+--------------------------------------------------------+
| ``unmanaged``                          | Share was unmanaged.                                   |
+----------------------------------------+--------------------------------------------------------+
| ``extending``                          | The extend, or increase, share size request was issued |
|                                        | successfully.                                          |
+----------------------------------------+--------------------------------------------------------+
| ``extending_error``                    | Extend share failed.                                   |
+----------------------------------------+--------------------------------------------------------+
| ``shrinking``                          | Share is being shrunk.                                 |
+----------------------------------------+--------------------------------------------------------+
| ``shrinking_error``                    | Failed to update quota on share shrinking.             |
+----------------------------------------+--------------------------------------------------------+
| ``shrinking_possible_data_loss_error`` | Shrink share failed due to possible data loss.         |
+----------------------------------------+--------------------------------------------------------+



Configures Shared File Systems to manage a share. This API is
available for micro-versions later than or equal to 2.7


List shares with details
========================

.. rest_method::  GET /v2/{tenant_id}/shares/detail

Lists all shares, with details.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - is_public: is_public
   - tenant_id: tenant_id
   - all_tenants: all_tenants
   - name: name
   - status: status
   - share_server_id: share_server_id
   - metadata: metadata
   - extra_specs: extra_specs
   - share_type_id: share_type_id
   - limit: limit
   - offset: offset
   - sort_key: sort_key
   - sort_dir: sort_dir
   - snapshot_id: snapshot_id
   - host: host
   - share_network_id: share_network_id
   - project_id: project_id
   - consistency_group_id: consistency_group_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - share_type_name: share_type_name
   - links: links
   - availability_zone: availability_zone
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
   - access_rules_status: access_rules_status
   - is_public: is_public
   - task_state: task_state
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

.. literalinclude:: ../samples/manila-shares-list-detailed-response.json
   :language: javascript




Create share
============

.. rest_method::  POST /v2/{tenant_id}/shares

Creates a share.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - display_name: display_name
   - description: description
   - share_type: share_type
   - availability_zone: availability_zone
   - share_proto: share_proto
   - display_description: display_description
   - name: name
   - consistency_group_id: consistency_group_id
   - share_network_id: share_network_id
   - snapshot_id: snapshot_id
   - is_public: is_public
   - size: size
   - volume_type: volume_type
   - metadata: metadata
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - share_type_name: share_type_name
   - links: links
   - availability_zone: availability_zone
   - share_network_id: share_network_id
   - export_locations: export_locations
   - share_server_id: share_server_id
   - snapshot_id: snapshot_id
   - id: id
   - size: size
   - display_name: display_name
   - share_type: share_type
   - export_location: export_location
   - display_description: display_description
   - consistency_group_id: consistency_group_id
   - project_id: project_id
   - metadata: metadata
   - status: status
   - description: description
   - host: host
   - is_public: is_public
   - task_state: task_state
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

.. literalinclude:: ../samples/manila-share-create-response.json
   :language: javascript




List shares
===========

.. rest_method::  GET /v2/{tenant_id}/shares

Lists all shares.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - is_public: is_public
   - tenant_id: tenant_id
   - all_tenants: all_tenants
   - name: name
   - status: status
   - share_server_id: share_server_id
   - metadata: metadata
   - extra_specs: extra_specs
   - share_type_id: share_type_id
   - limit: limit
   - offset: offset
   - sort_key: sort_key
   - sort_dir: sort_dir
   - snapshot_id: snapshot_id
   - host: host
   - share_network_id: share_network_id
   - project_id: project_id
   - consistency_group_id: consistency_group_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - id: id
   - links: links
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-shares-list-response.json
   :language: javascript




Show share details
==================

.. rest_method::  GET /v2/{tenant_id}/shares/{share_id}

Shows details for a share.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - share_id: share_id
   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - share_type_name: share_type_name
   - links: links
   - availability_zone: availability_zone
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
   - access_rules_status: access_rules_status
   - is_public: is_public
   - task_state: task_state
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

.. literalinclude:: ../samples/manila-share-show-response.json
   :language: javascript




Update share
============

.. rest_method::  PUT /v2/{tenant_id}/shares/{share_id}

Updates a share.

You can update these attributes:

- ``display_name``, which also changes the ``name`` of the share.

- ``display_description``, which also changes the ``description`` of
  the share.

- ``is_public``. Changes the level of visibility.

If you try to update other attributes, they retain their previous
values.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - is_public: is_public
   - display_name: display_name
   - display_description: display_description
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - share_type_name: share_type_name
   - links: links
   - availability_zone: availability_zone
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
   - access_rules_status: access_rules_status
   - is_public: is_public
   - task_state: task_state
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

.. literalinclude:: ../samples/manila-share-update-response.json
   :language: javascript




Delete share
============

.. rest_method::  DELETE /v2/{tenant_id}/shares/{share_id}

Deletes a share.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - share_id: share_id
   - tenant_id: tenant_id
   - consistency_group_id: consistency_group_id





