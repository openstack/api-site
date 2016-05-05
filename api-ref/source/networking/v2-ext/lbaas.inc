.. -*- rst -*-

==================================================================
LBaaS 1.0 (DEPRECATED) (lb, vips, health_monitors, pools, members)
==================================================================

The Load-Balancer-as-a-Service (LBaaS) v1.0 extension pairs with
the Networking v2.0 API to enable OpenStack tenants to manage load
balancers for their VMs. With this extension, you can load-balance
client traffic from one network to application services, such as
VMs, on the same network.

Use this extension to create and manage virtual IP addresses
(VIPs), pools, members of a pool, health monitors, and view status
of a resource.

**Load balancer statuses**

+----------------+--------------------------------------------------------------------+
| Status         | Description                                                        |
+----------------+--------------------------------------------------------------------+
| ACTIVE         | The resource is ready and active.                                  |
+----------------+--------------------------------------------------------------------+
| PENDING_CREATE | The resource is being created.                                     |
+----------------+--------------------------------------------------------------------+
| PENDING_UPDATE | The resource is being updated.                                     |
+----------------+--------------------------------------------------------------------+
| PENDING_DELETE | The resource is pending deletion.                                  |
+----------------+--------------------------------------------------------------------+
| INACTIVE       | The resource is not active.                                        |
+----------------+--------------------------------------------------------------------+
| ERROR          | An object within the service is not working. The ``error_details`` |
|                | attribute provides an explanation for the error, its cause, and    |
|                | possibly a solution.                                               |
+----------------+--------------------------------------------------------------------+


List members
============

.. rest_method::  GET /v2.0/lb/members

Lists members.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - weight: weight
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - pool_id: pool_id
   - members: members
   - address: address
   - protocol_port: protocol_port
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/members-list-response.json
   :language: javascript









Create a load balancer member
=============================

.. rest_method::  POST /v2.0/lb/members

Creates a load balancer member.

Error response codes:201,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - weight: weight
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - pool_id: pool_id
   - member: member
   - address: address
   - protocol_port: protocol_port

Request Example
---------------

.. literalinclude:: ../samples/lbaas/member-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - weight: weight
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - pool_id: pool_id
   - member: member
   - address: address
   - protocol_port: protocol_port
   - id: id










Show load balancer status tree
==============================

.. rest_method::  GET /v2.0/lbaas/loadbalancers/{loadbalancer_id}/statuses

Shows the status tree for a load balancer.

This operation returns a status tree for a load balancer object, by
load balancer ID. If you are not an administrative user and the
load balancer object does not belong to the tenant account, the API
returns the ``Forbidden (403)`` response code.

If the operation succeeds, the returned element is a status tree
that contains the load balancer and all provisioning and operating
statuses for its children.


Normal response codes: 200
Error response codes:403,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - provisioning_status: provisioning_status
   - listeners: listeners
   - healthmonitor: healthmonitor
   - members: members
   - pools: pools
   - id: id
   - operating_status: operating_status



Response Example
----------------

.. literalinclude:: ../samples/lbaas/loadbalancer-status-tree.json
   :language: javascript









Show listener details
=====================

.. rest_method::  GET /v2.0/lbaas/listeners/{listener_id}

Shows details for a listener.

This operation returns a listener object, by ID. If you are not an
administrative user and the listener object does not belong to your
account, the API returns the HTTP ``Forbidden (403)`` response
code.

Example: Show listener details


Normal response codes: 200
Error response codes:404,403,500,401,413,503,409,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - protocol_port: protocol_port
   - protocol: protocol
   - description: description
   - default_tls_container_ref: default_tls_container_ref
   - admin_state_up: admin_state_up
   - loadbalancers: loadbalancers
   - tenant_id: tenant_id
   - sni_container_refs: sni_container_refs
   - connection_limit: connection_limit
   - listener: listener
   - default_pool_id: default_pool_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/listener-show-response.json
   :language: javascript











Update listener
===============

.. rest_method::  PUT /v2.0/lbaas/listeners/{listener_id}

Updates a listener.

This operation updates the attributes of a listener. Upon
successful validation of the request, the service returns the HTTP
``Accepted (202)`` response code.

Note: You cannot update the ``listener_id``, ``tenant_id``,
``loadbalancer_id``, ``loadbalancers``, ``default_pool_id``,
``protocol``, and ``protocol_port`` attributes. Attempting to
update an immutable attribute results in the HTTP ``Immutable
(422)`` response code.

Note: You cannot update a listener if the load balancer to which
the listener is attached does not have an ``ACTIVE`` provisioning
status.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - protocol_port: protocol_port
   - protocol: protocol
   - description: description
   - default_tls_container_ref: default_tls_container_ref
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - sni_container_refs: sni_container_refs
   - connection_limit: connection_limit
   - listener: listener
   - default_pool_id: default_pool_id
   - loadbalancer_id: loadbalancer_id
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/lbaas/listener-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - protocol_port: protocol_port
   - protocol: protocol
   - description: description
   - default_tls_container_ref: default_tls_container_ref
   - admin_state_up: admin_state_up
   - loadbalancers: loadbalancers
   - tenant_id: tenant_id
   - sni_container_refs: sni_container_refs
   - connection_limit: connection_limit
   - listener: listener
   - default_pool_id: default_pool_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/listener-update-response.json
   :language: javascript









Remove listener
===============

.. rest_method::  DELETE /v2.0/lbaas/listeners/{listener_id}

Removes a listener.

This operation removes a listener and its associated configuration
from the tenant account. The API immediately purges any and all
configuration data. You cannot recover it.

You cannot delete a listener if the load balancer to which it is
attached does not have an ``ACTIVE`` provisioning status.

Example: Delete a listener

Error response codes:204,400,409,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml













Show health monitor details
===========================

.. rest_method::  GET /v2.0/lbaas/health_monitors/{health_monitor_id}

Shows details for a health monitor.

This operation returns a health monitor object, by health monitor
ID. If you are not an administrative user and the health monitor
object does not belong to your tenant account, the service returns
the HTTP ``Forbidden (403)`` response code.

Example: Show health monitor details


Normal response codes: 200
Error response codes:404,403,500,401,413,503,409,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - pools: pools
   - url_path: url_path
   - type: type
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/healthmonitor-show-response.json
   :language: javascript











Update health monitor
=====================

.. rest_method::  PUT /v2.0/lbaas/health_monitors/{health_monitor_id}

Updates a health monitor.

Upon successful validation of the request, the service returns the
HTTP ``Accepted (202)`` response code.

Note: The health monitor UUID, ``tenant_id``, ``pool_id``, and type
are immutable attributes and cannot be updated. If you specify an
unsupported attribute, the service returns the HTTP ``Immutable
(422)`` response code.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - url_path: url_path

Request Example
---------------

.. literalinclude:: ../samples/lbaas/healthmonitor-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - pools: pools
   - url_path: url_path
   - type: type
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/healthmonitor-update-response.json
   :language: javascript









Remove health monitor
=====================

.. rest_method::  DELETE /v2.0/lbaas/health_monitors/{health_monitor_id}

Removes a health monitor and its associated configuration from the tenant account.

The API immediately purges any and all configuration data. You
cannot recover it.

You cannot delete a health monitor if the attached load balancer
does not have an ``ACTIVE`` provisioning status.

Example: Delete a health monitor

Error response codes:204,400,409,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml













Show member details
===================

.. rest_method::  GET /v2.0/lb/members/{member_id}

Shows details for a member.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - member_id: member_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - weight: weight
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - pool_id: pool_id
   - member: member
   - address: address
   - protocol_port: protocol_port
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/member-show-response.json
   :language: javascript









Update member
=============

.. rest_method::  PUT /v2.0/lb/members/{member_id}

Updates a load balancer member.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - member: member
   - pool_id: pool_id
   - weight: weight
   - admin_state_up: admin_state_up
   - member_id: member_id

Request Example
---------------

.. literalinclude:: ../samples/lbaas/member-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - weight: weight
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - pool_id: pool_id
   - member: member
   - address: address
   - protocol_port: protocol_port
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/member-update-response.json
   :language: javascript









Delete member
=============

.. rest_method::  DELETE /v2.0/lb/members/{member_id}

Deletes a load balancer member.

Error response codes:204,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - member_id: member_id











Show pool member details
========================

.. rest_method::  GET /v2.0/lbaas/pools/{pool_id}/members/{member_id}

Shows details for a pool member.

This operation returns a member object identified by ``member_id``
that belongs to a pool object identified by ``pool_id``. If you are
not an administrative user and the pool or member object does not
belong to your tenant account, the service returns the HTTP
``Forbidden (403)`` response code.

If this operation succeeds, it returns a pool element.

Example: Show pool member details


Normal response codes: 200
Error response codes:404,403,500,401,413,503,409,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - weight: weight
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - pool_id: pool_id
   - member: member
   - address: address
   - protocol_port: protocol_port
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/member-show-response.json
   :language: javascript











Update pool member
==================

.. rest_method::  PUT /v2.0/lbaas/pools/{pool_id}/members/{member_id}

Updates attributes for a pool member.

Upon successful validation of the request, the service returns the
HTTP ``OK (200)`` response code.

Note: You cannot update the member UUID, ``tenant_id``,
``address``, ``protocol_port``, and ``subnet_id`` attributes. If
you attempt to update any of these attributes, the service returns
the HTTP ``Immutable (422)`` response code.

Note: You cannot update a member if the attached load balancer does
not have an ``ACTIVE`` provisioning status.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - member: member
   - pool_id: pool_id
   - weight: weight
   - admin_state_up: admin_state_up

Request Example
---------------

.. literalinclude:: ../samples/lbaas/member-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - weight: weight
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - pool_id: pool_id
   - member: member
   - address: address
   - protocol_port: protocol_port
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/member-update-response.json
   :language: javascript









Remove member from pool
=======================

.. rest_method::  DELETE /v2.0/lbaas/pools/{pool_id}/members/{member_id}

Removes a member from a pool and its associated configuration from the tenant account.

The API immediately purges any and all configuration data. You
cannot recover it.

You cannot delete a member if the attached load balancer does not
have an ``ACTIVE`` provisioning status.

Example: Remove a member from a pool

Error response codes:204,400,409,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml













Add member to pool
==================

.. rest_method::  POST /v2.0/lbaas/pools/{pool_id}/members

Adds a member to a pool.

This operation provisions a member and adds it to a pool by using
the configuration that you define in the request object. After the
API validates the request and starts the provisioning process, it
returns a response object, which contains a unique ID.

At a minimum, you must specify these pool attributes:

- ``tenant_id``. Admin only. Required to create a pool for another
  tenant.

- ``address``. The IP address of the member to receive traffic from
  the load balancer.

- ``protocol_port`` The port on which the member listens for
  traffic.

Some attributes receive default values if you omit them from the
request:

- ``admin_state_up``. Default is ``true``.

- ``weight``. Default is ``1``.

If you omit the ``subnet_id`` parameter, LBaaS uses the
``vip_subnet_id`` parameter value for the subnet UUID.

If the request fails due to incorrect data, the service returns the
HTTP ``Bad Request (400)`` response code with information about the
failure in the response body. Validation errors require that you
correct the error and submit the request again.

To configure all documented member features at creation time,
specify additional elements or attributes in the request.

Administrative users can specify a tenant ID that is different than
their own to create members for other tenants.

To update a member, the load balancer must have an ``ACTIVE``
provisioning status.

Error response codes:201,404,409,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - member: member
   - subnet_id: subnet_id
   - protocol_port: protocol_port
   - tenant_id: tenant_id
   - address: address

Request Example
---------------

.. literalinclude:: ../samples/lbaas/member-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - weight: weight
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - member: member
   - address: address
   - protocol_port: protocol_port
   - id: id











List pool members
=================

.. rest_method::  GET /v2.0/lbaas/pools/{pool_id}/members

Lists members of a pool.

Lists all members that are associated with a pool that is
associated with your tenant account. The list of members includes
only members that belong to the pool object identified by
``pool_id``.

The list might be empty.

Example: List pool members


Normal response codes: 200
Error response codes:500,401,503,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - weight: weight
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - pool_id: pool_id
   - members: members
   - address: address
   - protocol_port: protocol_port
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/pool-members-list-response.json
   :language: javascript







Show load balancer details
==========================

.. rest_method::  GET /v2.0/lbaas/loadbalancers/{loadbalancer_id}

Shows details for a load balancer.

This operation returns a load balancer object, by ID. If you are
not an administrative user and the load balancer object does not
belong to your tenant account, the service returns the HTTP
``Forbidden (403)`` response code.


Normal response codes: 200
Error response codes:404,403,500,401,413,503,409,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - provisioning_status: provisioning_status
   - listeners: listeners
   - vip_address: vip_address
   - operating_status: operating_status
   - provider: provider
   - vip_subnet_id: vip_subnet_id
   - flavor: flavor
   - id: id
   - loadbalancer: loadbalancer
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/loadbalancer-show-response.json
   :language: javascript











Update load balancer
====================

.. rest_method::  PUT /v2.0/lbaas/loadbalancers/{loadbalancer_id}

Updates a load balancer.

If the request is valid, the service returns the ``Accepted (202)``
response code. To confirm the update, check that the load balancer
provisioning status is ``ACTIVE``. If the status is
``PENDING_UPDATE``, use a GET operation to poll the load balancer
object for changes.

This operation returns the updated load balancer object with the
``ACTIVE``, ``PENDING_UPDATE``, or ``ERROR`` provisioning status.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name
   - description: description
   - loadbalancer: loadbalancer
   - admin_state_up: admin_state_up

Request Example
---------------

.. literalinclude:: ../samples/lbaas/loadbalancer-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - provisioning_status: provisioning_status
   - listeners: listeners
   - vip_address: vip_address
   - operating_status: operating_status
   - provider: provider
   - vip_subnet_id: vip_subnet_id
   - flavor: flavor
   - id: id
   - loadbalancer: loadbalancer
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/loadbalancer-update-response.json
   :language: javascript









Remove load balancer
====================

.. rest_method::  DELETE /v2.0/lbaas/loadbalancers/{loadbalancer_id}

Removes a load balancer and its associated configuration from the tenant account.

The API immediately purges any and all configuration data. You
cannot recover it.

Example: Delete a load balancer

Error response codes:204,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml












Show VIP details
================

.. rest_method::  GET /v2.0/lb/vips/{vip_id}

Shows details for a VIP.


Normal response codes: 200
Error response codes:404,403,500,401,413,503,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - vip_id: vip_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - protocol: protocol
   - description: description
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - connection_limit: connection_limit
   - pool_id: pool_id
   - session_persistence: session_persistence
   - vip: vip
   - address: address
   - protocol_port: protocol_port
   - port_id: port_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/vip-show-response.json
   :language: javascript











Update VIP
==========

.. rest_method::  PUT /v2.0/lb/vips/{vip_id}

Updates a load balancer VIP.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - description: description
   - admin_state_up: admin_state_up
   - connection_limit: connection_limit
   - pool_id: pool_id
   - session_persistence: session_persistence
   - vip: vip
   - name: name
   - vip_id: vip_id

Request Example
---------------

.. literalinclude:: ../samples/lbaas/vip-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - protocol: protocol
   - description: description
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - connection_limit: connection_limit
   - pool_id: pool_id
   - session_persistence: session_persistence
   - vip: vip
   - address: address
   - protocol_port: protocol_port
   - port_id: port_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/vip-update-response.json
   :language: javascript









Delete VIP
==========

.. rest_method::  DELETE /v2.0/lb/vips/{vip_id}

Deletes a load balancer VIP.

Error response codes:204,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - vip_id: vip_id











List load balancers
===================

.. rest_method::  GET /v2.0/lbaas/loadbalancers

Lists all load balancers for the tenant account.

The list might be empty.


Normal response codes: 200
Error response codes:404,500,401,503,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - admin_state_up: admin_state_up
   - loadbalancers: loadbalancers
   - tenant_id: tenant_id
   - provisioning_status: provisioning_status
   - listeners: listeners
   - vip_address: vip_address
   - provider: provider
   - vip_subnet_id: vip_subnet_id
   - flavor: flavor
   - id: id
   - operating_status: operating_status
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/loadbalancers-list-response.json
   :language: javascript








Create load balancer
====================

.. rest_method::  POST /v2.0/lbaas/loadbalancers

Creates a load balancer.

This operation provisions a new load balancer by using the
configuration that you define in the request object. After the API
validates the request and starts the provisioning process, the API
returns a response object that contains a unique ID and the status
of provisioning the load balancer.

In the response, the load balancer provisioning status is
``ACTIVE``, ``PENDING_CREATE``, or ``ERROR``.

If the status is ``PENDING_CREATE``, issue GET
``/lbaas/loadbalancers/loadbalancer_id`` to view the progress of
the provisioning operation. When the load balancer status changes
to ``ACTIVE``, the load balancer is successfully provisioned and
operational for traffic handling.

If the API cannot fulfill the request due to insufficient data or
data that is not valid, the service returns the HTTP ``Bad Request
(400)`` response code with information about the failure in the
response body. Validation errors require that you correct the error
and submit the request again.

You can configure all documented features of the load balancer at
creation time by specifying the additional elements or attributes
in the request.

Administrative users can specify a tenant ID that is different than
their own to create load balancers for other tenants.

**Example: Create a load balancer**

- ``tenant_id``. Admin only. Required to create a load balancer for
  another tenant.

- ``vip_subnet_id``. The network on which to allocate the VIP
  address for the load balancer. A tenant can only create load
  balancer VIPs on networks that the policy authorizes, such as her
  own networks or shared or provider networks.

Some attributes receive default values if you omit them from the
request:

- ``admin_state_up``. Default is ``true``.

- ``name``. Default is an empty string.

- ``description``. Default is an empty string.

If the API cannot fulfill the request due to insufficient data or
data that is not valid, the service returns the HTTP ``Bad Request
(400)`` response code with information about the failure in the
response body. Validation errors require that you correct the error
and submit the request again.

You can configure all documented features of the load balancer at
creation time by specifying the additional elements or attributes
in the request.

Administrative users can specify a tenant ID that is different than
their own to create load balancers for other tenants.

If you own the subnet where you want to create the load balancer
VIP, you can specify a ``vip_address`` attribute. If you omit the
``vip_address`` attribute from the payload, the LBaaS service
allocates a VIP address from the subnet of the load balancer VIP.

An optional ``flavor`` attribute can be passed to enable dynamic
selection of an appropriate provider if configured by the operator.
The basic selection algorithm chooses the provider in the first
service profile currently associated with flavor.

You can also specify the ``provider`` attribute when you create a
load balancer. You can set this attribute to any service provider
with a ``LOADBALANCER`` service type. Setting both a flavor and a
provider will result in a conflict error.

Example: Create a load balancer

Error response codes:201,404,409,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - description: description
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - vip_address: vip_address
   - provider: provider
   - vip_subnet_id: vip_subnet_id
   - flavor: flavor
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/lbaas/loadbalancer-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - provisioning_status: provisioning_status
   - listeners: listeners
   - vip_address: vip_address
   - operating_status: operating_status
   - provider: provider
   - vip_subnet_id: vip_subnet_id
   - flavor: flavor
   - id: id
   - loadbalancer: loadbalancer
   - name: name











Associate health monitor with pool
==================================

.. rest_method::  POST /v2.0/lb/pools/{pool_id}/health_monitors

Associates a health monitor with a pool.

Error response codes:201,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - id: id
   - health_monitor: health_monitor
   - pool_id: pool_id

Request Example
---------------

.. literalinclude:: ../samples/lbaas/healthmonitor-associate-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor










Show pool details
=================

.. rest_method::  GET /v2.0/lbaas/pools/{pool_id}

Shows details for a pool.

This operation shows details for a pool, by ID. If you are not an
administrative user and the pool object does not belong to your
tenant account, the call returns the HTTP ``Forbidden (403)``
response code.

If this operation succeeds, it returns a ``pool`` element.

Example: Show pool details


Normal response codes: 200
Error response codes:404,403,500,401,413,503,409,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - lb_method: lb_method
   - protocol: protocol
   - description: description
   - health_monitors: health_monitors
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - vip_id: vip_id
   - members: members
   - pools: pools
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/pool-show-response.json
   :language: javascript











Update pool
===========

.. rest_method::  PUT /v2.0/lbaas/pools/{pool_id}

Updates a pool.

This operation updates the attributes of a pool. Upon successful
validation of the request, the service returns the HTTP ``Accepted
(202)`` response code.

Note: You cannot update the pool UUID, ``tenant_id``,
``listener_id``, ``listeners``, ``health_monitor_id``,
``protocol``, and ``members`` immutable attributes. If you try to
update any of these attributes, the service returns the HTTP
``Immutable (422)`` response code.

Note: You cannot update a pool if the load balancer to which it is
attached does not have an ``ACTIVE`` provisioning status.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - pool: pool
   - lb_method: lb_method
   - description: description
   - name: name
   - admin_state_up: admin_state_up

Request Example
---------------

.. literalinclude:: ../samples/lbaas/pool-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - lb_method: lb_method
   - protocol: protocol
   - description: description
   - health_monitors: health_monitors
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - vip_id: vip_id
   - members: members
   - pools: pools
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/pool-update-response.json
   :language: javascript









Remove pool
===========

.. rest_method::  DELETE /v2.0/lbaas/pools/{pool_id}

Removes a pool.

This operation removes a pool and its associated configuration from
the tenant account. The API immediately purges any and all
configuration data. You cannot recover it.

You cannot delete a pool if the load balancer to which it is
attached does not have an ``ACTIVE`` provisioning status.

Error response codes:204,400,409,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml













Create health monitor
=====================

.. rest_method::  POST /v2.0/lbaas/health_monitors

Creates a health monitor.

This operation provisions a health monitor by using the
configuration that you define in the request object. After the API
validates the request and start the provisioning process, it
returns a response object. The object contains a unique identifier.

At a minimum, you must specify these health monitor attributes:

- ``tenant_id``. Admin only. Required to create a health monitor for
  another tenant.

- ``type``. The type of health monitor. A valid value is ``TCP``,
  ``HTTP``, or ``HTTPS``.

- ``delay``. The interval, in seconds, between health checks.

- ``timeout``. The time, in seconds, after which a health check
  times out.

- ``max_retries``. Number of failed health checks before marked as
  OFFLINE.

- ``pool_id``. The pool to monitor.

Some attributes receive default values if you omit them from the
request, and are only useful when you specify a health monitor type
of HTTP(S):

- ``http_method``. Default is ``GET``.

- ``url_path``. Default is ``/``.

- ``expected_codes``. The expected HTTP status codes to get from a
  successful health check. Default is ``200``.

- ``admin_state_up``. Default is ``true``.

If the API cannot fulfill the request due to insufficient data or
data that is not valid, it returns the ``Bad Request (400)``
response code with information about the nature of the failure in
the response body. Failures in the validation process are non-
recoverable and require that you correct the cause of the failure
and submit the request again.

You can configure all documented features of the health monitor at
creation time by specifying the additional elements or attributes
in the request.

Administrative users can specify a tenant ID that is different than
their own to create health monitors for other tenants.

To update a health monitor, the load balancer to which to attach
must have an ``ACTIVE`` provisioning status.

Error response codes:201,404,409,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - url_path: url_path
   - type: type

Request Example
---------------

.. literalinclude:: ../samples/lbaas/healthmonitor-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - pools: pools
   - url_path: url_path
   - type: type
   - id: id











List health monitors
====================

.. rest_method::  GET /v2.0/lbaas/health_monitors

Lists health monitors.

This operation lists all health monitors that are associated with
your tenant account.

This operation returns a list, which might be empty.


Normal response codes: 200
Error response codes:500,401,503,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - health_monitors: health_monitors
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - pools: pools
   - url_path: url_path
   - type: type
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/healthmonitors-list-response.json
   :language: javascript







Create listener
===============

.. rest_method::  POST /v2.0/lbaas/listeners

Creates a listener.

This operation provisions a new listener by using the configuration
that you define in the request object. After the request is
validated and the provisioning process begins, a response object is
returned. The object contains a unique identifier.

At a minimum, you must specify these listener attributes:

- ``tenant_id``. Admin only. Required to create a listener for
  another tenant.

- ``loadbalancer_id``. The load balancer on which to provision this
  listener. A tenant can only create listeners on load balancers
  that the policy authorizes. For example, her own load balancers.

- ``description``. The load balancer description.

- ``protocol``. The protocol for which the front end listens. Must
  be ``HTTP``, ``HTTPS``, ``TCP``, or ``TERMINATED_HTTPS``.

Some attributes receive default values if you omit them from the
request:

- ``protocol_port``. The port on which the front end listens. Must
  be an integer from 1 to 65535.

- ``default_tls_container_ref``. The reference to a container that
  holds TLS secrets. If you also specify ``sni_container_refs``,
  this container is the default. This parameter is required for the
  ``TERMINATED_HTTPS`` protocol.

- ``sni_container_refs``. A list of references to containers that
  hold TLS secrets for server name indication (SNI). This parameter
  is required for the ``TERMINATED_HTTPS`` protocol.

- ``admin_state_up``. Default is ``true``.

- ``name``. Default is an empty string.

- ``description``. Default is an empty string.

- ``connection_limit``. Default is ``-1``, which indicates an
  infinite limit.

If the API cannot fulfill the request due to insufficient data or
data that is not valid, the service returns the HTTP ``Bad Request
(400)`` response code with information about the failure in the
response body. Validation errors require that you correct the error
and submit the request again.

You can configure all documented features of the listener at
creation time by specifying the additional elements or attributes
in the request.

Administrative users can specify a tenant ID that is different than
their own to create listeners for other tenants.

To update a listener, the load balancer to which to attach must
have an ``ACTIVE`` provisioning status.

Error response codes:201,404,409,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - protocol_port: protocol_port
   - protocol: protocol
   - description: description
   - default_tls_container_ref: default_tls_container_ref
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - sni_container_refs: sni_container_refs
   - connection_limit: connection_limit
   - listener: listener
   - default_pool_id: default_pool_id
   - loadbalancer_id: loadbalancer_id
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/lbaas/listener-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - protocol_port: protocol_port
   - protocol: protocol
   - description: description
   - default_tls_container_ref: default_tls_container_ref
   - admin_state_up: admin_state_up
   - loadbalancers: loadbalancers
   - tenant_id: tenant_id
   - sni_container_refs: sni_container_refs
   - connection_limit: connection_limit
   - listener: listener
   - default_pool_id: default_pool_id
   - id: id
   - name: name











List listeners
==============

.. rest_method::  GET /v2.0/lbaas/listeners

Lists all listeners.

This operation lists all listeners that are associated with your
tenant account.

The list might be empty.

Example: List listeners


Normal response codes: 200
Error response codes:500,401,503,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - protocol_port: protocol_port
   - protocol: protocol
   - description: description
   - default_tls_container_ref: default_tls_container_ref
   - admin_state_up: admin_state_up
   - loadbalancers: loadbalancers
   - tenant_id: tenant_id
   - sni_container_refs: sni_container_refs
   - connection_limit: connection_limit
   - listeners: listeners
   - default_pool_id: default_pool_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/listeners-list-response.json
   :language: javascript







Create pool
===========

.. rest_method::  POST /v2.0/lbaas/pools

Creates a pool.

This operation provisions a pool by using the configuration that
you define in the request object. After the API validates the
request and starts the provisioning process, the API returns a
response object, which contains a unique ID.

At a minimum, you must specify these pool attributes:

- ``tenant_id``. Admin only. Required to create a pool for another
  tenant.

- ``protocol``. The protocol for which this pool and its members
  listen. A valid value is ``TCP``, ``HTTP``, or ``HTTPS``.

- ``lb_algorithm``. The load-balancer algorithm, such as
  ``ROUND_ROBIN``, ``LEAST_CONNECTIONS``, and ``SOURCE_IP``, that
  distributes traffic to the pool members. The load-balancer
  provider must support this algorithm.

- ``listener_id``. The UUID of the listener in which this pool
  becomes the default pool. Each listener has only one default
  pool.

Some attributes receive default values if you omit them from the
request:

- ``admin_state_up``. Default is ``true``.

- ``name``. Default is an empty string.

- ``description``. Default is an empty string.

- ``session_persistence``. Default is an empty dictionary.

If the API cannot fulfill the request due to insufficient data or
data that is not valid, the service returns the HTTP ``Bad Request
(400)`` response code with information about the failure in the
response body. Validation errors require that you correct the error
and submit the request again.

Users can configure all documented features at creation time by
providing the additional elements or attributes in the request.

Administrative users can specify a tenant ID that is different than
their own to create pools for other tenants.

To update a pool, the load balancer to which to attach must have an
``ACTIVE`` provisioning status.

Error response codes:201,404,409,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - lb_algorithm: lb_algorithm
   - protocol: protocol
   - description: description
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - listener_id: listener_id
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/lbaas/pool-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - lb_algorithm: lb_algorithm
   - status: status
   - protocol: protocol
   - description: description
   - vip_id: vip_id
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - session_persistence: session_persistence
   - healthmonitor_id: healthmonitor_id
   - health_monitors_status: health_monitors_status
   - members: members
   - id: id
   - pool: pool
   - name: name











List pools
==========

.. rest_method::  GET /v2.0/lbaas/pools

Lists all pools that are associated with your tenant account.

The list might be empty.

Example: List pools


Normal response codes: 200
Error response codes:500,401,503,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - lb_method: lb_method
   - protocol: protocol
   - description: description
   - health_monitors: health_monitors
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - vip_id: vip_id
   - members: members
   - pools: pools
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/pools-list-response.json
   :language: javascript







Disassociate health monitor from pool
=====================================

.. rest_method::  DELETE /v2.0/lb/pools/{pool_id}/health_monitors/{health_monitor_id}

Disassociates a health monitor from a pool.

Error response codes:204,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - health_monitor_id: health_monitor_id
   - pool_id: pool_id











Show health monitor details
===========================

.. rest_method::  GET /v2.0/lb/health_monitors/{health_monitor_id}

Shows details for a health monitor.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - health_monitor_id: health_monitor_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - pools: pools
   - url_path: url_path
   - type: type
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/healthmonitor-show-response.json
   :language: javascript









Update health monitor
=====================

.. rest_method::  PUT /v2.0/lb/health_monitors/{health_monitor_id}

Updates a load balancer health monitor.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - url_path: url_path
   - health_monitor_id: health_monitor_id

Request Example
---------------

.. literalinclude:: ../samples/lbaas/healthmonitor-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - pools: pools
   - url_path: url_path
   - type: type
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/healthmonitor-update-response.json
   :language: javascript









Delete health monitor
=====================

.. rest_method::  DELETE /v2.0/lb/health_monitors/{health_monitor_id}

Deletes a load balancer health monitor.

Error response codes:204,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - health_monitor_id: health_monitor_id











List pools
==========

.. rest_method::  GET /v2.0/lb/pools

Lists pools.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - lb_algorithm: lb_algorithm
   - status: status
   - protocol: protocol
   - description: description
   - health_monitors: health_monitors
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - vip_id: vip_id
   - health_monitors_status: health_monitors_status
   - members: members
   - provider: provider
   - pools: pools
   - status_description: status_description
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/pools-list-response.json
   :language: javascript









Create a load balancer pool
===========================

.. rest_method::  POST /v2.0/lb/pools

Creates a load balancer pool.

Error response codes:201,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - lb_method: lb_method
   - protocol: protocol
   - description: description
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - pool: pool
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/lbaas/pool-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - lb_algorithm: lb_algorithm
   - status: status
   - protocol: protocol
   - description: description
   - health_monitors: health_monitors
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - vip_id: vip_id
   - health_monitors_status: health_monitors_status
   - members: members
   - provider: provider
   - status_description: status_description
   - id: id
   - pool: pool
   - name: name










List health monitors
====================

.. rest_method::  GET /v2.0/lb/health_monitors

Lists health monitors.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - health_monitors: health_monitors
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - pools: pools
   - url_path: url_path
   - type: type
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/lbaas/healthmonitors-list-response.json
   :language: javascript









Create a load balancer health monitor
=====================================

.. rest_method::  POST /v2.0/lb/health_monitors

Creates a load balancer health monitor.

Error response codes:201,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - url_path: url_path
   - type: type

Request Example
---------------

.. literalinclude:: ../samples/lbaas/healthmonitor-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - health_monitor: health_monitor
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - delay: delay
   - expected_codes: expected_codes
   - max_retries: max_retries
   - http_method: http_method
   - timeout: timeout
   - pools: pools
   - url_path: url_path
   - type: type
   - id: id










List VIPs
=========

.. rest_method::  GET /v2.0/lb/vips

Lists VIPs.

The list might be empty.


Normal response codes: 200
Error response codes:500,401,503,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - protocol: protocol
   - description: description
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - connection_limit: connection_limit
   - pool_id: pool_id
   - session_persistence: session_persistence
   - address: address
   - vips: vips
   - protocol_port: protocol_port
   - port_id: port_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/vips-list-response.json
   :language: javascript







Create a load balancer VIP
==========================

.. rest_method::  POST /v2.0/lb/vips

Creates a load balancer VIP.

Error response codes:201,400,404,500,401,413,503,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - protocol: protocol
   - description: description
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - connection_limit: connection_limit
   - pool_id: pool_id
   - session_persistence: session_persistence
   - vip: vip
   - address: address
   - protocol_port: protocol_port
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/lbaas/vip-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - status_description: status_description
   - protocol: protocol
   - description: description
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - connection_limit: connection_limit
   - pool_id: pool_id
   - session_persistence: session_persistence
   - vip: vip
   - address: address
   - protocol_port: protocol_port
   - port_id: port_id
   - id: id
   - name: name












Show pool details
=================

.. rest_method::  GET /v2.0/lb/pools/{pool_id}

Shows details for a pool.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - pool_id: pool_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - lb_algorithm: lb_algorithm
   - status: status
   - protocol: protocol
   - description: description
   - health_monitors: health_monitors
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - vip_id: vip_id
   - health_monitors_status: health_monitors_status
   - members: members
   - provider: provider
   - status_description: status_description
   - id: id
   - pool: pool
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/pool-show-response.json
   :language: javascript









Update pool
===========

.. rest_method::  PUT /v2.0/lb/pools/{pool_id}

Updates a load balancer pool.


Normal response codes: 200
Error response codes:400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - pool: pool
   - lb_method: lb_method
   - description: description
   - name: name
   - admin_state_up: admin_state_up
   - pool_id: pool_id

Request Example
---------------

.. literalinclude:: ../samples/lbaas/pool-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - lb_algorithm: lb_algorithm
   - status: status
   - protocol: protocol
   - description: description
   - health_monitors: health_monitors
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - admin_state_up: admin_state_up
   - vip_id: vip_id
   - health_monitors_status: health_monitors_status
   - members: members
   - provider: provider
   - status_description: status_description
   - id: id
   - pool: pool
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/lbaas/pool-update-response.json
   :language: javascript









Delete pool
===========

.. rest_method::  DELETE /v2.0/lb/pools/{pool_id}

Deletes a load balancer pool.

Error response codes:204,400,401,413,503,500,


Request
-------

.. rest_parameters:: parameters.yaml

   - pool_id: pool_id










