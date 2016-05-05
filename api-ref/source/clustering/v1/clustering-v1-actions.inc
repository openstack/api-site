.. -*- rst -*-

=======
Actions
=======

Lists all actions and shows details for an action.


Show action details
===================

.. rest_method::  GET /v1/actions/{action_id}

Shows details for an action.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - action_id: action_id




Response Example
----------------

.. literalinclude:: ../samples/action-show-response.json
   :language: javascript




List actions
============

.. rest_method::  GET /v1/actions

Lists all actions.


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
   - target: target
   - action: action




Response Example
----------------

.. literalinclude:: ../samples/actions-list-response.json
   :language: javascript



