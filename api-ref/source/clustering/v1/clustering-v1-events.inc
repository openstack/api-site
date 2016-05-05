.. -*- rst -*-

======
Events
======

Lists all events and shows information for an event.


List events
===========

.. rest_method::  GET /v1/events

Lists events.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - limit: limit
   - marker: marker
   - sort: sort
   - global_project: global_project
   - obj_id: obj_id
   - obj_type: obj_type
   - obj_name: obj_name
   - cluster_id: cluster_id
   - action: action




Response Example
----------------

.. literalinclude:: ../samples/events-list-response.json
   :language: javascript




Show event details
==================

.. rest_method::  GET /v1/events/{event_id}

Shows details for an event.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - event_id: event_id




Response Example
----------------

.. literalinclude:: ../samples/event-show-response.json
   :language: javascript



