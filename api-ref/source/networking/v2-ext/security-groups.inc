.. -*- rst -*-

=================================
Security groups (security-groups)
=================================

Lists, creates, shows information for, updates, and deletes
security groups.


Show security group
===================

.. rest_method::  GET /v2.0/security-groups/{security_group_id}

Shows details for a security group.

The response contains the description, name, UUID, and security
group rules that are associated with the security group and tenant.


Normal response codes: 200
Error response codes:404,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - security_group_id: security_group_id
   - verbose: verbose
   - fields: fields


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - remote_group_id: remote_group_id
   - direction: direction
   - protocol: protocol
   - description: description
   - ethertype: ethertype
   - port_range_max: port_range_max
   - security_group_rules: security_group_rules
   - security_group_id: security_group_id
   - tenant_id: tenant_id
   - port_range_min: port_range_min
   - remote_ip_prefix: remote_ip_prefix
   - security_group: security_group
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/security-groups/security-group-show-response.json
   :language: javascript






Update security group
=====================

.. rest_method::  PUT /v2.0/security-groups/{security_group_id}

Updates a security group.


Normal response codes: 200
Error response codes:413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml

   - description: description
   - name: name
   - security_group_id: security_group_id

Request Example
---------------

.. literalinclude:: ../samples/security-groups/security-group-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - security_group: security_group
   - tenant_id: tenant_id
   - description: description
   - name: name
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/security-groups/security-group-update-response.json
   :language: javascript











Delete security group
=====================

.. rest_method::  DELETE /v2.0/security-groups/{security_group_id}

Deletes an OpenStack Networking security group.

This operation deletes an OpenStack Networking security group and
its associated security group rules, provided that a port is not
associated with the security group.

This operation does not require a request body. This operation does
not return a response body.

Error response codes:409,404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - security_group_id: security_group_id









List security groups
====================

.. rest_method::  GET /v2.0/security-groups

Lists OpenStack Networking security groups to which the tenant has access.

The list shows the UUID for and the rules that are associated with
each security group.


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
   - description: description
   - ethertype: ethertype
   - port_range_max: port_range_max
   - security_group_rules: security_group_rules
   - security_group_id: security_group_id
   - tenant_id: tenant_id
   - port_range_min: port_range_min
   - remote_ip_prefix: remote_ip_prefix
   - id: id
   - security_groups: security_groups
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/security-groups/security-groups-list-response.json
   :language: javascript





Create security group
=====================

.. rest_method::  POST /v2.0/security-groups

Creates an OpenStack Networking security group.

This operation creates a security group with default security group
rules for the IPv4 and IPv6 ether types.

Error response codes:201,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - security_group: security_group
   - tenant_id: tenant_id
   - description: description
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/security-groups/security-group-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - remote_group_id: remote_group_id
   - direction: direction
   - protocol: protocol
   - description: description
   - ethertype: ethertype
   - port_range_max: port_range_max
   - security_group_rules: security_group_rules
   - security_group_id: security_group_id
   - tenant_id: tenant_id
   - port_range_min: port_range_min
   - remote_ip_prefix: remote_ip_prefix
   - security_group: security_group
   - id: id
   - name: name






