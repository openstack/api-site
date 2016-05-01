.. -*- rst -*-

========
Services
========

Lists services. Services include ``manila-share`` and ``manila-
scheduler`` and their binaries, hosts, availability zones, current
statuses, and states (``up`` or ``down``).

Administrators can also enable or disable a service.

For old microversions 1.0-2.6 replace URL part ``services`` with
``os-services``.


Disable service
===============

.. rest_method::  PUT /v2/{tenant_id}/services/disable

Disables a service.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - binary: binary
   - host: host
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-service-disable-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - disabled: disabled
   - binary: binary
   - host: host



Response Example
----------------

.. literalinclude:: ../samples/manila-service-disable-response.json
   :language: javascript




List services
=============

.. rest_method::  GET /v2/{tenant_id}/services

Lists all services.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - binary: binary
   - zone: zone
   - state: state
   - updated_at: updated_at
   - host: host
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-services-list-response.json
   :language: javascript




Enable service
==============

.. rest_method::  PUT /v2/{tenant_id}/services/enable

Enables a service.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - binary: binary
   - host: host
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-service-enable-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - disabled: disabled
   - binary: binary
   - host: host



Response Example
----------------

.. literalinclude:: ../samples/manila-service-enable-response.json
   :language: javascript



