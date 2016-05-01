.. -*- rst -*-

============================================================================================================
VPNaaS 2.0 (CURRENT) (vpn, vpnservices, ikepolicies, ipsecpolicies, endpoint-groups, ipsec-site-connections)
============================================================================================================

The Virtual-Private-Network-as-a-Service (VPNaaS) extension enables
OpenStack tenants to extend private networks across the public
telecommunication infrastructure.

This initial implementation of the VPNaaS extension provides:

- Site-to-site VPN that connects two private networks.

- Multiple VPN connections per tenant.

- IKEv1 policy support with 3des, aes-128, aes-256, or aes-192
  encryption.

- IPSec policy support with 3des, aes-128, aes-192, or aes-256
  encryption, sha1 authentication, ESP, AH, or AH-ESP transform
  protocol, and tunnel or transport mode encapsulation.

- Dead Peer Detection (DPD) with hold, clear, restart, disabled, or
  restart-by-peer actions.

This extension introduces these resources:

- ``service``. A parent object that associates VPN with a specific
  subnet and router.

- ``ikepolicy``. The Internet Key Exchange (IKE) policy that
  identifies the authentication and encryption algorithm to use
  during phase one and two negotiation of a VPN connection.

- ``ipsecpolicy``. The IP security policy that specifies the
  authentication and encryption algorithm and encapsulation mode to
  use for the established VPN connection.

- ``ipsec-site-connection``. Details for the site-to-site IPsec
  connection, including the peer CIDRs, MTU, authentication mode,
  peer address, DPD settings, and status.


Create IKE policy
=================

.. rest_method::  POST /v2.0/vpn/ikepolicies

Creates an IKE policy.

The IKE policy is used for phases one and two negotiation of the
VPN connection. You can specify both the authentication and
encryption algorithms for connections.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - ikepolicy: ikepolicy
   - description: description
   - tenant_id: tenant_id
   - auth_algorithm: auth_algorithm
   - name: name
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - phase1_negotiation_mode: phase1_negotiation_mode
   - units: units
   - lifetime: lifetime
   - ike_version: ike_version

Request Example
---------------

.. literalinclude:: ../samples/vpn/ikepolicy-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - ikepolicy: ikepolicy
   - ikepolicies: ikepolicies
   - description: description
   - tenant_id: tenant_id
   - auth_algorithm: auth_algorithm
   - name: name
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - phase1_negotiation_mode: phase1_negotiation_mode
   - units: units
   - lifetime: lifetime
   - id: id
   - ike_version: ike_version







List IKE policies
=================

.. rest_method::  GET /v2.0/vpn/ikepolicies

Lists IKE policies.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - ikepolicies: ikepolicies
   - description: description
   - tenant_id: tenant_id
   - auth_algorithm: auth_algorithm
   - name: name
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - phase1_negotiation_mode: phase1_negotiation_mode
   - units: units
   - lifetime: lifetime
   - id: id
   - ike_version: ike_version



Response Example
----------------

.. literalinclude:: ../samples/vpn/ikepolicies-list-response.json
   :language: javascript






Create IPSec connection
=======================

.. rest_method::  POST /v2.0/vpn/ipsec-site-connections

Creates a site-to-site IPSec connection for a service.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - auth_mode: auth_mode
   - ikepolicy_id: ikepolicy_id
   - vpnservice_id: vpnservice_id
   - local_ep_group_id: local_ep_group_id
   - peer_address: peer_address
   - ipsec_site_connection: ipsec_site_connection
   - route_mode: route_mode
   - ipsecpolicy_id: ipsecpolicy_id
   - peer_id: peer_id
   - status: status
   - psk: psk
   - description: description
   - initiator: initiator
   - peer_cidrs: peer_cidrs
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - interval: interval
   - mtu: mtu
   - peer_ep_group_id: peer_ep_group_id
   - dpd: dpd
   - timeout: timeout
   - action: action

Request Example
---------------

.. literalinclude:: ../samples/vpn/ipsec-site-connection-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - auth_mode: auth_mode
   - ikepolicy_id: ikepolicy_id
   - vpnservice_id: vpnservice_id
   - local_ep_group_id: local_ep_group_id
   - peer_address: peer_address
   - id: id
   - ipsec_site_connection: ipsec_site_connection
   - route_mode: route_mode
   - ipsecpolicy_id: ipsecpolicy_id
   - peer_id: peer_id
   - status: status
   - psk: psk
   - description: description
   - initiator: initiator
   - peer_cidrs: peer_cidrs
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - interval: interval
   - mtu: mtu
   - peer_ep_group_id: peer_ep_group_id
   - dpd: dpd
   - timeout: timeout
   - action: action







List IPSec connections
======================

.. rest_method::  GET /v2.0/vpn/ipsec-site-connections

Lists all IPSec connections.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - auth_mode: auth_mode
   - ikepolicy_id: ikepolicy_id
   - vpnservice_id: vpnservice_id
   - local_ep_group_id: local_ep_group_id
   - peer_address: peer_address
   - id: id
   - route_mode: route_mode
   - ipsecpolicy_id: ipsecpolicy_id
   - peer_id: peer_id
   - status: status
   - psk: psk
   - description: description
   - initiator: initiator
   - peer_cidrs: peer_cidrs
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - interval: interval
   - mtu: mtu
   - peer_ep_group_id: peer_ep_group_id
   - dpd: dpd
   - timeout: timeout
   - action: action



Response Example
----------------

.. literalinclude:: ../samples/vpn/ipsec-site-connections-list-response.json
   :language: javascript






Show IPSec connection
=====================

.. rest_method::  GET /v2.0/vpn/ipsec-site-connections/{connection_id}

Shows details for an IPSec connection.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - connection_id: connection_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - auth_mode: auth_mode
   - ikepolicy_id: ikepolicy_id
   - vpnservice_id: vpnservice_id
   - local_ep_group_id: local_ep_group_id
   - peer_address: peer_address
   - id: id
   - ipsec_site_connection: ipsec_site_connection
   - route_mode: route_mode
   - ipsecpolicy_id: ipsecpolicy_id
   - peer_id: peer_id
   - status: status
   - psk: psk
   - description: description
   - initiator: initiator
   - peer_cidrs: peer_cidrs
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - interval: interval
   - mtu: mtu
   - peer_ep_group_id: peer_ep_group_id
   - dpd: dpd
   - timeout: timeout
   - action: action



Response Example
----------------

.. literalinclude:: ../samples/vpn/ipsec-site-connection-show-response.json
   :language: javascript







Update IPSec connection
=======================

.. rest_method::  PUT /v2.0/vpn/ipsec-site-connections/{connection_id}

Updates connection settings for an IPSec connection.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - psk: psk
   - initiator: initiator
   - description: description
   - ipsec_site_connection: ipsec_site_connection
   - admin_state_up: admin_state_up
   - interval: interval
   - peer_cidrs: peer_cidrs
   - mtu: mtu
   - peer_ep_group_id: peer_ep_group_id
   - local_ep_group_id: local_ep_group_id
   - dpd: dpd
   - timeout: timeout
   - action: action
   - peer_address: peer_address
   - peer_id: peer_id
   - name: name
   - connection_id: connection_id

Request Example
---------------

.. literalinclude:: ../samples/vpn/ipsec-site-connection-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - auth_mode: auth_mode
   - ikepolicy_id: ikepolicy_id
   - vpnservice_id: vpnservice_id
   - local_ep_group_id: local_ep_group_id
   - peer_address: peer_address
   - id: id
   - ipsec_site_connection: ipsec_site_connection
   - route_mode: route_mode
   - ipsecpolicy_id: ipsecpolicy_id
   - peer_id: peer_id
   - status: status
   - psk: psk
   - description: description
   - initiator: initiator
   - peer_cidrs: peer_cidrs
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - interval: interval
   - mtu: mtu
   - peer_ep_group_id: peer_ep_group_id
   - dpd: dpd
   - timeout: timeout
   - action: action



Response Example
----------------

.. literalinclude:: ../samples/vpn/ipsec-site-connection-update-response.json
   :language: javascript







Remove IPSec connection
=======================

.. rest_method::  DELETE /v2.0/vpn/ipsec-site-connections/{connection_id}

Removes an IPSec connection.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - connection_id: connection_id









Create VPN endpoint group
=========================

.. rest_method::  POST /v2.0/vpn/endpoint-groups

Creates a VPN endpoint group.

The endpoint group contains one or more endpoints of a specific
type that you can use to create a VPN connections.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - endpoints: endpoints
   - type: type
   - description: description
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/vpn/vpn-endpoint-group-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - tenant_id: tenant_id
   - endpoints: endpoints
   - type: type
   - id: id
   - name: name







List VPN endpoint groups
========================

.. rest_method::  GET /v2.0/vpn/endpoint-groups

Lists VPN endpoint groups.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - tenant_id: tenant_id
   - endpoints: endpoints
   - type: type
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/vpn/vpn-endpoint-groups-list-response.json
   :language: javascript






List VPN services
=================

.. rest_method::  GET /v2.0/vpn/vpnservices

Lists all VPN services.

The list might be empty.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - router_id: router_id
   - status: status
   - name: name
   - external_v6_ip: external_v6_ip
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - external_v4_ip: external_v4_ip
   - vpnservices: vpnservices
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/vpn/vpnservices-list-response.json
   :language: javascript






Create VPN service
==================

.. rest_method::  POST /v2.0/vpn/vpnservices

Creates a VPN service.

The service is associated with a router. After you create the
service, it can contain multiple VPN connections.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - router_id: router_id
   - description: description
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - vpnservice: vpnservice
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/vpn/vpnservice-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - router_id: router_id
   - status: status
   - name: name
   - external_v6_ip: external_v6_ip
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - external_v4_ip: external_v4_ip
   - vpnservice: vpnservice
   - id: id
   - description: description







Show VPN service details
========================

.. rest_method::  GET /v2.0/vpn/vpnservices/{service_id}

Shows details for a VPN service.

If the user is not an administrative user and the VPN service
object does not belong to the tenant account for the user, the
operation returns the ``Forbidden (403)`` response code.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - service_id: service_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - router_id: router_id
   - status: status
   - name: name
   - external_v6_ip: external_v6_ip
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - external_v4_ip: external_v4_ip
   - vpnservice: vpnservice
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/vpn/vpnservice-show-response.json
   :language: javascript







Update VPN service
==================

.. rest_method::  PUT /v2.0/vpn/vpnservices/{service_id}

Updates a VPN service.

Updates the attributes of a VPN service. You cannot update a
service with a ``PENDING_*`` status.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - vpnservice: vpnservice
   - description: description
   - name: name
   - admin_state_up: admin_state_up
   - service_id: service_id

Request Example
---------------

.. literalinclude:: ../samples/vpn/vpnservice-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - router_id: router_id
   - status: status
   - name: name
   - external_v6_ip: external_v6_ip
   - admin_state_up: admin_state_up
   - subnet_id: subnet_id
   - tenant_id: tenant_id
   - external_v4_ip: external_v4_ip
   - vpnservice: vpnservice
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/vpn/vpnservice-update-response.json
   :language: javascript







Remove VPN service
==================

.. rest_method::  DELETE /v2.0/vpn/vpnservices/{service_id}

Removes a VPN service.

If the service has connections, the request is rejected.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - service_id: service_id









Show IKE policy details
=======================

.. rest_method::  GET /v2.0/vpn/ikepolicies/{ikepolicy_id}

Shows details for an IKE policy.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - ikepolicy_id: ikepolicy_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - ikepolicy: ikepolicy
   - ikepolicies: ikepolicies
   - description: description
   - tenant_id: tenant_id
   - auth_algorithm: auth_algorithm
   - name: name
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - phase1_negotiation_mode: phase1_negotiation_mode
   - units: units
   - lifetime: lifetime
   - id: id
   - ike_version: ike_version



Response Example
----------------

.. literalinclude:: ../samples/vpn/ikepolicy-show-response.json
   :language: javascript







Update IKE policy
=================

.. rest_method::  PUT /v2.0/vpn/ikepolicies/{ikepolicy_id}

Updates policy settings in an IKE policy.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - ikepolicy: ikepolicy
   - description: description
   - auth_algorithm: auth_algorithm
   - name: name
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - phase1_negotiation_mode: phase1_negotiation_mode
   - units: units
   - lifetime: lifetime
   - ike_version: ike_version
   - ikepolicy_id: ikepolicy_id

Request Example
---------------

.. literalinclude:: ../samples/vpn/ikepolicy-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - ikepolicy: ikepolicy
   - ikepolicies: ikepolicies
   - description: description
   - tenant_id: tenant_id
   - auth_algorithm: auth_algorithm
   - name: name
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - phase1_negotiation_mode: phase1_negotiation_mode
   - units: units
   - lifetime: lifetime
   - id: id
   - ike_version: ike_version



Response Example
----------------

.. literalinclude:: ../samples/vpn/ikepolicy-update-response.json
   :language: javascript







Remove IKE policy
=================

.. rest_method::  DELETE /v2.0/vpn/ikepolicies/{ikepolicy_id}

Removes an IKE policy.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - ikepolicy_id: ikepolicy_id









Show IPSec policy
=================

.. rest_method::  GET /v2.0/vpn/ipsecpolicies/{ipsecpolicy_id}

Shows details for an IPSec policy.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - ipsecpolicy_id: ipsecpolicy_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - ipsecpolicies: ipsecpolicies
   - description: description
   - tenant_id: tenant_id
   - ipsecpolicy: ipsecpolicy
   - auth_algorithm: auth_algorithm
   - encapsulation_mode: encapsulation_mode
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - transform_protocol: transform_protocol
   - units: units
   - lifetime: lifetime
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/vpn/ipsecpolicy-show-response.json
   :language: javascript







Update IPSec policy
===================

.. rest_method::  PUT /v2.0/vpn/ipsecpolicies/{ipsecpolicy_id}

Updates policy settings in an IPSec policy.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - description: description
   - transform_protocol: transform_protocol
   - ipsecpolicy: ipsecpolicy
   - auth_algorithm: auth_algorithm
   - encapsulation_mode: encapsulation_mode
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - units: units
   - lifetime: lifetime
   - name: name
   - ipsecpolicy_id: ipsecpolicy_id

Request Example
---------------

.. literalinclude:: ../samples/vpn/ipsecpolicy-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - ipsecpolicies: ipsecpolicies
   - description: description
   - tenant_id: tenant_id
   - ipsecpolicy: ipsecpolicy
   - auth_algorithm: auth_algorithm
   - encapsulation_mode: encapsulation_mode
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - transform_protocol: transform_protocol
   - units: units
   - lifetime: lifetime
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/vpn/ipsecpolicy-update-response.json
   :language: javascript







Remove IPSec policy
===================

.. rest_method::  DELETE /v2.0/vpn/ipsecpolicies/{ipsecpolicy_id}

Removes an IPSec policy.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - ipsecpolicy_id: ipsecpolicy_id









Show VPN endpoint group
=======================

.. rest_method::  GET /v2.0/vpn/endpoint-groups/{endpoint_group_id}

Shows details for a VPN endpoint group.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - endpoint_group_id: endpoint_group_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - tenant_id: tenant_id
   - endpoints: endpoints
   - type: type
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/vpn/vpn-endpoint-group-show-response.json
   :language: javascript







Update VPN endpoint group
=========================

.. rest_method::  PUT /v2.0/vpn/endpoint-groups/{endpoint_group_id}

Updates settings for a VPN endpoint group.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - description: description
   - name: name
   - endpoint_group_id: endpoint_group_id

Request Example
---------------

.. literalinclude:: ../samples/vpn/vpn-endpoint-group-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - tenant_id: tenant_id
   - endpoints: endpoints
   - type: type
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/vpn/vpn-endpoint-group-update-response.json
   :language: javascript







Remove VPN endpoint group
=========================

.. rest_method::  DELETE /v2.0/vpn/endpoint-groups/{endpoint_group_id}

Removes a VPN endpoint group.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - endpoint_group_id: endpoint_group_id









Create IPSec policy
===================

.. rest_method::  POST /v2.0/vpn/ipsecpolicies

Creates an IP security (IPSec) policy.

The IPsec policy specifies the authentication and encryption
algorithms and encapsulation mode to use for the established VPN
connection.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - description: description
   - tenant_id: tenant_id
   - ipsecpolicy: ipsecpolicy
   - auth_algorithm: auth_algorithm
   - encapsulation_mode: encapsulation_mode
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - transform_protocol: transform_protocol
   - units: units
   - lifetime: lifetime
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/vpn/ipsecpolicy-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - ipsecpolicies: ipsecpolicies
   - description: description
   - tenant_id: tenant_id
   - ipsecpolicy: ipsecpolicy
   - auth_algorithm: auth_algorithm
   - encapsulation_mode: encapsulation_mode
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - transform_protocol: transform_protocol
   - units: units
   - lifetime: lifetime
   - id: id
   - name: name







List IPSec policies
===================

.. rest_method::  GET /v2.0/vpn/ipsecpolicies

Lists all IPSec policies.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - ipsecpolicies: ipsecpolicies
   - description: description
   - tenant_id: tenant_id
   - auth_algorithm: auth_algorithm
   - encapsulation_mode: encapsulation_mode
   - encryption_algorithm: encryption_algorithm
   - pfs: pfs
   - value: value
   - transform_protocol: transform_protocol
   - units: units
   - lifetime: lifetime
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/vpn/ipsecpolicies-list-response.json
   :language: javascript





