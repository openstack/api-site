.. -*- rst -*-

=========
Receivers
=========

Lists all receivers and creates, shows information for, and deletes
a receiver.


Show receiver details
=====================

.. rest_method::  GET /v1/receivers/{receiver_id}

Shows details for a receiver.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - receiver_id: receiver_id




Response Example
----------------

.. literalinclude:: ../samples/receiver-show-response.json
   :language: javascript




Delete receiver
===============

.. rest_method::  DELETE /v1/receivers/{receiver_id}

Deletes a receiver.

Error response codes:204,


Request
-------

.. rest_parameters:: parameters.yaml

   - receiver_id: receiver_id






List receivers
==============

.. rest_method::  GET /v1/receivers

Lists all receivers.


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
   - user: user
   - cluster_id: cluster_id
   - action: action




Response Example
----------------

.. literalinclude:: ../samples/receivers-list-response.json
   :language: javascript




Create receiver
===============

.. rest_method::  POST /v1/receivers

Creates a receiver.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml

   - receiver: receiver

Request Example
---------------

.. literalinclude:: ../samples/receiver-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location
   - receiver: receiver




