.. -*- rst -*-

=========================
Quotas extension (quotas)
=========================

Lists quotas for tenants who have non-default quota values, and
lists, updates, and resets quotas for a tenant.

A quota value of ``-1`` means that quota has no limit.


List quotas for tenants with non-default quota values
=====================================================

.. rest_method::  GET /v2.0/quotas

Lists quotas for tenants who have non-default quota values.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - subnet: subnet
   - network: network
   - floatingip: floatingip
   - subnetpool: subnetpool
   - quotas: quotas
   - security_group_rule: security_group_rule
   - security_group: security_group
   - router: router
   - rbac_policy: rbac_policy
   - port: port



Response Example
----------------

.. literalinclude:: ../samples/quotas/quotas-list-response.json
   :language: javascript






List quotas for a tenant
========================

.. rest_method::  GET /v2.0/quotas/{tenant_id}

Lists quotas for a tenant.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - subnet: subnet
   - network: network
   - floatingip: floatingip
   - subnetpool: subnetpool
   - quota: quota
   - security_group_rule: security_group_rule
   - security_group: security_group
   - router: router
   - rbac_policy: rbac_policy
   - port: port



Response Example
----------------

.. literalinclude:: ../samples/quotas/quotas-list-for-tenant-response.json
   :language: javascript







Update quota for a tenant
=========================

.. rest_method::  PUT /v2.0/quotas/{tenant_id}

Updates quotas for a tenant. Use when non-default quotas are desired.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - subnet: subnet
   - network: network
   - floatingip: floatingip
   - subnetpool: subnetpool
   - quota: quota
   - security_group_rule: security_group_rule
   - security_group: security_group
   - router: router
   - rbac_policy: rbac_policy
   - port: port
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/quotas/quotas-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - subnet: subnet
   - network: network
   - floatingip: floatingip
   - subnetpool: subnetpool
   - quota: quota
   - security_group_rule: security_group_rule
   - security_group: security_group
   - router: router
   - rbac_policy: rbac_policy
   - port: port



Response Example
----------------

.. literalinclude:: ../samples/quotas/quotas-update-response.json
   :language: javascript







Reset quota for a tenant
========================

.. rest_method::  DELETE /v2.0/quotas/{tenant_id}

Resets quotas to default values for a tenant.

Error response codes:404,403,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id








