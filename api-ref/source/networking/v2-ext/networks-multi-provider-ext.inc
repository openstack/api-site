.. -*- rst -*-

===============================================
Networks multiple provider extension (networks)
===============================================

Enables administrative users to define multiple physical bindings
for an OpenStack Networking network and list or show details for
networks with multiple physical bindings.

You cannot update any ``provider`` attributes. If you try to do so,
an error occurs.

To delete a network with multiple physical bindings, issue a normal
delete network request.

To define multiple physical bindings for a network, include a
``segments`` list in the request body of a ``POST /v2.0/networks``
request. Each element in the ``segments`` list has the same
structure as the provider network attributes. These attributes are
``provider:network_type``, ``provider:physical_network``, and
``provider:segmentation_id``. The validation rules for these
attributes are the same as for the `Networks provider extended
attributes <http://developer.openstack.org/api-ref-
networking-v2-ext.html#network_provider-ext>`_ . You cannot use
both extensions at the same time.

The NSX and ML2 plug-ins support this extension. With the ML2 plug-
in, you can specify multiple VLANs for a network, a VXLAN tunnel
ID, and a VLAN.


Show details for a network with multiple segments
=================================================

.. rest_method::  GET /v2.0/networks/{network_id}

Shows details for a network with multiple segments.


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
   - provider:physical_network: provider:physical_network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - segments: segments
   - provider:segmentation_id: provider:segmentation_id
   - mtu: mtu
   - shared: shared
   - port_security_enabled: port_security_enabled
   - provider:network_type: provider:network_type
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/networks/networks-multi-show-response.json
   :language: javascript






List networks
=============

.. rest_method::  GET /v2.0/networks

Lists networks that are accessible to the tenant who submits the request. Networks with multiple segments include the ``segments`` list in the response.


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
   - provider:physical_network: provider:physical_network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - segments: segments
   - mtu: mtu
   - shared: shared
   - id: id
   - port_security_enabled: port_security_enabled
   - provider:network_type: provider:network_type
   - networks: networks
   - provider:segmentation_id: provider:segmentation_id



Response Example
----------------

.. literalinclude:: ../samples/networks/networks-multi-list-response.json
   :language: javascript





Create network with multiple segment mappings
=============================================

.. rest_method::  POST /v2.0/networks

Creates a network with multiple segment mappings.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - router:external: router:external
   - network: network
   - provider:physical_network: provider:physical_network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - segments: segments
   - provider:network_type: provider:network_type
   - shared: shared
   - port_security_enabled: port_security_enabled
   - provider:segmentation_id: provider:segmentation_id
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/networks/network-multi-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - router:external: router:external
   - subnets: subnets
   - network: network
   - provider:physical_network: provider:physical_network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - provider:segmentation_id: provider:segmentation_id
   - mtu: mtu
   - shared: shared
   - port_security_enabled: port_security_enabled
   - provider:network_type: provider:network_type
   - id: id
   - name: name






