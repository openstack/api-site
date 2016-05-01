.. -*- rst -*-

========
Networks
========

Lists, shows details for, creates, updates, and deletes networks.


Show network details
====================

.. rest_method::  GET /v2.0/networks/{network_id}

Shows details for a network.

You can control which response parameters are returned by using the
fields query parameter. For information, see `Filtering and column
selection <http://specs.openstack.org/openstack/neutron-
specs/specs/api/networking_general_api_information.html#filtering-
and-column-selection>`_.

The response might show extension response parameters. For
information, see `Networks multiple provider extension (networks)
<http://developer.openstack.org/api-ref-
networking-v2-ext.html#showProviderNetwork>`_.


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
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - updated_at: updated_at
   - changed_at: changed_at
   - mtu: mtu
   - qos_policy_id: qos_policy_id
   - subnets: subnets
   - shared: shared
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
Error response codes:404,403,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - router:external: router:external
   - network: network
   - admin_state_up: admin_state_up
   - shared: shared
   - port_security_enabled: port_security_enabled
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
   - availability_zone_hints: availability_zone_hints
   - availability_zones: availability_zones
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - mtu: mtu
   - qos_policy_id: qos_policy_id
   - subnets: subnets
   - shared: shared
   - id: id
   - network: network



Response Example
----------------

.. literalinclude:: ../samples/networks/network-update-response.json
   :language: javascript








Delete network
==============

.. rest_method::  DELETE /v2.0/networks/{network_id}

Deletes a network and its associated resources.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - network_id: network_id









List networks
=============

.. rest_method::  GET /v2.0/networks

Lists networks to which the tenant has access.

Use the ``fields`` query parameter to filter the response. For
information, see `Filtering and Column Selection <https://wiki.open
stack.org/wiki/Neutron/APIv2-specification#Filtering_and_Column_Sel
ection>`_.

Use the ``tags``, ``tags-any``, ``not-tags``, ``not-tags-any``
query parameter to filter the response with tags. For information,
see `REST API Impact <http://specs.openstack.org/openstack/neutron-
specs/specs/mitaka/add-tags-to-core-resources.html#rest-api-
impact>`_.


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
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - networks: networks
   - mtu: mtu
   - subnets: subnets
   - shared: shared
   - id: id
   - qos_policy_id: qos_policy_id



Response Example
----------------

.. literalinclude:: ../samples/networks/networks-list-response.json
   :language: javascript





Create network
==============

.. rest_method::  POST /v2.0/networks

Creates a network.

A request body is optional. An administrative user can specify
another tenant UUID, which is the tenant who owns the network, in
the request body.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml


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
   - availability_zones: availability_zones
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - mtu: mtu
   - qos_policy_id: qos_policy_id
   - subnets: subnets
   - shared: shared
   - id: id
   - network: network







Bulk create networks
====================

.. rest_method::  POST /v2.0/networks

Creates multiple networks in a single request.

In the request body, specify a list of networks.

The bulk create operation is always atomic. Either all or no
networks in the request body are created.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - router:external: router:external
   - name: name
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - port_security_enabled: port_security_enabled
   - shared: shared
   - networks: networks

Request Example
---------------

.. literalinclude:: ../samples/networks/networks-bulk-create-request.json
   :language: javascript



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
   - shared: shared
   - id: id
   - port_security_enabled: port_security_enabled
   - networks: networks






