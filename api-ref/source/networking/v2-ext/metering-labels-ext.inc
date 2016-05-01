.. -*- rst -*-

=================================================================
Metering labels and rules (metering-labels, metering-label-rules)
=================================================================

Creates, modifies, and deletes OpenStack Layer3 metering labels and
rules.


List metering labels
====================

.. rest_method::  GET /v2.0/metering/metering-labels

Lists all L3 metering labels that belong to the tenant.

The list shows the UUID for each metering label.


Normal response codes: 200
Error response codes:401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - tenant_id: tenant_id
   - metering_labels: metering_labels
   - shared: shared
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/metering-labels/metering-labels-list-response.json
   :language: javascript





Create metering label
=====================

.. rest_method::  POST /v2.0/metering/metering-labels

Creates an L3 metering label.

Error response codes:201,403,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - shared: shared
   - metering_label: metering_label
   - description: description
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/metering-labels/metering-label-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - tenant_id: tenant_id
   - metering_label: metering_label
   - shared: shared
   - id: id
   - name: name








Show metering label details
===========================

.. rest_method::  GET /v2.0/metering/metering-labels/{metering-label-id}

Shows details for a metering label.

The response body shows the description, name, and UUID.


Normal response codes: 200
Error response codes:404,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - tenant_id: tenant_id
   - metering_label: metering_label
   - shared: shared
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/metering-labels/metering-label-show-response.json
   :language: javascript






Delete metering label
=====================

.. rest_method::  DELETE /v2.0/metering/metering-labels/{metering-label-id}

Deletes an L3 metering label.

Error response codes:404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml









List metering label rules
=========================

.. rest_method::  GET /v2.0/metering/metering-label-rules

Lists a summary of all L3 metering label rules that belong to the tenant.

The list shows the UUID for each metering label rule.


Normal response codes: 200
Error response codes:401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - direction: direction
   - remote_ip_prefix: remote_ip_prefix
   - metering_label_rules: metering_label_rules
   - excluded : excluded 
   - metering_label_id: metering_label_id
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/metering-labels/metering-label-rules-list-response.json
   :language: javascript





Create metering label rule
==========================

.. rest_method::  POST /v2.0/metering/metering-label-rules

Creates an L3 metering label rule.

Error response codes:201,404,403,401,400,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - remote_ip_prefix: remote_ip_prefix
   - direction: direction
   - metering_label_id: metering_label_id
   - metering_label_rule: metering_label_rule
   - excluded: excluded

Request Example
---------------

.. literalinclude:: ../samples/metering-labels/metering-label-rule-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - direction: direction
   - remote_ip_prefix: remote_ip_prefix
   - excluded : excluded 
   - metering_label_id: metering_label_id
   - metering_label_rule: metering_label_rule
   - id: id










Show metering label rule details
================================

.. rest_method::  GET /v2.0/metering/metering-label-rules/{metering-label-rule-id}

Shows details for a metering label rule.

The response body shows this information for each metering label
rule:

- ``direction``. Either ingress or egress.

- ``excluded``. Either ``true`` or ``false``.

- The UUID for the metering label rule.

- The remote IP prefix.

- The metering label ID for the metering label with which the rule
  is associated.


Normal response codes: 200
Error response codes:404,401,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/metering-labels/metering-label-rule-show-response.json
   :language: javascript






Delete metering label rule
==========================

.. rest_method::  DELETE /v2.0/metering/metering-label-rules/{metering-label-rule-id}

Deletes an L3 metering label rule.

Error response codes:404,204,401,


Request
-------

.. rest_parameters:: parameters.yaml








