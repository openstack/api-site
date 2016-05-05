.. -*- rst -*-

=====
Nodes
=====

Lists all nodes, and creates, shows information for, updates,
deletes a node.


List nodes
==========

.. rest_method::  GET /v1/nodes

Lists all nodes.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - limit: limit
   - marker: marker
   - sort: sort
   - global_project: global_project
   - cluster_id: cluster_id
   - name: name
   - status: status


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - nodes: nodes



Response Example
----------------

.. literalinclude:: ../samples/nodes-list-response.json
   :language: javascript




Create node
===========

.. rest_method::  POST /v1/nodes

Creates a node.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - role: role
   - profile_id: profile_id
   - cluster_id: cluster_id
   - name: name
   - metadata: metadata

Request Example
---------------

.. literalinclude:: ../samples/node-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location
   - node: node





Trigger node action
===================

.. rest_method::  POST /v1/nodes/{node_id}/actions

Triggers an action on a node.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - action: action
   - node_id: node_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location





Update node
===========

.. rest_method::  PATCH /v1/nodes/{node_id}

Updates a node.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - node: node
   - node_id: node_id

Request Example
---------------

.. literalinclude:: ../samples/node-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location
   - node: node





Delete node
===========

.. rest_method::  DELETE /v1/nodes/{node_id}

Deletes a node.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - node_id: node_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location





Show node details
=================

.. rest_method::  GET /v1/nodes/{node_id}

Shows data for a node.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - node_id: node_id
   - show_details: show_details




Response Example
----------------

.. literalinclude:: ../samples/node-show-response.json
   :language: javascript



