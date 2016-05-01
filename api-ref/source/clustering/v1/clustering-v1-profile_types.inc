.. -*- rst -*-

=============
Profile types
=============

Lists all profile types and shows details for a profile type.


Show profile type details
=========================

.. rest_method::  GET /v1/profile-types/{profile_type}

Shows details for a profile type.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - profile_type: profile_type




Response Example
----------------

.. literalinclude:: ../samples/profile-type-show-response.json
   :language: javascript




List profile types
==================

.. rest_method::  GET /v1/profile-types

Lists supported profile types.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/profile-types-list-response.json
   :language: javascript



