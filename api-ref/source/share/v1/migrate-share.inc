.. -*- rst -*-

==========================
Experimental share actions
==========================




Migrate share
=============

.. rest_method::  POST /v2/{tenant_id}/shares/{share_id}/action

(Only for API v1.0-2.14) Migrates a share from one back end to another.

You can migrate a share from one back end to another but both back
ends must set the ``driver_handles_share_servers`` parameter to
``False``. If a share driver handles one of the back ends, this
action is not supported. You can configure a back end in the
``manila.conf`` file.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - force_host_copy: force_host_copy
   - host: host
   - share_id: share_id
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-share-actions-migrate-request.json
   :language: javascript






