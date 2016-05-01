.. -*- rst -*-

======================================
VLAN transparency extension (networks)
======================================

Enables plug-ins that support VLAN transparency to deliver VLAN-
transparent trunk networks. If the service does not support VLAN
transparency and a user requests a VLAN-transparent network, the
plug-in refuses to create one and returns an appropriate error to
the user.

You cannot update the ``vlan-transparent`` attribute. If you try to
do so, an error occurs.

To delete a VLAN-transparent network, issue a normal delete network
request.

The ML2 plug-in currently supports this extension. With the ML2
plug-in, you can set the ``vlan-transparent`` attribute to either
``true`` or ``false``.


Show VLAN-transparent network details
=====================================

.. rest_method::  GET /v2.0/networks/{network_id}

Shows details for a VLAN-transparent network.


Normal response codes: 200
Error response codes:404,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - network_id: network_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - router:external: router:external
   - subnets: subnets
   - network: network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - mtu: mtu
   - shared: shared
   - vlan_transparent: vlan_transparent
   - port_security_enabled: port_security_enabled
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/networks/network-vlan-transparent-show-response.json
   :language: javascript






List networks with VLAN transparency attribute
==============================================

.. rest_method::  GET /v2.0/networks

Lists networks. The response shows the VLAN transparency attribute.


Normal response codes: 200
Error response codes:401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - router:external: router:external
   - subnets: subnets
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - mtu: mtu
   - vlan_transparent: vlan_transparent
   - shared: shared
   - id: id
   - port_security_enabled: port_security_enabled
   - networks: networks



Response Example
----------------

.. literalinclude:: ../samples/networks/networks-vlan-transparent-list-response.json
   :language: javascript





Create VLAN-transparent network
===============================

.. rest_method::  POST /v2.0/networks

Creates a VLAN-transparent network.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - router:external: router:external
   - network: network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - shared: shared
   - vlan_transparent: vlan_transparent
   - port_security_enabled: port_security_enabled
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/networks/network-vlan-transparent-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - router:external: router:external
   - subnets: subnets
   - network: network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - mtu: mtu
   - shared: shared
   - vlan_transparent: vlan_transparent
   - port_security_enabled: port_security_enabled
   - id: id
   - name: name






