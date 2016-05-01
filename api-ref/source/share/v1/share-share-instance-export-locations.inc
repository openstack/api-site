.. -*- rst -*-

================================================
Share instance export locations (since API v2.9)
================================================

Set of APIs used to view export locations of share instances.

By default, these APIs are admin-only. Use the ``policy.json`` file
to grant permissions for these actions to other roles.

Lists all export locations for a share instance.

Show details of an export location belonging to a share instance.


List export locations
=====================

.. rest_method::  GET /v2/{tenant_id}/share_instances/{share_instance_id}/export_locations




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

   - path: path
   - share_instance_id: share_instance_id
   - is_admin_only: is_admin_only
   - id: id
   - preferred: preferred



Response Example
----------------

.. literalinclude:: ../samples/manila-export-location-list-response.json
   :language: javascript




Show single export location
===========================

.. rest_method::  GET /v2/{tenant_id}/share_instances/{share_instance_id}/export_locations/{export_location_id}




Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - export_location_id: export_location_id
   - tenant_id: tenant_id
   - share_instance_id: share_instance_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - created_at: created_at
   - updated_at: updated_at
   - preferred: preferred
   - is_admin_only: is_admin_only
   - share_instance_id: share_instance_id
   - path: path
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-export-location-show-response.json
   :language: javascript



