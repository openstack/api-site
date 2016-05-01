.. -*- rst -*-

========
Clusters
========

Lists all clusters and creates, shows information for, updates,
deletes, and triggers an action on a cluster.


List clusters
=============

.. rest_method::  GET /v1/clusters

Lists clusters.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - limit: limit
   - marker: marker
   - sort: sort
   - global_project: global_project
   - name: name
   - status: status


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - clusters: clusters



Response Example
----------------

.. literalinclude:: ../samples/clusters-list-response.json
   :language: javascript




Create cluster
==============

.. rest_method::  POST /v1/clusters

Creates a cluster.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name
   - parent: parent
   - desired_capacity: desired_capacity
   - profile_id: profile_id
   - min_size: min_size
   - cluster: cluster
   - timeout: timeout
   - max_size: max_size
   - metadata: metadata

Request Example
---------------

.. literalinclude:: ../samples/cluster-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location
   - cluster: cluster





Trigger cluster action
======================

.. rest_method::  POST /v1/clusters/{cluster_id}/actions

Triggers an action on a cluster.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - action: action
   - cluster_id: cluster_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location





Show cluster details
====================

.. rest_method::  GET /v1/clusters/{cluster_id}

Shows details for a cluster.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - cluster_id: cluster_id




Response Example
----------------

.. literalinclude:: ../samples/cluster-show-response.json
   :language: javascript




Update cluster
==============

.. rest_method::  PATCH /v1/clusters/{cluster_id}

Updates a cluster.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name
   - parent: parent
   - profile_id: profile_id
   - cluster: cluster
   - timeout: timeout
   - metadata: metadata
   - cluster_id: cluster_id

Request Example
---------------

.. literalinclude:: ../samples/cluster-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location
   - cluster: cluster





Delete cluster
==============

.. rest_method::  DELETE /v1/clusters/{cluster_id}

Deletes a cluster.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - cluster_id: cluster_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location




