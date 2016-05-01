.. -*- rst -*-

=====================================================================
Networking Flavors Framework v2.0 (CURRENT) (flavor, service_profile)
=====================================================================

Extension that allows user selection of operator-curated flavors
during resource creation.

Service ``q-flavors`` must be enabled in the configuration to use
this feature.


Disassociate a flavor.
======================

.. rest_method::  DELETE /v2.0/flavors/{flavor_id}/service_profiles/{profile_id}

Disassociate a flavor from a service profile.

Error response codes:404,403,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - profile_id: profile_id
   - flavor_id: flavor_id









Show service profile details
============================

.. rest_method::  GET /v2.0/service_profiles/{profile_id}

Shows details for a service profile.

This operation returns a service profile object by ID. If you are
not an administrative user and the object is not visible to your
tenant account, the service returns the HTTP ``Forbidden (403)``
response code.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - profile_id: profile_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - driver: driver
   - enabled: enabled
   - metainfo: metainfo
   - service_profile: service_profile
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/flavors/service-profile-show-response.json
   :language: javascript







Update service profile
======================

.. rest_method::  PUT /v2.0/service_profiles/{profile_id}

Updates a service profile.


Normal response codes: 200
Error response codes:404,403,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - service_profile: service_profile
   - enabled: enabled
   - driver: driver
   - description: description
   - metainfo: metainfo
   - profile_id: profile_id

Request Example
---------------

.. literalinclude:: ../samples/flavors/service-profile-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - driver: driver
   - enabled: enabled
   - metainfo: metainfo
   - service_profile: service_profile
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/flavors/service-profile-update-response.json
   :language: javascript








Delete service profile
======================

.. rest_method::  DELETE /v2.0/service_profiles/{profile_id}

Deletes a service profile.

Attempting to delete a service profile that is currently associated
with a flavor will return a ``Conflict 409`` with a response body
containing an in use message.

Error response codes:409,404,403,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - profile_id: profile_id










List service profiles
=====================

.. rest_method::  GET /v2.0/service_profiles

Lists all service profiles visible for the tenant account.

The list can be empty.

Standard query parameters are supported on the URI.


Normal response codes: 200
Error response codes:401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - driver: driver
   - enabled: enabled
   - metainfo: metainfo
   - service_profiles: service_profiles
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/flavors/service-profiles-list-response.json
   :language: javascript





Create service profile
======================

.. rest_method::  POST /v2.0/service_profiles

Creates a service profile.

This operation establishes a new service profile that can be
associated with one or more flavors.

Either metadata or a driver is required.

If a driver is specified but does not exist, call will return a
``Not found 404`` error with the response body explaining that the
driver could not be found.

Creation currently limited to administrators. Other users will
receive a ``Forbidden 403`` response code with a response body
NeutronError message expressing that creation is disallowed by
policy.

If the API cannot fulfill the request due to insufficient data or
data that is not valid, the service returns the HTTP ``Bad Request
(400)`` response code with information about the failure in the
response body. Validation errors require that you correct the error
and submit the request again.

Error response codes:201,403,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - service_profile: service_profile
   - enabled: enabled
   - driver: driver
   - description: description
   - metainfo: metainfo

Request Example
---------------

.. literalinclude:: ../samples/flavors/service-profile-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - driver: driver
   - enabled: enabled
   - metainfo: metainfo
   - service_profile: service_profile
   - id: id








List flavors
============

.. rest_method::  GET /v2.0/flavors

Lists all flavors visible for the tenant account.

The list can be empty.

Standard query parameters are supported on the URI. For example,
``fields`` can be used to limit the returned response to just name
by appending ``?fields=name``. If Neutron configuration supports
pagination by overriding allow_pagination = false, the ``marker``
query parameter can set the last element id the client has seen and
``limit`` set the maximum number of items to return. if Neutron
configuration has allow_sorting = true, ``sort_key`` and
``sort_dir`` pairs can be used where sort direction is 'asc' or
'desc'.


Normal response codes: 200
Error response codes:401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - flavors: flavors
   - description: description
   - enabled: enabled
   - service_profiles: service_profiles
   - service_type: service_type
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/flavors/flavors-list-response.json
   :language: javascript





Create flavor
=============

.. rest_method::  POST /v2.0/flavors

Creates a flavor.

This operation establishes a new flavor.

The service_type to which the flavor applies is a required
parameter. The corresponding service plugin must have been
activated as part of the configuration. See `Service providers
<http://developer.openstack.org/api-ref-networking-v2.html#service-
type>`_ for how to see currently loaded service types. Additionally
the service plugin needs to support the use of flavors. For
example, the LOADBALANCERV2 service type using the LBaaSv2 API
currently supports Neutron service flavors.

Creation currently limited to administrators. Other users will
receive a ``Forbidden 403`` response code with a response body
NeutronError message expressing that creation is disallowed by
policy.

Until one or more service profiles are associated with the flavor
by the operator, attempts to use the flavor during resource
creations will currently return a ``Not Found 404`` with a response
body that indicates no service profile could be found.

If the API cannot fulfill the request due to insufficient data or
data that is not valid, the service returns the HTTP ``Bad Request
(400)`` response code with information about the failure in the
response body. Validation errors require that you correct the error
and submit the request again.

Error response codes:201,403,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - service_type: service_type
   - flavor: flavor
   - enabled: enabled
   - description: description
   - name: name

Request Example
---------------

.. literalinclude:: ../samples/flavors/flavor-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - enabled: enabled
   - service_profiles: service_profiles
   - service_type: service_type
   - flavor: flavor
   - id: id
   - name: name








Associate flavor
================

.. rest_method::  POST /v2.0/flavors/{flavor_id}/service_profiles

Associate a flavor with a service profile.

A flavor can be associated with more than one profile.

Will return ``409 Conflict`` if association already exists.

Error response codes:201,404,403,401,400,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - service_profile: service_profile
   - id: id
   - flavor_id: flavor_id

Request Example
---------------

.. literalinclude:: ../samples/flavors/flavor-associate-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - service_profile: service_profile
   - id: id










Show flavor details
===================

.. rest_method::  GET /v2.0/flavors/{flavor_id}

Shows details for a flavor.

This operation returns a flavor object by ID. If you are not an
administrative user and the flavor object is not visible to your
tenant account, the service returns the HTTP ``Forbidden (403)``
response code.


Normal response codes: 200
Error response codes:404,403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - flavor_id: flavor_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - enabled: enabled
   - service_profiles: service_profiles
   - service_type: service_type
   - flavor: flavor
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/flavors/flavor-show-response.json
   :language: javascript







Update flavor
=============

.. rest_method::  PUT /v2.0/flavors/{flavor_id}

Updates a flavor.

The service_type cannot be updated as there may be associated
service profiles and consumers depending on the value.


Normal response codes: 200
Error response codes:404,403,401,400,


Request
-------

.. rest_parameters:: parameters.yaml

   - flavor: flavor
   - enabled: enabled
   - description: description
   - name: name
   - flavor_id: flavor_id

Request Example
---------------

.. literalinclude:: ../samples/flavors/flavor-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - description: description
   - enabled: enabled
   - service_profiles: service_profiles
   - service_type: service_type
   - flavor: flavor
   - id: id
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/flavors/flavor-update-response.json
   :language: javascript








Delete flavor
=============

.. rest_method::  DELETE /v2.0/flavors/{flavor_id}

Deletes a flavor.

Error response codes:404,403,204,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - flavor_id: flavor_id








