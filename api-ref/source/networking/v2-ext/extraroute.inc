.. -*- rst -*-

======================
Extra routes (routers)
======================

Adds extra routes to the ``router`` resource.

You can update a router to add a set of next hop IPs and
destination CIDRs.

The next hop IP must be part of a subnet to which the router
interfaces are connected. You can configure the ``routes``
attribute on only update operations.


Update extra routes
===================

.. rest_method::  PUT /v2.0/routers/{router_id}

Updates extra routes on a router.

The next hop IP address must be a part of one of the subnets to
which the router interfaces are connected. Otherwise, the server
responds with the ``Bad Request (400)`` error code.

When a validation error is detected, such as a format error of IP
address or CIDR, the server responds with the ``Bad Request (400)``
response code.

When Networking receives a request to delete the router interface
for subnets that are used by one or more routes, it responds with a
``Conflict (409)`` response code.


Normal response codes: 200
Error response codes:404,409,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - external_gateway_info: external_gateway_info
   - destination: destination
   - nexthop: nexthop
   - routes: routes
   - router: router
   - external_fixed_ips: external_fixed_ips
   - router_id: router_id

Request Example
---------------

.. literalinclude:: ../samples/routers/router-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - external_gateway_info: external_gateway_info
   - status: status
   - enable_snat: enable_snat
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - routes: routes
   - router: router
   - id: id
   - external_fixed_ips: external_fixed_ips



Response Example
----------------

.. literalinclude:: ../samples/routers/router-update-response.json
   :language: javascript







