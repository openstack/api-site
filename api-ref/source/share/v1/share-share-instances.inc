.. -*- rst -*-

================================
Share instances (since API v2.3)
================================

Administrators can list, show information for, explicitly set the
state of, and force-delete share instances. Use the ``policy.json``
file to grant permissions for these actions to other roles.


List share instances
====================

.. rest_method::  GET /v2/{tenant_id}/share_instances

Lists all share instances.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - replica_state: replica_state
   - availability_zone: availability_zone
   - created_at: created_at
   - export_location: export_location
   - share_network_id: share_network_id
   - export_locations: export_locations
   - share_server_id: share_server_id
   - host: host
   - share_id: share_id
   - access_rules_status: access_rules_status
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-instances-list-response.json
   :language: javascript




Reset share instance state
==========================

.. rest_method::  POST /v2/{tenant_id}/share_instances/{share_instance_id}/action

Administrator only. Explicitly updates the state of a share instance.

Use the ``policy.json`` file to grant permissions for this action
to other roles.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - status: status
   - tenant_id: tenant_id
   - share_instance_id: share_instance_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-instance-actions-reset-state-request.json
   :language: javascript







Force-delete share instance
===========================

.. rest_method::  POST /v2/{tenant_id}/share_instances/{share_instance_id}/action

Administrator only. Force-deletes a share instance.

Use the ``policy.json`` file to grant permissions for this action
to other roles.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - force_delete: force_delete
   - tenant_id: tenant_id
   - share_instance_id: share_instance_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-instance-actions-force-delete-request.json
   :language: javascript







Show share instance details
===========================

.. rest_method::  GET /v2/{tenant_id}/share_instances/{share_instance_id}

Shows details for a share instance.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - share_instance_id: share_instance_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - replica_state: replica_state
   - availability_zone: availability_zone
   - created_at: created_at
   - export_location: export_location
   - share_network_id: share_network_id
   - export_locations: export_locations
   - share_server_id: share_server_id
   - host: host
   - share_id: share_id
   - access_rules_status: access_rules_status
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-show-instance-response.json
   :language: javascript



