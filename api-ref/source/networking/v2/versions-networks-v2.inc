.. -*- rst -*-

============
API versions
============

Lists information for all Networking API versions.


Show API v2 details
===================

.. rest_method::  GET /v2.0

Shows details for Networking API v2.0.


Normal response codes: 200
Error response codes:203,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location



Response Example
----------------

.. literalinclude:: ../samples/networks/version-show-response.json
   :language: javascript





List API versions
=================

.. rest_method::  GET /

Lists information about all Networking API versions.


Normal response codes: 200
Error response codes:300,


Request
-------

.. rest_parameters:: parameters.yaml






Response Example
----------------

.. literalinclude:: ../samples/networks/versions-list-response.json
   :language: javascript



