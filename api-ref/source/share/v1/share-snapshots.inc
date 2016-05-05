.. -*- rst -*-

===============
Share snapshots
===============

Use the shared file service to make snapshots of shares. A share
snapshot is a point-in-time, read-only copy of the data that is
contained in a share. You can create, manage, update, and delete
share snapshots. After you create or manage a share snapshot, you
can create a share from it.

You can update a share snapshot to rename it, change its
description, or update its state to one of these supported states:

- ``available``

- ``error``

- ``creating``

- ``deleting``

- ``error_deleting``

- ``manage_starting``

- ``manage_error``

- ``unmanage_starting``

- ``unmanage_error``

As administrator, you can also reset the state of a snapshot and
force-delete a share snapshot in any state. Use the ``policy.json``
file to grant permissions for these actions to other roles.


Create share snapshot
=====================

.. rest_method::  POST /v2/{tenant_id}/snapshots

Creates a snapshot from a share.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - share_id: share_id
   - force: force
   - description: description
   - display_description: display_description
   - display_name: display_name
   - name: name
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-snapshot-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - share_id: share_id
   - description: description
   - created_at: created_at
   - share_proto: share_proto
   - provider_location: provider_location
   - share_size: share_size
   - size: size
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-snapshot-create-response.json
   :language: javascript




List share snapshots
====================

.. rest_method::  GET /v2/{tenant_id}/snapshots

Lists all share snapshots.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-snapshots-list-response.json
   :language: javascript




List share snapshots with details
=================================

.. rest_method::  GET /v2/{tenant_id}/snapshots/detail

Lists all share snapshots with details.


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
   - share_id: share_id
   - description: description
   - created_at: created_at
   - share_proto: share_proto
   - share_size: share_size
   - size: size
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-snapshots-list-detailed-response.json
   :language: javascript




Manage share snapshot
=====================

.. rest_method::  POST /v2/{tenant_id}/snapshots/manage

(Since API v2.12) Configures Shared File Systems to manage a share snapshot.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - share_id: share_id
   - display_name: display_name
   - description: description
   - provider_location: provider_location
   - driver_options: driver_options
   - display_description: display_description
   - name: name
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-snapshot-manage-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - share_id: share_id
   - description: description
   - created_at: created_at
   - share_proto: share_proto
   - provider_location: provider_location
   - share_size: share_size
   - size: size
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-snapshot-manage-response.json
   :language: javascript




Reset share snapshot state
==========================

.. rest_method::  POST /v2/{tenant_id}/snapshots/{snapshot_id}/action

Administrator only. Explicitly updates the state of a share snapshot.

Use the ``policy.json`` file to grant permissions for this action
to other roles.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - status: status
   - tenant_id: tenant_id
   - snapshot_id: snapshot_id

Request Example
---------------

.. literalinclude:: ../samples/manila-snapshot-actions-reset-state-request.json
   :language: javascript







Force-delete share snapshot
===========================

.. rest_method::  POST /v2/{tenant_id}/snapshots/{snapshot_id}/action

Administrator only. Force-deletes a share snapshot in any state.

Use the ``policy.json`` file to grant permissions for this action
to other roles.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - force_delete: force_delete
   - tenant_id: tenant_id
   - snapshot_id: snapshot_id

Request Example
---------------

.. literalinclude:: ../samples/manila-snapshot-actions-force-delete-request.json
   :language: javascript







Unmanage share snapshot
=======================

.. rest_method::  POST /v2/{tenant_id}/snapshots/{snapshot_id}/action

(Since API v2.12) Configures Shared File Systems to stop managing a share snapshot.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - unmanage: unmanage
   - tenant_id: tenant_id
   - snapshot_id: snapshot_id

Request Example
---------------

.. literalinclude:: ../samples/manila-snapshot-actions-unmanage-request.json
   :language: javascript







Show share snapshot details
===========================

.. rest_method::  GET /v2/{tenant_id}/snapshots/{snapshot_id}

Shows details for a share snapshot.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - snapshot_id: snapshot_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - share_id: share_id
   - description: description
   - created_at: created_at
   - share_proto: share_proto
   - share_size: share_size
   - size: size
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-snapshot-show-response.json
   :language: javascript




Update share snapshot
=====================

.. rest_method::  PUT /v2/{tenant_id}/snapshots/{snapshot_id}

Updates a share snapshot.

You can update these attributes:

- ``display_name``, which also changes the ``name`` of the share
  snapshot.

- ``display_description``, which also changes the ``description`` of
  the share snapshot.

- ``is_public``. Changes the level of visibility.

If you try to update other attributes, they retain their previous
values.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - display_name: display_name
   - display_description: display_description
   - tenant_id: tenant_id
   - snapshot_id: snapshot_id

Request Example
---------------

.. literalinclude:: ../samples/manila-snapshot-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - share_id: share_id
   - description: description
   - created_at: created_at
   - share_proto: share_proto
   - share_size: share_size
   - size: size
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-snapshot-update-response.json
   :language: javascript




Delete share snapshot
=====================

.. rest_method::  DELETE /v2/{tenant_id}/snapshots/{snapshot_id}

Deletes a share snapshot.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - snapshot_id: snapshot_id





