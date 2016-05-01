.. -*- rst -*-

=================
Service providers
=================

Lists service providers.


List service providers
======================

.. rest_method::  GET /v2.0/service-providers

Lists service providers and their associated service types.


Normal response codes: 200
Error response codes:404,409,401,400,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - default: default
   - service_type: service_type
   - service_providers: service_providers
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/service-type-response.json
   :language: javascript







