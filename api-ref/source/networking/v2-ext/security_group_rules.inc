.. -*- rst -*-

===========================================
Security group rules (security-group-rules)
===========================================

Lists, creates, shows information for, and deletes security group
rules.


Show security group rule
========================

.. rest_method::  GET /v2.0/security-group-rules/{security-group-rules-id}

Shows detailed information for a security group rule.

The response body contains the following information about the
security group rule:


Normal response codes: 200
Error response codes:404,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - remote_group_id: remote_group_id
   - direction: direction
   - protocol: protocol
   - ethertype: ethertype
   - port_range_max: port_range_max
   - security_group_id: security_group_id
   - security_group_rule: security_group_rule
   - tenant_id: tenant_id
   - port_range_min: port_range_min
   - remote_ip_prefix: remote_ip_prefix
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/security-groups/security-group-rule-show-response.json
   :language: javascript






Delete security group rule
==========================

.. rest_method::  DELETE /v2.0/security-group-rules/{security-group-rules-id}

Deletes a rule from an OpenStack Networking security group.

Error response codes:404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml









List security group rules
=========================

.. rest_method::  GET /v2.0/security-group-rules

Lists a summary of all OpenStack Networking security group rules that the tenant can access.

The list provides the UUID for each security group rule.


Normal response codes: 200
Error response codes:401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - remote_group_id: remote_group_id
   - direction: direction
   - protocol: protocol
   - ethertype: ethertype
   - port_range_max: port_range_max
   - security_group_rules: security_group_rules
   - security_group_id: security_group_id
   - tenant_id: tenant_id
   - port_range_min: port_range_min
   - remote_ip_prefix: remote_ip_prefix
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/security-groups/security-group-rules-list-response.json
   :language: javascript





Create security group rule
==========================

.. rest_method::  POST /v2.0/security-group-rules

Creates an OpenStack Networking security group rule.

Error response codes:201,404,409,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - remote_group_id: remote_group_id
   - direction: direction
   - protocol: protocol
   - ethertype: ethertype
   - port_range_max: port_range_max
   - security_group_id: security_group_id
   - security_group_rule: security_group_rule
   - port_range_min: port_range_min
   - remote_ip_prefix: remote_ip_prefix

Request Example
---------------

.. literalinclude:: ../samples/security-groups/security-group-rule-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - remote_group_id: remote_group_id
   - direction: direction
   - protocol: protocol
   - ethertype: ethertype
   - port_range_max: port_range_max
   - security_group_id: security_group_id
   - security_group_rule: security_group_rule
   - tenant_id: tenant_id
   - port_range_min: port_range_min
   - remote_ip_prefix: remote_ip_prefix
   - id: id








