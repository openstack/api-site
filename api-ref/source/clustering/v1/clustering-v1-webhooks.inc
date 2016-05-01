.. -*- rst -*-

========
Webhooks
========

Triggers an action represented by a webhook.


Trigger webhook action
======================

.. rest_method::  POST /v1/webhooks/{webhook_id}/trigger

Triggers a webhook receiver.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - webhook_id: webhook_id
   - V: V
   - params: params


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location




