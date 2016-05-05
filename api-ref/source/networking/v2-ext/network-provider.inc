.. -*- rst -*-

================================================
Networks provider extended attributes (networks)
================================================

Lists, creates, shows information for, updates, and deletes
networks.

The provider extension decorates network resources with additional
attributes. These attributes are ``provider:network_type``,
``provider:physical_network``, and ``provider:segmentation_id``.
The validation rules for these attributes are the same as for the
`Networks multiple provider extension
<http://developer.openstack.org/api-ref-networking-v2-ext.html
#networks-multi-provider-ext>`_ . You cannot use both extensions at
the same time.


Show network details
====================

.. rest_method::  GET /v2.0/networks/{network_id}

Shows details for a network.


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
   - availability_zone_hints: availability_zone_hints
   - availability_zones: availability_zones
   - name: name
   - provider:physical_network: provider:physical_network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - provider:segmentation_id: provider:segmentation_id
   - mtu: mtu
   - shared: shared
   - subnets: subnets
   - port_security_enabled: port_security_enabled
   - provider:network_type: provider:network_type
   - id: id
   - network: network



Response Example
----------------

.. literalinclude:: ../samples/networks/network-show-response.json
   :language: javascript






Update network
==============

.. rest_method::  PUT /v2.0/networks/{network_id}

Updates a network.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - router:external: router:external
   - availability_zone_hints: availability_zone_hints
   - availability_zones: availability_zones
   - network: network
   - provider:physical_network: provider:physical_network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - provider:network_type: provider:network_type
   - shared: shared
   - port_security_enabled: port_security_enabled
   - provider:segmentation_id: provider:segmentation_id
   - name: name
   - network_id: network_id

Request Example
---------------

.. literalinclude:: ../samples/networks/network-update-request.json
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



Response Example
----------------

.. literalinclude:: ../samples/networks/network-update-response.json
   :language: javascript







Delete network
==============

.. rest_method::  DELETE /v2.0/networks/{network_id}

Deletes a network.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - network_id: network_id









List networks
=============

.. rest_method::  GET /v2.0/networks

Lists networks that are accessible to the tenant who submits the request.


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
   - availability_zone_hints: availability_zone_hints
   - availability_zones: availability_zones
   - name: name
   - provider:physical_network: provider:physical_network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - networks: networks
   - mtu: mtu
   - shared: shared
   - subnets: subnets
   - port_security_enabled: port_security_enabled
   - provider:network_type: provider:network_type
   - id: id
   - provider:segmentation_id: provider:segmentation_id



Response Example
----------------

.. literalinclude:: ../samples/networks/networks-list-response.json
   :language: javascript





Create network
==============

.. rest_method::  POST /v2.0/networks

Creates a network.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - router:external: router:external
   - network: network
   - provider:physical_network: provider:physical_network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - provider:network_type: provider:network_type
   - shared: shared
   - port_security_enabled: port_security_enabled
   - provider:segmentation_id: provider:segmentation_id
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/networks/network-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - router:external: router:external
   - availability_zone_hints: availability_zone_hints
   - network: network
   - provider:physical_network: provider:physical_network
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - provider:segmentation_id: provider:segmentation_id
   - mtu: mtu
   - shared: shared
   - subnets: subnets
   - port_security_enabled: port_security_enabled
   - provider:network_type: provider:network_type
   - id: id
   - name: name






