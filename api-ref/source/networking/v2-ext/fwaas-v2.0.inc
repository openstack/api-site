.. -*- rst -*-

=======================================================================
FWaaS v2.0 (CURRENT) (fw, firewalls, firewall_policies, firewall_rules)
=======================================================================

Use the Firewall-as-a-Service (FWaaS) v2.0 extension to deploy
firewalls to protect your networks.

The FWaaS extension enables you to:

- Apply firewall rules on traffic entering and leaving tenant
  networks.

- Apply TCP, UDP, ICMP, or protocol-agnostic rules.

- Create and share firewall policies that hold an ordered collection
  of the firewall rules.

- Audit firewall rules and policies.

This extension introduces these resources:

- ``firewall``. A logical firewall resource that a tenant can
  instantiate and manage. A firewall can have one firewall policy.

- ``firewall_policy``. An ordered collection of firewall rules. You
  can share a firewall policy across tenants. You can include a
  firewall policy as part of an audit workflow so that an
  authorized relevant entity can audit the firewall policy. This
  entity can differ from the tenant who created, or the tenants
  that use, the firewall policy.

- ``firewall_rule``. A collection of attributes, such as ports and
  IP addresses. These attributes define match criteria and an
  action to take, such as allow or deny, on matched data traffic.


Insert rule into a firewall policy
==================================

.. rest_method::  PUT /v2.0/fw/firewall_policies/{firewall_policy_id}/insert_rule

Insert firewall rule into a policy.

A firewall_rule_id is inserted relative to the position of the
firewall_rule_id set in ``insert_before`` or ``insert_after``. If
``insert_before`` is set, ``insert_after`` is ignored. If both
``insert_before`` and ``insert_after`` are not set, the new
firewall_rule_id is inserted at the top of the policy.


Normal response codes: 200
Error response codes:404,409,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - insert_after: insert_after
   - firewall_rule_id: firewall_rule_id
   - insert_before: insert_before
   - firewall_policy_id: firewall_policy_id

Request Example
---------------

.. literalinclude:: ../samples/firewalls/firewall-policy-insert-rule-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - firewall_rules: firewall_rules
   - tenant_id: tenant_id
   - firewall_list: firewall_list
   - audited: audited
   - shared: shared
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-policy-insert-rule-response.json
   :language: javascript








Show firewall policy details
============================

.. rest_method::  GET /v2.0/fw/firewall_policies/{firewall_policy_id}

Shows details for a firewall policy.

If the user is not an administrative user and the firewall policy
object does not belong to the tenant account, this call returns the
``Forbidden (403)`` response code.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_policy_id: firewall_policy_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - firewall_policy: firewall_policy
   - name: name
   - firewall_rules: firewall_rules
   - tenant_id: tenant_id
   - audited: audited
   - shared: shared
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-policy-show-response.json
   :language: javascript







Update firewall policy
======================

.. rest_method::  PUT /v2.0/fw/firewall_policies/{firewall_policy_id}

Updates a firewall policy.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_policy_id: firewall_policy_id

Request Example
---------------

.. literalinclude:: ../samples/firewalls/firewall-policy-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - firewall_policy: firewall_policy
   - name: name
   - firewall_rules: firewall_rules
   - tenant_id: tenant_id
   - audited: audited
   - shared: shared
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-policy-update-response.json
   :language: javascript







Delete firewall policy
======================

.. rest_method::  DELETE /v2.0/fw/firewall_policies/{firewall_policy_id}

Deletes a firewall policy.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_policy_id: firewall_policy_id









List firewall policies
======================

.. rest_method::  GET /v2.0/fw/firewall_policies

Lists all firewall policies.

The list might be empty.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - firewall_rules: firewall_rules
   - tenant_id: tenant_id
   - audited: audited
   - firewall_policies: firewall_policies
   - shared: shared
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-policies-list-response.json
   :language: javascript






Create firewall policy
======================

.. rest_method::  POST /v2.0/fw/firewall_policies

Creates a firewall policy.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_rules_id: firewall_rules_id
   - firewall_policy: firewall_policy
   - name: name
   - tenant_id: tenant_id
   - shared: shared
   - audited: audited
   - description: description

Request Example
---------------

.. literalinclude:: ../samples/firewalls/firewall-policy-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - firewall_policy: firewall_policy
   - name: name
   - firewall_rules: firewall_rules
   - tenant_id: tenant_id
   - audited: audited
   - shared: shared
   - id: id
   - description: description







Show firewall rule details
==========================

.. rest_method::  GET /v2.0/fw/firewall_rules/{firewall_rule_id}

Shows details for a firewall rule.

If the user is not an administrative user and the firewall rule
object does not belong to the tenant account, this call returns the
``Forbidden (403)`` response code.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_rule_id: firewall_rule_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - firewall_rule: firewall_rule
   - description: description
   - source_ip_address: source_ip_address
   - tenant_id: tenant_id
   - enabled: enabled
   - protocol: protocol
   - source_port: source_port
   - ip_version: ip_version
   - destination_ip_address: destination_ip_address
   - firewall_policy_id: firewall_policy_id
   - shared: shared
   - action: action
   - position: position
   - destination_port: destination_port
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-rule-show-response.json
   :language: javascript







Update firewall rule
====================

.. rest_method::  PUT /v2.0/fw/firewall_rules/{firewall_rule_id}

Updates a firewall rule.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_rule: firewall_rule
   - description: description
   - tenant_id: tenant_id
   - enabled: enabled
   - ip_version: ip_version
   - destination_ip_address: destination_ip_address
   - source_port: source_port
   - shared: shared
   - action: action
   - protocol: protocol
   - destination_port: destination_port
   - name: name
   - firewall_rule_id: firewall_rule_id

Request Example
---------------

.. literalinclude:: ../samples/firewalls/firewall-rule-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - firewall_rule: firewall_rule
   - description: description
   - source_ip_address: source_ip_address
   - tenant_id: tenant_id
   - enabled: enabled
   - protocol: protocol
   - source_port: source_port
   - ip_version: ip_version
   - destination_ip_address: destination_ip_address
   - firewall_policy_id: firewall_policy_id
   - shared: shared
   - action: action
   - position: position
   - destination_port: destination_port
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-rule-update-response.json
   :language: javascript







Delete firewall rule
====================

.. rest_method::  DELETE /v2.0/fw/firewall_rules/{firewall_rule_id}

Deletes a firewall rule.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_rule_id: firewall_rule_id









Show firewall details
=====================

.. rest_method::  GET /v2.0/fw/firewalls/{firewall_id}

Shows details for a firewall.

If the user is not an administrative user and the firewall object
does not belong to the tenant account, this call returns the
``Forbidden (403)`` response code.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_id: firewall_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - router_ids: router_ids
   - description: description
   - admin_state_up: admin_state_up
   - firewall: firewall
   - tenant_id: tenant_id
   - firewall_policy_id: firewall_policy_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-show-response.json
   :language: javascript







Update firewall
===============

.. rest_method::  PUT /v2.0/fw/firewalls/{firewall_id}

Updates a firewall.

To update a service, the service status cannot be a ``PENDING_*``
status.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - router_ids: router_ids
   - description: description
   - admin_state_up: admin_state_up
   - firewall: firewall
   - firewall_policy_id: firewall_policy_id
   - name: name
   - firewall_id: firewall_id

Request Example
---------------

.. literalinclude:: ../samples/firewalls/firewall-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - router_ids: router_ids
   - description: description
   - admin_state_up: admin_state_up
   - firewall: firewall
   - tenant_id: tenant_id
   - firewall_policy_id: firewall_policy_id
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-update-response.json
   :language: javascript







Delete firewall
===============

.. rest_method::  DELETE /v2.0/fw/firewalls/{firewall_id}

Deletes a firewall.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_id: firewall_id









List firewall rules
===================

.. rest_method::  GET /v2.0/fw/firewall_rules

Lists all firewall rules.

The list might be empty.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - protocol: protocol
   - description: description
   - source_ip_address: source_ip_address
   - tenant_id: tenant_id
   - enabled: enabled
   - id: id
   - ip_version: ip_version
   - destination_ip_address: destination_ip_address
   - firewall_policy_id: firewall_policy_id
   - shared: shared
   - action: action
   - position: position
   - destination_port: destination_port
   - source_port: source_port
   - firewalls: firewalls
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-rules-list-response.json
   :language: javascript






Create firewall rule
====================

.. rest_method::  POST /v2.0/fw/firewall_rules

Creates a firewall rule.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_rule: firewall_rule
   - description: description
   - tenant_id: tenant_id
   - enabled: enabled
   - ip_version: ip_version
   - destination_ip_address: destination_ip_address
   - source_port: source_port
   - shared: shared
   - action: action
   - protocol: protocol
   - destination_port: destination_port
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/firewalls/firewall-rule-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - firewall_rule: firewall_rule
   - description: description
   - source_ip_address: source_ip_address
   - tenant_id: tenant_id
   - enabled: enabled
   - protocol: protocol
   - source_port: source_port
   - ip_version: ip_version
   - destination_ip_address: destination_ip_address
   - firewall_policy_id: firewall_policy_id
   - shared: shared
   - action: action
   - position: position
   - destination_port: destination_port
   - id: id
   - name: name







List firewalls
==============

.. rest_method::  GET /v2.0/fw/firewalls

Lists all firewalls.

The list might be empty.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - router_ids: router_ids
   - description: description
   - admin_state_up: admin_state_up
   - tenant_id: tenant_id
   - firewall_policy_id: firewall_policy_id
   - firewalls: firewalls
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewalls-list-response.json
   :language: javascript






Create firewall
===============

.. rest_method::  POST /v2.0/fw/firewalls

Creates a firewall.

The firewall must be associated with a firewall policy.

If ``admin_state_up`` is ``false``, the firewall would block all
traffic.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - router_ids: router_ids
   - description: description
   - admin_state_up: admin_state_up
   - firewall: firewall
   - firewall_policy_id: firewall_policy_id
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/firewalls/firewall-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - router_ids: router_ids
   - description: description
   - admin_state_up: admin_state_up
   - firewall: firewall
   - tenant_id: tenant_id
   - firewall_policy_id: firewall_policy_id
   - id: id
   - name: name







Remove rule from firewall policy
================================

.. rest_method::  PUT /v2.0/fw/firewall_policies/{firewall_policy_id}/remove_rule

Remove firewall rule from a policy.


Normal response codes: 200
Error response codes:404,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - firewall_rule_id: firewall_rule_id
   - firewall_policy_id: firewall_policy_id

Request Example
---------------

.. literalinclude:: ../samples/firewalls/firewall-policy-remove-rule-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - firewall_rules: firewall_rules
   - tenant_id: tenant_id
   - firewall_list: firewall_list
   - audited: audited
   - shared: shared
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/firewalls/firewall-policy-remove-rule-response.json
   :language: javascript






