.. -*- rst -*-

====================
Tag extension (tags)
====================

Shows details for, updates, and deletes tags. This extension is
available since Mitaka release.


Replace all tags
================

.. rest_method::  PUT /v2.0/{resource_type}/{resource_id}/tags

Replaces all tags on the resource.


Normal response codes: 200
Error response codes:404,401,400,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - tags: tags
   - resource_type: resource_type
   - resource_id: resource_id

Request Example
---------------

.. literalinclude:: ../samples/tag/tag-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - tags: tags



Response Example
----------------

.. literalinclude:: ../samples/tag/tag-update-response.json
   :language: javascript









Remove all tags
===============

.. rest_method::  DELETE /v2.0/{resource_type}/{resource_id}/tags

Removes all tags on the resource.

Error response codes:500,404,204,401,503,


Request
-------

.. rest_parameters:: parameters.yaml

   - resource_type: resource_type
   - resource_id: resource_id










Confirm a tag
=============

.. rest_method::  GET /v2.0/{resource_type}/{resource_id}/tags/{tag}

Confirms a given tag is set on the resource.

Error response codes:500,404,204,401,503,


Request
-------

.. rest_parameters:: parameters.yaml

   - tag: tag
   - resource_type: resource_type
   - resource_id: resource_id










Add a tag
=========

.. rest_method::  PUT /v2.0/{resource_type}/{resource_id}/tags/{tag}

Adds a tag on the resource.

Error response codes:201,404,500,401,503,


Request
-------

.. rest_parameters:: parameters.yaml

   - tag: tag
   - resource_type: resource_type
   - resource_id: resource_id










Remove a tag
============

.. rest_method::  DELETE /v2.0/{resource_type}/{resource_id}/tags/{tag}

Removes a tag on the resource.

Error response codes:500,404,204,401,503,


Request
-------

.. rest_parameters:: parameters.yaml

   - tag: tag
   - resource_type: resource_type
   - resource_id: resource_id









