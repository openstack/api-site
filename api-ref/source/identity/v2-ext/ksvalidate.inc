.. -*- rst -*-

=============================
OS-KSVALIDATE admin extension
=============================




List endpoints for token
========================

.. rest_method::  GET /v2.0/OS-KSVALIDATE/token/endpoints

Lists endpoints for a token.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/OS-KSVALIDATE/endpoints-list-response.json
   :language: javascript












Validate token
==============

.. rest_method::  GET /v2.0/OS-KSVALIDATE/token/validate

Checks that a token is valid and that it belongs to the tenant and any service IDs. Returns the permissions for a particular client.

Behavior is similar to ``/tokens/{tokenId}``. If the token is not
valid, the call returns the ``itemNotFound (404)`` response code.

This extension might decrypt the ``X-Subject-Token`` header and
internally call and pass in all headers and query parameters to the
normal validation code for Identity. Consequently, this extension
must support all existing ``/tokens/{tokenId}`` calls including
extensions such as HP-IDM.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/OS-KSVALIDATE/token-validate-response.json
   :language: javascript












Check token
===========

.. rest_method::  HEAD /v2.0/OS-KSVALIDATE/token/validate

Checks that a token is valid and that it belongs to the tenant and any service IDs, for performance.

Behavior is similar to ``/tokens/{tokenId}``. If the token is not
valid, the call returns the ``itemNotFound (404)`` response code.

This extension might decrypt the ``X-Subject-Token`` header and
internally call and pass in all headers and query parameters to the
normal validation code for Identity. Consequently, this extension
must support all existing ``/tokens/{tokenId}`` calls including
extensions such as HP-IDM.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: 
   :language: javascript











