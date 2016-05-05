.. -*- rst -*-

===========
Share types
===========

A share type enables you to filter or choose back ends before you
create a share. A share type behaves in the same way as a Block
Storage volume type behaves.

You set a share type to private or public and manage the access to
the private share types.

When you issue a create a share type request, you can submit a
request body with either a ``share_type`` or ``volume_type``
object. The use of the ``volume_type`` object is deprecated but
supported. It is recommended that you use the ``share_type`` object
when you create a share type.

No matter which object type you include in the request, the API
creates both a ``volume_type`` object and a ``share_type`` object.
Both objects have the same ID. When you issue a list share types
request, the response shows both ``share_types`` and
``volume_types`` objects.

You can set share types as either public or private. By default a
share type is created as publicly accessible. Set
``share_type_access:is_public`` (``os-share-type-access:is_public``
for micro-versions 1.0-2.6) to ``False`` to make the share type
private.

You can manage the access to the private share types for the
different projects. You can add access, remove access, and get
information about access for a private share type.

Administrators can create share types with these extra
specifications that are used to filter back ends:

- ``driver_handles_share_servers``. Required. Defines the driver
  mode for share server, or storage, life cycle management. The
  Shared File Systems service creates a share server for the export
  of shares.

  Set to ``True`` when the share driver manages, or handles, the
  share server life cycle.

  Set to ``False`` when an administrator rather than a share driver
  manages the storage life cycle.

- ``snapshot_support``. Filters back ends by whether they do or do
  not support share snapshots.

  Set to ``True`` to find back ends that support share snapshots.

  Set to ``False`` to find back ends that do not support share
  snapshots.

Administrators can also set additional extra specifications for a
share type for the following purposes:

- Filter back ends. Specify these unqualified extra specifications
  in this format: ``extra_spec=value``. For example,
  ``netapp_raid_type=raid4``.

- Set data for the driver. Except for the special ``capabilities``
  prefix, you specify these qualified extra specifications with its
  prefix followed by a colon: ``vendor:extra_spec=value``. For
  example, ``netapp:thin_provisioned=true``.

The scheduler uses the special ``capabilities`` prefix for
filtering. The scheduler can only create a share on a back end that
reports capabilities that match the unscoped extra-spec keys for
the share type. For details, see `Capabilities and Extra-Specs <htt
p://docs.openstack.org/developer/manila/devref/capabilities_and_ext
ra_specs.html>`_.

Each driver implementation determines which extra specification
keys it uses. For details, see the documentation for the driver.

An administrator can use the ``policy.json`` file to grant
permissions for share type creation with extra specifications to
other roles.


Unset an extra spec
===================

.. rest_method::  DELETE /v2/{tenant_id}/types/{share_type_id}/extra_specs/{key}

Unsets an extra specification for the share type.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - share_type_id: share_type_id
   - tenant_id: tenant_id






Delete share type
=================

.. rest_method::  DELETE /v2/{tenant_id}/types/{share_type_id}

Deletes a share type.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - share_type_id: share_type_id
   - tenant_id: tenant_id






Create share type
=================

.. rest_method::  POST /v2/{tenant_id}/types

Creates a share type.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - os-share-type-access:is_public: os-share-type-access:is_public
   - snapshot_support: snapshot_support
   - extra_specs: extra_specs
   - name: name
   - driver_handles_share_servers: driver_handles_share_servers
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-type-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - os-share-type-access:is_public: os-share-type-access:is_public
   - required_extra_specs: required_extra_specs
   - name: name
   - driver_handles_share_servers: driver_handles_share_servers
   - extra_specs: extra_specs
   - snapshot_support: snapshot_support
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-type-create-response.json
   :language: javascript




List share types
================

.. rest_method::  GET /v2/{tenant_id}/types

Lists all share types.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - os-share-type-access:is_public: os-share-type-access:is_public
   - required_extra_specs: required_extra_specs
   - name: name
   - driver_handles_share_servers: driver_handles_share_servers
   - extra_specs: extra_specs
   - snapshot_support: snapshot_support
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-types-list-response.json
   :language: javascript




Add share type access
=====================

.. rest_method::  POST /v2/{tenant_id}/types/{share_type_id}/action

Adds share type access for a project.

You can add access to private share types only.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - project: project
   - share_type_id: share_type_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-type-grant-access-request.json
   :language: javascript







Remove share type access
========================

.. rest_method::  POST /v2/{tenant_id}/types/{share_type_id}/action

Removes share type access from a project.

You can remove access from private share types only.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - project: project
   - share_type_id: share_type_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-type-revoke-access-request.json
   :language: javascript







Show share type access details
==============================

.. rest_method::  GET /v2/{tenant_id}/types/{share_type_id}/share_type_access

Shows access details for a share type.

You can view access details for private share types only.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - share_type_id: share_type_id
   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - share_type_id: share_type_id
   - project_id: project_id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-types-list-access-response.json
   :language: javascript




Set extra spec for share type
=============================

.. rest_method::  POST /v2/{tenant_id}/types/{share_type_id}/extra_specs

Sets an extra specification for the share type.

Each driver implementation determines which extra specification
keys it uses. For details, see `Capabilities and Extra-Specs <http:
//docs.openstack.org/developer/manila/devref/capabilities_and_extra
_specs.html>`_ and documentation for your driver.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - extra_specs: extra_specs
   - share_type_id: share_type_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-type-set-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - extra_specs: extra_specs



Response Example
----------------

.. literalinclude:: ../samples/manila-share-type-set-response.json
   :language: javascript




List extra specs
================

.. rest_method::  GET /v2/{tenant_id}/types/{share_type_id}/extra_specs

Lists the extra specifications for a share type.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - share_type_id: share_type_id
   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - snapshot_support: snapshot_support
   - extra_specs: extra_specs
   - driver_handles_share_servers: driver_handles_share_servers



Response Example
----------------

.. literalinclude:: ../samples/manila-share-types-extra-specs-list-response.json
   :language: javascript




List default share types
========================

.. rest_method::  GET /v2/{tenant_id}/types/default

Lists default share types.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - os-share-type-access:is_public: os-share-type-access:is_public
   - required_extra_specs: required_extra_specs
   - name: name
   - driver_handles_share_servers: driver_handles_share_servers
   - extra_specs: extra_specs
   - snapshot_support: snapshot_support
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-types-default-list-response.json
   :language: javascript



