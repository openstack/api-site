.. -*- rst -*-

======================================================================
Metadata definition namespaces (since API v2.0) (metadefs, namespaces)
======================================================================

Creates, lists, shows details for, updates, and deletes metadata
definition namespaces. Defines namespaces that can contain property
definitions, object definitions, and resource type associations.


Create namespace
================

.. rest_method::  POST /v2/metadefs/namespaces

Creates a namespace.

The ``Location`` response header contains the newly-created URI for
the namespace.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml


Request Example
---------------

.. literalinclude:: ../samples/metadef-namespace-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - display_name: display_name
   - description: description
   - hypervisor_type: hypervisor_type
   - enum: enum
   - namespace: namespace
   - visibility: visibility
   - objects: objects
   - protected: protected
   - resource_type_associations: resource_type_associations
   - properties: properties





List namespaces
===============

.. rest_method::  GET /v2/metadefs/namespaces

Lists public namespaces.

Returns a subset in the larger collection of namespaces and a link
that you can use to get the next set of namespaces. Check for the
presence of a ``next`` link and use it as the URI in a subsequent
HTTP GET request. Follow this pattern until a ``next`` link is no
longer provided. The ``next`` link preserves any query parameters
that you send in your initial request. You can use the ``first``
link to return to the first page in the collection. If you prefer
to paginate through namespaces manually, use the ``limit`` and
``marker`` parameters.

The list operation accepts the ``resource_types`` and
``visibility`` query parameters, which you can use to filter the
response.

To sort the results of this operation, use the ``sort_key`` and
``sort_dir`` parameters. The API uses the natural sorting order in
the namespace attribute that you provide as the ``sort_key``
parameter.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - limit: limit
   - marker: marker
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

.. literalinclude:: ../samples/metadef-namespaces-list-response.json
   :language: javascript




Get namespaces details
======================

.. rest_method::  GET /v2/metadefs/namespaces/{namespace_id}

Gets details for a namespace.

The response body shows a single namespace entity with all details
including properties and objects.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace_id: namespace_id




Response Example
----------------

.. literalinclude:: ../samples/metadef-namespace-details-response.json
   :language: javascript




Update namespace
================

.. rest_method::  PUT /v2/metadefs/namespaces/{namespace_id}

Updates a namespace.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace_id: namespace_id

Request Example
---------------

.. literalinclude:: ../samples/metadef-namespace-update-request.json
   :language: javascript





Response Example
----------------

.. literalinclude:: ../samples/metadef-namespace-update-response.json
   :language: javascript




Delete namespace
================

.. rest_method::  DELETE /v2/metadefs/namespaces/{namespace_id}

Deletes a namespace and its properties, objects, and any resource type associations.

You cannot delete namespaces with the ``protected`` attribute set
to ``true`` (boolean); the response returns the HTTP ``403``
response code.

To delete a namespace, you must first make an update namespace
request to set the ``protected`` attribute to false (boolean) on
the namespace. Then, delete the namespace.

A successful operation returns the HTTP ``204`` response code.

If you try to remove a namespace with the ``protected`` attribute
set to true (boolean), the operation fails and the response returns
the HTTP ``403`` response code.

Error response codes:403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace_id: namespace_id






