.. -*- rst -*-

========
Profiles
========

Lists all profiles and creates, shows information for, updates, and
deletes a profile.


Show profile details
====================

.. rest_method::  GET /v1/profiles/{profile_id}

Shows details for a profile.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - profile_id: profile_id




Response Example
----------------

.. literalinclude:: ../samples/profile-show-response.json
   :language: javascript




Update profile
==============

.. rest_method::  PATCH /v1/profiles/{profile_id}

Updates a profile.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name
   - metadata: metadata
   - profile_id: profile_id

Request Example
---------------

.. literalinclude:: ../samples/profile-update-request.json
   :language: javascript





Response Example
----------------

.. literalinclude:: ../samples/profile-update-response.json
   :language: javascript




Delete profile
==============

.. rest_method::  DELETE /v1/profiles/{profile_id}

Deletes a profile.

Error response codes:204,


Request
-------

.. rest_parameters:: parameters.yaml

   - profile_id: profile_id






List profiles
=============

.. rest_method::  GET /v1/profiles

Lists all profiles.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - limit: limit
   - marker: marker
   - sort: sort
   - global_project: global_project
   - name: name
   - type: type
   - metadata: metadata


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - profiles: profiles



Response Example
----------------

.. literalinclude:: ../samples/profiles-list-response.json
   :language: javascript




Create profile
==============

.. rest_method::  POST /v1/profiles

Creates a profile.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml

   - spec: spec
   - name: name
   - metadata: metadata

Request Example
---------------

.. literalinclude:: ../samples/profile-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location
   - profile: profile




