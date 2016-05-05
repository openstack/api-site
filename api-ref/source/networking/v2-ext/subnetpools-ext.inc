.. -*- rst -*-

====================================
Subnet pools extension (subnetpools)
====================================

Lists, creates, shows details for, updates, and deletes subnet
pools.


Show subnet pool
================

.. rest_method::  GET /v2.0/subnetpools/{subnetpool_id}

Shows information for a subnet pool.

Use the ``fields`` query parameter to filter the results.


Normal response codes: 200
Error response codes:404,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - subnetpool_id: subnetpool_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - default_quota: default_quota
   - tenant_id: tenant_id
   - created_at: created_at
   - subnetpool: subnetpool
   - updated_at: updated_at
   - prefixes: prefixes
   - min_prefixlen: min_prefixlen
   - address_scope_id: address_scope_id
   - ip_version: ip_version
   - shared: shared
   - default_prefixlen: default_prefixlen
   - id: id
   - max_prefixlen: max_prefixlen



Response Example
----------------

.. literalinclude:: ../samples/subnets/subnetpool-show-response.json
   :language: javascript






Update subnet pool
==================

.. rest_method::  PUT /v2.0/subnetpools/{subnetpool_id}

Updates a subnet pool.


Normal response codes: 200
Error response codes:404,403,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name
   - default_quota: default_quota
   - tenant_id: tenant_id
   - subnetpool: subnetpool
   - prefixes: prefixes
   - min_prefixlen: min_prefixlen
   - address_scope_id: address_scope_id
   - default_prefixlen: default_prefixlen
   - max_prefixlen: max_prefixlen
   - subnetpool_id: subnetpool_id

Request Example
---------------

.. literalinclude:: ../samples/subnets/subnetpool-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - default_quota: default_quota
   - tenant_id: tenant_id
   - created_at: created_at
   - subnetpool: subnetpool
   - updated_at: updated_at
   - prefixes: prefixes
   - min_prefixlen: min_prefixlen
   - address_scope_id: address_scope_id
   - ip_version: ip_version
   - shared: shared
   - default_prefixlen: default_prefixlen
   - id: id
   - max_prefixlen: max_prefixlen



Response Example
----------------

.. literalinclude:: ../samples/subnets/subnetpool-update-response.json
   :language: javascript








Delete subnet pool
==================

.. rest_method::  DELETE /v2.0/subnetpools/{subnetpool_id}

Deletes a subnet pool.

The operation fails if any subnets allocated from the subnet pool
are still in use.

Error response codes:404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - subnetpool_id: subnetpool_id








List subnet pools
=================

.. rest_method::  GET /v2.0/subnetpools

Lists subnet pools to which the tenant has access.

Default policy settings returns exclusively subnet pools owned by
the tenant submitting the request, unless the request is submitted
by a user with administrative rights.


Normal response codes: 200
Error response codes:401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - default_quota: default_quota
   - tenant_id: tenant_id
   - created_at: created_at
   - updated_at: updated_at
   - prefixes: prefixes
   - min_prefixlen: min_prefixlen
   - address_scope_id: address_scope_id
   - ip_version: ip_version
   - shared: shared
   - default_prefixlen: default_prefixlen
   - subnetpools: subnetpools
   - id: id
   - max_prefixlen: max_prefixlen



Response Example
----------------

.. literalinclude:: ../samples/subnets/subnetpools-list-response.json
   :language: javascript





Create subnet pool
==================

.. rest_method::  POST /v2.0/subnetpools

Creates a subnet pool.

Error response codes:201,404,403,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name
   - default_quota: default_quota
   - tenant_id: tenant_id
   - subnetpool: subnetpool
   - prefixes: prefixes
   - min_prefixlen: min_prefixlen
   - address_scope_id: address_scope_id
   - shared: shared
   - default_prefixlen: default_prefixlen
   - max_prefixlen: max_prefixlen

Request Example
---------------

.. literalinclude:: ../samples/subnets/subnetpool-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - default_quota: default_quota
   - tenant_id: tenant_id
   - created_at: created_at
   - subnetpool: subnetpool
   - updated_at: updated_at
   - prefixes: prefixes
   - min_prefixlen: min_prefixlen
   - address_scope_id: address_scope_id
   - ip_version: ip_version
   - shared: shared
   - default_prefixlen: default_prefixlen
   - id: id
   - max_prefixlen: max_prefixlen








