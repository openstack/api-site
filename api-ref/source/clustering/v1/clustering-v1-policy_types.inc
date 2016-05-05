.. -*- rst -*-

============
Policy types
============

Lists all policy types and shows details for a policy type.


List policy types
=================

.. rest_method::  GET /v1/policy-types

Lists all supported policy types.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name



Response Example
----------------

.. literalinclude:: ../samples/policy-types-list-response.json
   :language: javascript




Show policy type details
========================

.. rest_method::  GET /v1/policy-types/{policy_type}

Shows details for a policy type.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - policy_type: policy_type




Response Example
----------------

.. literalinclude:: ../samples/policy-type-show-response.json
   :language: javascript



