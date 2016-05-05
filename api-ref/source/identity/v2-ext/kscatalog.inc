.. -*- rst -*-

============================
OS-KSCATALOG admin extension
============================

Supports CRUD operations for endpoint templates and endpoints.
Requires administrator privileges.


Update endpoint template
========================

.. rest_method::  PUT /v2.0/OS-KSCATALOG/endpointTemplates/{endpointTemplateId}

Updates endpoint template.


Normal response codes: 200
Error response codes:413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - endpointTemplateId: endpointTemplateId

Request Example
---------------

.. literalinclude:: ../samples/OS-KSCATALOG/endpointTemplate-create-request.json
   :language: javascript





Response Example
----------------

.. literalinclude:: ../samples/OS-KSCATALOG/endpointTemplate-show-response.json
   :language: javascript













Delete endpoint template.
=========================

.. rest_method::  DELETE /v2.0/OS-KSCATALOG/endpointTemplates/{endpointTemplateId}

Deletes an endpoint template.

Error response codes:204,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - endpointTemplateId: endpointTemplateId















Create endpoint
===============

.. rest_method::  POST /v2.0/tenants/{tenantId}/OS-KSCATALOG/endpoints

Creates endpoint to a tenant.

Error response codes:201,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml


Request Example
---------------

.. literalinclude:: ../samples/OS-KSCATALOG/endpointTemplateWithOnlyId-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - Location: Location














List endpoints
==============

.. rest_method::  GET /v2.0/tenants/{tenantId}/OS-KSCATALOG/endpoints

Lists endpoints for a tenant.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/OS-KSCATALOG/endpoints-list-response.json
   :language: javascript












Get endpoint
============

.. rest_method::  GET /v2.0/tenants/{tenantId}/OS-KSCATALOG/endpoints

Gets endpoint for a tenant.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/OS-KSCATALOG/endpoint-show-response.json
   :language: javascript












List endpoint templates
=======================

.. rest_method::  GET /v2.0/OS-KSCATALOG/endpointTemplates

Lists endpoint templates.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/OS-KSCATALOG/endpointTemplates-list-response.json
   :language: javascript












Get endpoint template
=====================

.. rest_method::  GET /v2.0/OS-KSCATALOG/endpointTemplates

Gets endpoint templates.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/OS-KSCATALOG/endpointTemplate-show-response.json
   :language: javascript












Create endpoint template
========================

.. rest_method::  POST /v2.0/OS-KSCATALOG/endpointTemplates

Creates endpoint template.

Error response codes:201,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml


Request Example
---------------

.. literalinclude:: ../samples/OS-KSCATALOG/endpointTemplate-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - Location: Location














Delete endpoint
===============

.. rest_method::  DELETE /v2.0/tenants/{tenantId}/OS-KSCATALOG/endpoints/{endpointId}

Deletes an endpoint from a tenant.

Error response codes:204,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml















