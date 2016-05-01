.. -*- rst -*-

========
Policies
========

Lists all policies and creates, shows information for, updates, and
deletes a policy.


List policies
=============

.. rest_method::  GET /v1/policies

Lists all policies.


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
   - type: type


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - policies: policies



Response Example
----------------

.. literalinclude:: ../samples/policies-list-response.json
   :language: javascript




Create policy
=============

.. rest_method::  POST /v1/policies

Creates a policy.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml

   - policy: policy
   - spec: spec
   - cooldown: cooldown
   - name: name
   - level: level

Request Example
---------------

.. literalinclude:: ../samples/policy-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location
   - policy: policy





Show policy details
===================

.. rest_method::  GET /v1/policies/{policy_id}

Shows details for a policy.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - policy_id: policy_id




Response Example
----------------

.. literalinclude:: ../samples/policy-show-response.json
   :language: javascript




Update policy
=============

.. rest_method::  PATCH /v1/policies/{policy_id}

Updates a policy.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - policy: policy
   - policy_id: policy_id

Request Example
---------------

.. literalinclude:: ../samples/policy-update-request.json
   :language: javascript





Response Example
----------------

.. literalinclude:: ../samples/policy-update-response.json
   :language: javascript




Delete policy
=============

.. rest_method::  DELETE /v1/policies/{policy_id}

Deletes a policy.

Error response codes:204,


Request
-------

.. rest_parameters:: parameters.yaml

   - policy_id: policy_id





