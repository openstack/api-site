.. -*- rst -*-

==============
Share networks
==============

A share network stores network information that share servers can
use where shares are hosted. You can associate a share with a
single share network. When you create a share, you can optionally
specify the ID of a share network through which instances can
access the share.

You can create, update, view, and delete a share network.

When you create a share network, you can specify only one type of
network:

- Neutron network. Specify a network ID and subnet ID.

- Nova network. Specify a network ID.

For more information about supported plug-ins for share networks,
see `Manila Network Plugins <http://docs.openstack.org/developer/ma
nila/adminref/network_plugins.html>`_.

A share network has these attributes:

- The IP block in Classless Inter-Domain Routing (CIDR) notation
  from which to allocate the network.

- The IP version of the network.

- The network type, which is ``vlan``, ``vxlan``, ``gre``, or
  ``flat``.

- If the network uses segmentation, a segmentation identifier. For
  example, VLAN, VXLAN, and GRE networks use segmentation.


Show share network details
==========================

.. rest_method::  GET /v2/{tenant_id}/share-networks/{share_network_id}

Shows details for a share network.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - share_network_id: share_network_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - neutron_net_id: neutron_net_id
   - created_at: created_at
   - neutron_subnet_id: neutron_subnet_id
   - updated_at: updated_at
   - network_type: network_type
   - segmentation_id: segmentation_id
   - ip_version: ip_version
   - nova_net_id: nova_net_id
   - cidr: cidr
   - project_id: project_id
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-share-network-show-response.json
   :language: javascript




Update share network
====================

.. rest_method::  PUT /v2/{tenant_id}/share-networks/{share_network_id}

Updates a share network.

Note that if the share network is used by any share server, you can
update only the ``name`` and ``description`` attributes.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - description: description
   - name: name
   - tenant_id: tenant_id
   - share_network_id: share_network_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-network-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - neutron_net_id: neutron_net_id
   - created_at: created_at
   - neutron_subnet_id: neutron_subnet_id
   - updated_at: updated_at
   - network_type: network_type
   - segmentation_id: segmentation_id
   - ip_version: ip_version
   - nova_net_id: nova_net_id
   - cidr: cidr
   - project_id: project_id
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-share-network-update-response.json
   :language: javascript




Delete share network
====================

.. rest_method::  DELETE /v2/{tenant_id}/share-networks/{share_network_id}

Deletes a share network.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - share_network_id: share_network_id






List share networks with details
================================

.. rest_method::  GET /v2/{tenant_id}/share-networks/detail

Lists all share networks with details.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - neutron_net_id: neutron_net_id
   - created_at: created_at
   - neutron_subnet_id: neutron_subnet_id
   - updated_at: updated_at
   - network_type: network_type
   - segmentation_id: segmentation_id
   - ip_version: ip_version
   - nova_net_id: nova_net_id
   - cidr: cidr
   - project_id: project_id
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-share-networks-list-detailed-response.json
   :language: javascript




Add security service to share network
=====================================

.. rest_method::  POST /v2/{tenant_id}/share-networks/{share_network_id}/action

Adds a security service to a share network.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - security_service_id: security_service_id
   - tenant_id: tenant_id
   - share_network_id: share_network_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-network-add-security-service-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - neutron_net_id: neutron_net_id
   - created_at: created_at
   - neutron_subnet_id: neutron_subnet_id
   - updated_at: updated_at
   - network_type: network_type
   - segmentation_id: segmentation_id
   - ip_version: ip_version
   - nova_net_id: nova_net_id
   - cidr: cidr
   - project_id: project_id
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-share-network-add-security-service-response.json
   :language: javascript




Remove security service from share network
==========================================

.. rest_method::  POST /v2/{tenant_id}/share-networks/{share_network_id}/action

Removes a security service from a share network.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - security_service_id: security_service_id
   - tenant_id: tenant_id
   - share_network_id: share_network_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-network-remove-security-service-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - neutron_net_id: neutron_net_id
   - created_at: created_at
   - neutron_subnet_id: neutron_subnet_id
   - updated_at: updated_at
   - network_type: network_type
   - segmentation_id: segmentation_id
   - ip_version: ip_version
   - nova_net_id: nova_net_id
   - cidr: cidr
   - project_id: project_id
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-share-network-remove-security-service-response.json
   :language: javascript




Create share network
====================

.. rest_method::  POST /v2/{tenant_id}/share-networks

Creates a share network.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - nova_net_id: nova_net_id
   - neutron_net_id: neutron_net_id
   - neutron_subnet_id: neutron_subnet_id
   - description: description
   - name: name
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-network-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - neutron_net_id: neutron_net_id
   - created_at: created_at
   - neutron_subnet_id: neutron_subnet_id
   - updated_at: updated_at
   - network_type: network_type
   - segmentation_id: segmentation_id
   - ip_version: ip_version
   - nova_net_id: nova_net_id
   - cidr: cidr
   - project_id: project_id
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-share-network-create-response.json
   :language: javascript




List share networks
===================

.. rest_method::  GET /v2/{tenant_id}/share-networks

Lists all share networks.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-share-networks-list-response.json
   :language: javascript



