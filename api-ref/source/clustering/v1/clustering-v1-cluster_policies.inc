.. -*- rst -*-

================
Cluster policies
================

Lists all cluster policies and shows information for a cluster
policy.


Show cluster policy details
===========================

.. rest_method::  GET /v1/clusters/{cluster_id}/policies/{policy_id}

Shows details for a policy for a cluster.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - cluster_id: cluster_id
   - policy_id: policy_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - cluster_type: cluster_type
   - enabled: enabled
   - policy_name: policy_name
   - cluster_name: cluster_name
   - cluster_id: cluster_id
   - id: id
   - policy_id: policy_id



Response Example
----------------

.. literalinclude:: ../samples/cluster-policy-show-response.json
   :language: javascript







List policies
=============

.. rest_method::  GET /v1/clusters/{cluster_id}/policies

Lists all policies for a cluster.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - cluster_id: cluster_id
   - sort: sort
   - enabled: enabled




Response Example
----------------

.. literalinclude:: ../samples/cluster-policies-list-response.json
   :language: javascript



