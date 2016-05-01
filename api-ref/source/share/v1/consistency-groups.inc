.. -*- rst -*-

===================================
Consistency groups (since API v2.4)
===================================

Consistency groups enable you to create snapshots at the exact same
point in time from multiple file system shares. For example, a
database might place its tables, logs, and configuration on
separate shares. To restore this database from a previous point in
time, it makes sense to restore the logs, tables, and configuration
together from the exact same point in time.

As an administrator, you can also reset the state of a consistency
group and force-delete a consistency group in any state. Use the
``policy.json`` file to grant permissions for these actions to
other roles.


List consistency groups with details
====================================

.. rest_method::  GET /v2/{tenant_id}/consistency-groups/detail

Lists all consistency groups with details.


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
   - description: description
   - source_cgsnapshot_id: source_cgsnapshot_id
   - consistency_group: consistency_group
   - created_at: created_at
   - share_network_id: share_network_id
   - host: host
   - link: link
   - project_id: project_id
   - share_types: share_types
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-consistency-groups-list-detailed-response.json
   :language: javascript




Show consistency group details
==============================

.. rest_method::  GET /v2/{tenant_id}/consistency-groups/{consistency_group_id}

Shows details for a consistency group.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - consistency_group_id: consistency_group_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - description: description
   - source_cgsnapshot_id: source_cgsnapshot_id
   - consistency_group: consistency_group
   - created_at: created_at
   - share_network_id: share_network_id
   - host: host
   - link: link
   - project_id: project_id
   - share_types: share_types
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-consistency-group-show-response.json
   :language: javascript




Update consistency group
========================

.. rest_method::  PUT /v2/{tenant_id}/consistency-groups/{consistency_group_id}

Updates a consistency group.

You can update only these attributes:

- ``name``, which changes the consistency group name.

- ``description``, which changes the consistency group description.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - description: description
   - name: name
   - tenant_id: tenant_id
   - consistency_group_id: consistency_group_id

Request Example
---------------

.. literalinclude:: ../samples/manila-consistency-group-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - description: description
   - source_cgsnapshot_id: source_cgsnapshot_id
   - consistency_group: consistency_group
   - created_at: created_at
   - share_network_id: share_network_id
   - host: host
   - link: link
   - project_id: project_id
   - share_types: share_types
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-consistency-group-update-response.json
   :language: javascript




Delete consistency group
========================

.. rest_method::  DELETE /v2/{tenant_id}/consistency-groups/{consistency_group_id}

Deletes a consistency group.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - consistency_group_id: consistency_group_id






Create consistency group
========================

.. rest_method::  POST /v2/{tenant_id}/consistency-groups

Creates a consistency group.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - source_cgsnapshot_id: source_cgsnapshot_id
   - share_types: share_types
   - description: description
   - share_network_id: share_network_id
   - name: name
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-consistency-group-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - description: description
   - source_cgsnapshot_id: source_cgsnapshot_id
   - consistency_group: consistency_group
   - created_at: created_at
   - share_network_id: share_network_id
   - host: host
   - link: link
   - project_id: project_id
   - share_types: share_types
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-consistency-group-create-response.json
   :language: javascript




List consistency groups
=======================

.. rest_method::  GET /v2/{tenant_id}/consistency-groups

Lists all consistency groups.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - consistency_groups: consistency_groups
   - link: link
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-consistency-groups-list-response.json
   :language: javascript




Reset consistency group state
=============================

.. rest_method::  POST /v2/{tenant_id}/consistency-groups/{consistency_group_id}/action

Administrator only. Explicitly updates the state of a consistency group.

Use the ``policy.json`` file to grant permissions for this action
to other roles.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - status: status
   - tenant_id: tenant_id
   - consistency_group_id: consistency_group_id

Request Example
---------------

.. literalinclude:: ../samples/manila-consistency-group-reset-state-request.json
   :language: javascript







Force-delete consistency group
==============================

.. rest_method::  POST /v2/{tenant_id}/consistency-groups/{consistency_group_id}/action

Administrator only. Force-deletes a consistency group.

Use the ``policy.json`` file to grant permissions for this action
to other roles.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - force_delete: force_delete
   - tenant_id: tenant_id
   - consistency_group_id: consistency_group_id

Request Example
---------------

.. literalinclude:: ../samples/manila-consistency-group-force-delete-request.json
   :language: javascript






