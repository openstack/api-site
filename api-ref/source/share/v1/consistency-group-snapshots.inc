.. -*- rst -*-

============================================
Consistency group snapshots (since API v2.4)
============================================

You can create snapshots of consistency groups. To create a
snapshot, you specify the ID of the consistency group that you want
to snapshot. After you create a consistency group snapshot, you can
create a consistency group from it.

A consistency group snapshot can have member shares. To add a
member share, include the ``consistency_group_id`` parameter in the
create share request. This ID must match the ID of the consistency
group from which the consistency group snapshot was created. Then,
when you use consistency group snapshots to restore data, you can
easily determine which shares belong to a consistency group.

As an administrator, you can also reset the state of a consistency
group snapshot and force-delete a consistency group snapshot in any
state. Use the ``policy.json`` file to grant permissions for these
actions to other roles.


Show consistency group snapshot member
======================================

.. rest_method::  GET /v2/{tenant_id}/cgsnapshots/{cgsnapshot_id}/members

Shows information about a consistency group snapshot member.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - cgsnapshot_id: cgsnapshot_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - share_type_id: share_type_id
   - share_id: share_id
   - created_at: created_at
   - cgsnapshot_id: cgsnapshot_id
   - share_protocol: share_protocol
   - cgsnapshot_members: cgsnapshot_members
   - project_id: project_id
   - id: id
   - size: size



Response Example
----------------

.. literalinclude:: ../samples/manila-cg-snapshots-list-members-response.json
   :language: javascript




Show consistency group snapshot details
=======================================

.. rest_method::  GET /v2/{tenant_id}/cgsnapshots/{cgsnapshot_id}

Shows details for a consistency group snapshot.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - cgsnapshot_id: cgsnapshot_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - description: description
   - links: links
   - cgsnapshot: cgsnapshot
   - created_at: created_at
   - consistency_group_id: consistency_group_id
   - project_id: project_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-cg-snapshot-show-response.json
   :language: javascript




Update consistency group snapshot
=================================

.. rest_method::  PUT /v2/{tenant_id}/cgsnapshots/{cgsnapshot_id}

Updates a consistency group snapshot.

You can update only these attributes:

- ``name``, which changes the consistency group snapshot name.

- ``description``, which changes the consistency group snapshot
  description.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - description: description
   - name: name
   - tenant_id: tenant_id
   - cgsnapshot_id: cgsnapshot_id

Request Example
---------------

.. literalinclude:: ../samples/manila-cg-snapshot-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - description: description
   - links: links
   - cgsnapshot: cgsnapshot
   - created_at: created_at
   - consistency_group_id: consistency_group_id
   - project_id: project_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-cg-snapshot-update-response.json
   :language: javascript




Delete consistency group snapshot
=================================

.. rest_method::  DELETE /v2/{tenant_id}/cgsnapshots/{cgsnapshot_id}

Deletes a consistency group snapshot.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - cgsnapshot_id: cgsnapshot_id






List consistency group snapshots with details
=============================================

.. rest_method::  GET /v2/{tenant_id}/cgsnapshots/detail

Lists all consistency group snapshots with details.


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
   - links: links
   - created_at: created_at
   - consistency_group_id: consistency_group_id
   - project_id: project_id
   - id: id
   - cgsnapshots: cgsnapshots
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-cg-snapshots-list-detailed-response.json
   :language: javascript




Reset consistency group snapshot state
======================================

.. rest_method::  POST /v2/{tenant_id}/cgsnapshots/{cgsnapshot_id}/action

Administrator only. Explicitly updates the state of a consistency group snapshot.

Administrators can use the ``policy.json`` file to permit other
roles to complete this action.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - status: status
   - tenant_id: tenant_id
   - cgsnapshot_id: cgsnapshot_id

Request Example
---------------

.. literalinclude:: ../samples/manila-cg-snapshot-reset-state-request.json
   :language: javascript







Force-delete consistency group snapshot
=======================================

.. rest_method::  POST /v2/{tenant_id}/cgsnapshots/{cgsnapshot_id}/action

Administrator only. Force-deletes a consistency group snapshot.

Use the ``policy.json`` file to grant permissions for this action
to other roles.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - force_delete: force_delete
   - tenant_id: tenant_id
   - cgsnapshot_id: cgsnapshot_id

Request Example
---------------

.. literalinclude:: ../samples/manila-cg-snapshot-force-delete-request.json
   :language: javascript







Create consistency group snapshot
=================================

.. rest_method::  POST /v2/{tenant_id}/cgsnapshots

Creates a consistency group snapshot.

You can create a consistency group snapshot for a consistency group
in ``available`` state only.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - consistency_group_id: consistency_group_id
   - description: description
   - name: name
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-cg-snapshot-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - description: description
   - links: links
   - cgsnapshot: cgsnapshot
   - created_at: created_at
   - consistency_group_id: consistency_group_id
   - project_id: project_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-cg-snapshot-create-response.json
   :language: javascript




List consistency group snapshots
================================

.. rest_method::  GET /v2/{tenant_id}/cgsnapshots

Lists all consistency group snapshots.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - link: link
   - id: id
   - cgsnapshots: cgsnapshots
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-cg-snapshots-list-response.json
   :language: javascript



