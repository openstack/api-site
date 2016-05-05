.. -*- rst -*-

=================
Security services
=================

You can create, update, view, and delete a security service. A
security service stores configuration information for clients for
authentication and authorization (AuthN/AuthZ). For example, a
share server will be the client for an existing service such as
LDAP, Kerberos, or Microsoft Active Directory.

You can associate a share with from one to three security service
types:

- ``ldap``. LDAP.

- ``kerberos``. Kerberos.

- ``active_directory``. Microsoft Active Directory.

You can configure a security service with these options:

- A DNS IP address.

- An IP address or host name.

- A domain.

- A user or group name.

- The password for the user, if you specify a user name.


Show security service details
=============================

.. rest_method::  GET /v2/{tenant_id}/security-services/{security_service_id}

Shows details for a security service.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - security_service_id: security_service_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - domain: domain
   - project_id: project_id
   - name: name
   - updated_at: updated_at
   - created_at: created_at
   - dns_ip: dns_ip
   - server: server
   - user: user
   - password: password
   - type: type
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-security-service-show-response.json
   :language: javascript




Update security service
=======================

.. rest_method::  PUT /v2/{tenant_id}/security-services/{security_service_id}

Updates a security service.

If the security service is in ``active`` state, you can update only
the ``name`` and ``description`` attributes. A security service in
``active`` state is attached to a share network with an associated
share server.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - domain: domain
   - description: description
   - dns_ip: dns_ip
   - server: server
   - user: user
   - password: password
   - type: type
   - name: name
   - tenant_id: tenant_id
   - security_service_id: security_service_id

Request Example
---------------

.. literalinclude:: ../samples/manila-security-service-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - domain: domain
   - project_id: project_id
   - name: name
   - updated_at: updated_at
   - created_at: created_at
   - dns_ip: dns_ip
   - server: server
   - user: user
   - password: password
   - type: type
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-security-service-update-response.json
   :language: javascript




Delete security service
=======================

.. rest_method::  DELETE /v2/{tenant_id}/security-services/{security_service_id}

Deletes a security service.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: tenant_id
   - security_service_id: security_service_id






Create security service
=======================

.. rest_method::  POST /v2/{tenant_id}/security-services

Creates a security service.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - domain: domain
   - description: description
   - dns_ip: dns_ip
   - server: server
   - user: user
   - password: password
   - type: type
   - name: name
   - tenant_id: tenant_id

Request Example
---------------

.. literalinclude:: ../samples/manila-security-service-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - domain: domain
   - project_id: project_id
   - name: name
   - updated_at: updated_at
   - created_at: created_at
   - dns_ip: dns_ip
   - server: server
   - user: user
   - password: password
   - type: type
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-security-service-create-response.json
   :language: javascript




List security services
======================

.. rest_method::  GET /v2/{tenant_id}/security-services

Lists all security services.


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
   - type: type
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/manila-security-services-list-response.json
   :language: javascript




List security services with details
===================================

.. rest_method::  GET /v2/{tenant_id}/security-services/detail

Lists all security services with details.


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
   - domain: domain
   - project_id: project_id
   - name: name
   - updated_at: updated_at
   - created_at: created_at
   - dns_ip: dns_ip
   - server: server
   - user: user
   - password: password
   - type: type
   - id: id
   - description: description



Response Example
----------------

.. literalinclude:: ../samples/manila-security-services-list-detailed-response.json
   :language: javascript



