.. -*- rst -*-

============================================================================
Metadata definition objects (since API v2.0) (metadefs, namespaces, objects)
============================================================================

Creates, lists, shows details for, updates, and deletes metadata
definition objects.


Show object definition
======================

.. rest_method::  GET /v2/metadefs/namespaces/{namespace_id}/objects/{object_name}

Shows the definition for an object.

The response body shows a single object entity.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - object_name: object_name
   - namespace_id: namespace_id




Response Example
----------------

.. literalinclude:: ../samples/metadef-object-details-response.json
   :language: javascript




Update object definition
========================

.. rest_method::  PUT /v2/metadefs/namespaces/{namespace_id}/objects/{object_name}

Updates an object definition in a namespace.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - object_name: object_name
   - namespace_id: namespace_id

Request Example
---------------

.. literalinclude:: ../samples/metadef-object-update-request.json
   :language: javascript





Response Example
----------------

.. literalinclude:: ../samples/metadef-object-update-response.json
   :language: javascript




Delete property definition
==========================

.. rest_method::  DELETE /v2/metadefs/namespaces/{namespace_id}/objects/{object_name}

Deletes an object definition from a namespace.

To delete a protected object from a namespace, you must first set
the ``protected`` attribute to false (boolean) on the namespace and
then perform the delete. If you try to delete a protected object,
the call returns the ``403`` response code.

When you successfully delete an object from a namespace, the
response is empty and the response code is ``204``.

Error response codes:403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - object_name: object_name
   - namespace_id: namespace_id







Create object
=============

.. rest_method::  POST /v2/metadefs/namespaces/{namespace_id}/objects

Creates an object definition in a namespace.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml

   - display_name: display_name
   - description: description
   - objects: objects
   - namespace: namespace
   - visibility: visibility
   - protected: protected
   - resource_type_associations: resource_type_associations
   - properties: properties
   - namespace_id: namespace_id

Request Example
---------------

.. literalinclude:: ../samples/metadef-object-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - display_name: display_name
   - description: description
   - objects: objects
   - namespace: namespace
   - visibility: visibility
   - protected: protected
   - resource_type_associations: resource_type_associations
   - properties: properties





List object definitions
=======================

.. rest_method::  GET /v2/metadefs/namespaces/{namespace_id}/objects

Lists object definitions in a namespace.

Returns a subset of the larger collection of namespaces and a link
that you can use to get the next set of namespaces. You should
always check for the presence of a ``next`` link and use it as the
URI in a subsequent HTTP GET request. You should follow this
pattern until a ``next`` link is no longer provided. The next link
preserves any query parameters that you send in your initial
request. You can use the ``first`` link to jump back to the first
page of the collection. If you prefer to paginate through
namespaces manually, use the ``limit`` and ``marker`` parameters.

Use the ``resource_types`` and ``visibility`` query parameters to
filter the response.

For example, set the ``resource_types`` query parameter to
``OS::Glance::Image,OS::Nova::Flavor`` to filter the response to
include only namespaces that are associated with the given resource
types.

You can sort the results of this operation by using the
``sort_key`` and ``sort_dir`` parameters. The API uses the natural
sorting of whatever namespace attribute is provided as the
``sort_key``.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace_id: namespace_id
   - visibility: visibility
   - resource_types: resource_types
   - sort_key: sort_key
   - sort_dir: sort_dir


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - display_name: display_name
   - description: description
   - namespace: namespace
   - visibility: visibility
   - protected: protected
   - namespaces: namespaces
   - resource_type_associations: resource_type_associations



Response Example
----------------

.. literalinclude:: ../samples/metadef-objects-list-response.json
   :language: javascript



