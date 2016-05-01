.. -*- rst -*-

==========
Quota sets
==========

Provides quotas management support.

For old microversions 1.0-2.6 replace URL part ``quota-sets`` with
``os-quota-sets``.


Show default quotas
===================

.. rest_method::  GET /v2/{tenant_id}/quota-sets/{tenant_id}/defaults

Shows default quotas for a tenant.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - gigabytes: gigabytes
   - shares: shares
   - snapshot_gigabytes: snapshot_gigabytes
   - snapshots: snapshots
   - quota_set: quota_set
   - id: id
   - share_networks: share_networks



Response Example
----------------

.. literalinclude:: ../samples/manila-quota-show-response.json
   :language: javascript




Show quotas
===========

.. rest_method::  GET /v2/{tenant_id}/quota-sets/{tenant_id}

Shows quotas for a tenant.

If you specify the optional ``user_id`` query parameter, you get
the quotas for this user in the tenant. If you omit this parameter,
you get the quotas for the project.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - gigabytes: gigabytes
   - shares: shares
   - snapshot_gigabytes: snapshot_gigabytes
   - snapshots: snapshots
   - quota_set: quota_set
   - id: id
   - share_networks: share_networks



Response Example
----------------

.. literalinclude:: ../samples/manila-quota-show-response.json
   :language: javascript




Update quotas
=============

.. rest_method::  PUT /v2/{tenant_id}/quota-sets/{tenant_id}

Updates quotas for a tenant.

If you specify the optional ``user_id`` query parameter, you update
the quotas for this user in the tenant. If you omit this parameter,
you update the quotas for the project.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - force: force
   - gigabytes: gigabytes
   - snapshots: snapshots
   - snapshot_gigabytes: snapshot_gigabytes
   - shares: shares
   - share_networks: share_networks
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-quota-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - gigabytes: gigabytes
   - snapshots: snapshots
   - snapshot_gigabytes: snapshot_gigabytes
   - shares: shares
   - quota_set: quota_set
   - share_networks: share_networks



Response Example
----------------

.. literalinclude:: ../samples/manila-quota-update-response.json
   :language: javascript




Delete quotas
=============

.. rest_method::  DELETE /v2/{tenant_id}/quota-sets/{tenant_id}

Deletes quotas for a tenant. The quota reverts to the default quota.

If you specify the optional ``user_id`` query parameter, you delete
the quotas for this user in the tenant. If you omit this parameter,
you delete the quotas for the project.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id





