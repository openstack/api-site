.. -*- rst -*-

======================================================================
Metadata definition tags (since API v2.0) (metadefs, namespaces, tags)
======================================================================

Creates, lists, shows details for, updates, and deletes metadata
definition tags.


Add tag definition
==================

.. rest_method::  POST /v2/metadefs/namespaces/tags/{namespace_id}/{tag_name}

Adds a tag to the list of namespace tag definitions.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tag_name: tag_name
   - namespace_id: namespace_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name



Response Example
----------------

.. literalinclude:: ../samples/metadef-tag-add-response.json
   :language: javascript




Get tag definition
==================

.. rest_method::  GET /v2/metadefs/namespaces/tags/{namespace_id}/{tag_name}

Gets a definition for a tag.

The response body shows a single tag entity.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tag_name: tag_name
   - namespace_id: namespace_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name



Response Example
----------------

.. literalinclude:: ../samples/metadef-tag-details-response.json
   :language: javascript




Update tag definition
=====================

.. rest_method::  PUT /v2/metadefs/namespaces/tags/{namespace_id}/{tag_name}

Renames a tag definition.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tag_name: tag_name
   - namespace_id: namespace_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name



Response Example
----------------

.. literalinclude:: ../samples/metadef-tag-update-response.json
   :language: javascript




Delete tag definition
=====================

.. rest_method::  DELETE /v2/metadefs/namespaces/tags/{namespace_id}/{tag_name}

Deletes a tag definition within a namespace.

You cannot delete tags in a namespace with the 'protected'
attribute set to true (boolean); the response returns the HTTP 403
status code.

You must first set the ``protected`` attribute to false (boolean)
on the namespace and then perform the delete. The response is empty
and returns the HTTP 204 status code.

Error response codes:403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - tag_name: tag_name
   - namespace_id: namespace_id







Create tags
===========

.. rest_method::  POST /v2/metadefs/namespaces/tags/{namespace_id}

Creates one or more tag definitions in a namespace.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace: namespace
   - name: name
   - tags: tags
   - namespace_id: namespace_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - tags: tags





List tags
=========

.. rest_method::  GET /v2/metadefs/namespaces/tags/{namespace_id}

Lists the tag definitions within a namespace.

To manually paginate through the list of tags, use the ``limit``
and ``marker`` parameters.

To sort the results of this operation use the ``sort_key`` and
``sort_dir`` parameters. The API uses the natural sort order of the
tag attribute of the ``sort_key`` parameter.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace: namespace
   - namespace_id: namespace_id
   - limit: limit
   - marker: marker
   - sort_key: sort_key
   - sort_dir: sort_dir


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - tags: tags



Response Example
----------------

.. literalinclude:: ../samples/metadef-tags-list-response.json
   :language: javascript




Delete all tag definitions
==========================

.. rest_method::  DELETE /v2/metadefs/namespaces/tags/{namespace_id}

Deletes all tag definitions within a namespace.

You cannot delete tags in a namespace with the 'protected'
attribute set to true (boolean); the response returns the HTTP 403
status code.

You must first set the ``protected`` attribute to false (boolean)
on the namespace and then perform the delete. The response is empty
and returns the HTTP 204 status code.

Error response codes:403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace: namespace
   - namespace_id: namespace_id






