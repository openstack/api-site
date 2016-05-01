.. -*- rst -*-

==========================================================================================
Metadata definition resource types (since API v2.0) (metadefs, namespaces, resource_types)
==========================================================================================

Lists resource types. Also, creates, lists, and removes resource
type associations in a namespace.


List resource types
===================

.. rest_method::  GET /v2/metadefs/resource_types

Lists all resource types.

You can assign metadata definition namespaces to these resource
types. See the metadata definition resource types section.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - created_at: created_at
   - name: name
   - updated_at: updated_at



Response Example
----------------

.. literalinclude:: ../samples/metadef-resource-types-list-response.json
   :language: javascript




Create resource type association
================================

.. rest_method::  POST /v2/metadefs/namespaces/{namespace_id}/resource_types

Creates a resource type association in a namespace.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml

   - prefix: prefix
   - properties_target: properties_target
   - name: name
   - namespace_id: namespace_id

Request Example
---------------

.. literalinclude:: ../samples/metadef-resource-type-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - created_at: created_at
   - prefix: prefix
   - properties_target: properties_target
   - name: name
   - updated_at: updated_at





List resource type associations
===============================

.. rest_method::  GET /v2/metadefs/namespaces/{namespace_id}/resource_types

Lists resource type associations in a namespace.

The response body lists resource type association entities.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace_id: namespace_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - created_at: created_at
   - name: name
   - updated_at: updated_at



Response Example
----------------

.. literalinclude:: ../samples/metadef-resource-types-list-response.json
   :language: javascript




Remove resource type association
================================

.. rest_method::  DELETE /v2/metadefs/namespaces/{namespace_id}/resource_types/{name}

Removes a resource type association in a namespace.

To remove an association, first make an update namespace request to
set the ``protected`` attribute to false (boolean) on the
namespace. Then, remove the association. If the operation succeeds,
the response returns the HTTP 204 status code.

If you try to remove resource type associations in a namespace with
the ``protected`` attribute set to true (boolean), the operation
fails and the response returns the HTTP 403 error code.

Error response codes:403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace_id: namespace_id
   - name: name






