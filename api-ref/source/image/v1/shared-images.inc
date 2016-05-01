.. -*- rst -*-

=============
Shared images
=============




List shared images
==================

.. rest_method::  GET /v1/shared-images/{owner_id}

Lists the VM images that an owner shares. The owner ID is the tenant ID.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - owner_id: owner_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - can_share: can_share



Response Example
----------------

.. literalinclude:: ../samples/shared-images-list-response.json
   :language: javascript



