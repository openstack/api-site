.. -*- rst -*-

=============
Share servers
=============

A share server is created by multi-tenant back-end drivers where
shares are hosted. For example, with the ``generic`` driver, shares
are hosted on Compute VMs. With the ``cluster_mode`` driver from
NetApp, shares are hosted on virtual storage servers, also known as
Vservers or SVMs.

Administrators can perform read and delete actions for share
servers. An administrator can delete an active share server only if
it contains no dependent shares. If an administrator deletes the
share server, the Shared File Systems service creates a share
server in response to a subsequent create share request.

An administrator can use the ``policy.json`` file to grant
permissions for share server actions to other roles.

The status of a share server indicates its current state. After you
successfully set up a share server, its status is ``active``. If
errors occur during set up such as when server data is not valid,
its status is ``error``.

The possible share servers statuses are:

**Share server statuses**

+--------------+------------------------------------------------------------------+
| Status       | Description                                                      |
+--------------+------------------------------------------------------------------+
| ``active``   | Share server was successfully set up.                            |
+--------------+------------------------------------------------------------------+
| ``error``    | The set up or deletion of the share server failed.               |
+--------------+------------------------------------------------------------------+
| ``deleting`` | The share server has no dependent shares and is being deleted.   |
+--------------+------------------------------------------------------------------+
| ``creating`` | The share server is being created on the back end with data from |
|              | the database.                                                    |
+--------------+------------------------------------------------------------------+


Show share server details
=========================

.. rest_method::  GET /v2/{tenant_id}/share-servers/{share_server_id}/detail

Shows details for a share server.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - share_server_id: share_server_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - backend_details: backend_details



Response Example
----------------

.. literalinclude:: ../samples/manila-share-server-show-details-response.json
   :language: javascript




List share servers
==================

.. rest_method::  GET /v2/{tenant_id}/share-servers

Lists all share servers.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - updated_at: updated_at
   - share_network_id: share_network_id
   - host: host
   - share_network_name: share_network_name
   - project_id: project_id
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-servers-list-response.json
   :language: javascript




Show share server details
=========================

.. rest_method::  GET /v2/{tenant_id}/share-servers/{share_server_id}

Shows details for a share server.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - share_server_id: share_server_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - backend_details: backend_details
   - created_at: created_at
   - updated_at: updated_at
   - share_network_id: share_network_id
   - host: host
   - share_network_name: share_network_name
   - project_id: project_id
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/manila-share-server-show-response.json
   :language: javascript




Delete share server
===================

.. rest_method::  DELETE /v2/{tenant_id}/share-servers/{share_server_id}

Deletes a share server.

An administrator can delete an active share server only if it
contains no dependent shares.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - share_server_id: share_server_id





