.. -*- rst -*-

=========================================
Ports binding extended attributes (ports)
=========================================

Lists, creates, shows information for, updates, and deletes ports.


Show port details
=================

.. rest_method::  GET /v2.0/ports/{port_id}

Shows details for a port.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - port_id: port_id




Response Example
----------------

.. literalinclude:: ../samples/ports/port-bind-show-response.json
   :language: javascript




Update port
===========

.. rest_method::  PUT /v2.0/ports/{port_id}

Updates a port.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - port_id: port_id

Request Example
---------------

.. literalinclude:: ../samples/ports/port-create-request.json
   :language: javascript





Response Example
----------------

.. literalinclude:: ../samples/ports/port-bind-create-update-response.json
   :language: javascript







Delete port
===========

.. rest_method::  DELETE /v2.0/ports/{port_id}

Deletes a port.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - port_id: port_id









List ports
==========

.. rest_method::  GET /v2.0/ports

Lists ports to which the tenant has access.


Normal response codes: 200
Error response codes:401,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/ports/ports-list-response.json
   :language: javascript





Create port
===========

.. rest_method::  POST /v2.0/ports

Creates a port on a network.

Error response codes:201,403,401,400,


Request
-------

.. rest_parameters:: parameters.yaml


Request Example
---------------

.. literalinclude:: ../samples/ports/port-create-request.json
   :language: javascript









