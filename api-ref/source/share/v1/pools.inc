.. -*- rst -*-

======================
Back-end storage pools
======================

An administrator can list all back-end storage pools that are known
to the scheduler service.


List back-end storage pools
===========================

.. rest_method::  GET /v2/{tenant_id}/scheduler-stats/pools

Lists all back-end storage pools.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - host: host
   - name: name
   - pool: pool
   - backend: backend



Response Example
----------------

.. literalinclude:: ../samples/manila-pools-list-response.json
   :language: javascript




List back-end storage pools with details
========================================

.. rest_method::  GET /v2/{tenant_id}/scheduler-stats/pools/detail

Lists all storage pools for a back end, with details.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - vendor_name: vendor_name
   - qos: qos
   - name: name
   - consistency_group_support: consistency_group_support
   - share_backend_name: share_backend_name
   - total_capacity_gb: total_capacity_gb
   - reserved_percentage: reserved_percentage
   - server_pools_mapping: server_pools_mapping
   - capabilities: capabilities
   - driver_handles_share_servers: driver_handles_share_servers
   - driver_version: driver_version
   - host: host
   - storage_protocol: storage_protocol
   - timestamp: timestamp
   - pools: pools
   - free_capacity_gb: free_capacity_gb
   - snapshot_support: snapshot_support
   - pool: pool
   - backend: backend



Response Example
----------------

.. literalinclude:: ../samples/manila-pools-list-detailed-response.json
   :language: javascript



