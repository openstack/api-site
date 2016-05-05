.. -*- rst -*-

=============
Share actions
=============

Grants or revokes share access, lists the permissions for a share,
and explicitly updates the state of a share.

To grant or revoke share access, specify one of these supported
share access levels:

- ``rw``. Read and write (RW) access.

- ``ro``. Read-only (RO) access.

You must also specify one of these supported authentication
methods:

- ``ip``. Authenticates an instance through its IP address. A valid
  format is ``XX.XX.XX.XX`` or ``XX.XX.XX.XX/XX``. For example
  ``0.0.0.0/0``.

- ``cert``. Authenticates an instance through a TLS certificate.
  Specify the TLS identity as the IDENTKEY. A valid value is any
  string up to 64 characters long in the common name (CN) of the
  certificate. The meaning of a string depends on its
  interpretation.

- ``user``. Authenticates by a user or group name. A valid value is
  an alphanumeric string that can contain some special characters
  and is from 4 to 32 characters long.

To verify that the access rules (ACL) were configured correctly for
a share, you list permissions for a share.

As administrator, you can reset the state of a share and force-
delete a share in any state. Use the ``policy.json`` file to grant
permissions for this action to other roles.

You can set the state of a share to one of these supported states:

- ``available``

- ``error``

- ``creating``

- ``deleting``

- ``error_deleting``

If micro-version 1.0-2.6 is used then all share actions, defined
below, should include prefix ``os-`` in top element of request
JSON's body.

For example: {"access_list": null} is valid for v2.7+. And {"os-
access_list": null} is valid for v1.0-2.6


Grant access
============

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/action

Grants access to a share.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - allow_access: allow_access
   - access_level: access_level
   - access_type: access_type
   - access_to: access_to
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-actions-grant-access-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - share_id: share_id
   - created_at: created_at
   - updated_at: updated_at
   - access_type: access_type
   - access_to: access_to
   - access: access
   - access_level: access_level
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-actions-grant-access-response.json
   :language: javascript




Revoke access
=============

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/action

Revokes access from a share.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - os-deny_access: os-deny_access
   - access_id: access_id
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-actions-revoke-access-request.json
   :language: javascript







List access rules
=================

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/action

Lists access rules for a share.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - access_list: access_list
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-actions-list-access-rules-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - access_type: access_type
   - access_to: access_to
   - access_level: access_level
   - state: state
   - access_list: access_list
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-actions-list-access-rules-response.json
   :language: javascript




Reset share state
=================

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/action

Administrator only. Explicitly updates the state of a share.

Use the ``policy.json`` file to grant permissions for this action
to other roles.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - status: status
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-actions-reset-state-request.json
   :language: javascript







Force-delete share
==================

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/action

Administrator only. Force-deletes a share in any state.

Use the ``policy.json`` file to grant permissions for this action
to other roles.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - force_delete: force_delete
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-actions-force-delete-request.json
   :language: javascript







Extend share
============

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/action

Increases the size of a share.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - new_size: new_size
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-actions-extend-request.json
   :language: javascript







Shrink share
============

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/action

Shrinks the size of a share.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - new_size: new_size
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-actions-shrink-request.json
   :language: javascript







Unmanage share
==============

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/action

This API is available for micro-versions later than or equal to 2.7

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - unmanage: unmanage
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-actions-unmanage-request.json
   :language: javascript






