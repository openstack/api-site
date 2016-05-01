.. -*- rst -*-

==============
Share metadata
==============

Shows, sets, updates, and unsets share metadata.


Show share metadata
===================

.. rest_method::  GET /v2/{tenant_id}/shares/{share_id}/metadata

Shows the metadata for a share.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - share_id: share_id
   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - metadata: metadata



Response Example
----------------

.. literalinclude:: ../samples/manila-share-show-metadata-response.json
   :language: javascript




Update share metadata
=====================

.. rest_method::  PUT /v2/{tenant_id}/shares/{share_id}/metadata

Updates the metadata for a share.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - metadata: metadata
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-update-metadata-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - metadata: metadata



Response Example
----------------

.. literalinclude:: ../samples/manila-share-update-metadata-response.json
   :language: javascript




Set share metadata
==================

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/metadata

Sets the metadata on a share.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - metadata: metadata
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-set-metadata-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - metadata: metadata



Response Example
----------------

.. literalinclude:: ../samples/manila-share-set-metadata-response.json
   :language: javascript




Unset share metadata
====================

.. rest_method::  DELETE /v2/{tenant_id}/shares/{share_id}/metadata/{key}

Unsets the metadata on a share.

To unset a metadata key value, specify only the key name in the
URI.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - share_id: share_id
   - tenant_id: tenant_id




Response Example
----------------

.. literalinclude:: 
   :language: javascript



