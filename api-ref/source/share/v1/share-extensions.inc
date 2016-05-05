.. -*- rst -*-

==============
API extensions
==============

Lists available Shared File Systems API extensions.


List extensions
===============

.. rest_method::  GET /v2/{tenant_id}/extensions

Lists all extensions.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - alias: alias
   - updated: updated
   - description: description
   - links: links
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-extensions-list-response.json
   :language: javascript



