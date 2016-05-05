.. -*- rst -*-

=======================
OS-KSS3 admin extension
=======================




List credentials by type
========================

.. rest_method::  GET /v2.0/users/{userId}/OS-KSS3/credentials/s3credentials/{type}

Lists credentials by type.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/OS-KSS3/credentialswiths3-list-response.json
   :language: javascript












Update user credentials
=======================

.. rest_method::  POST /v2.0/users/{userId}/OS-KSS3/credentials/s3credentials

Updates credentials.


Normal response codes: 200
Error response codes:413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml


Request Example
---------------

.. literalinclude:: ../samples/OS-KSS3/s3Credentials-create-request.json
   :language: javascript





Response Example
----------------

.. literalinclude:: ../samples/OS-KSS3/s3Credentials-show-response.json
   :language: javascript













Revoke user credentials
=======================

.. rest_method::  DELETE /v2.0/users/{userId}/OS-KSS3/credentials/s3credentials

Revokes user credentials.

Error response codes:204,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml
















Get user credentials
====================

.. rest_method::  GET /v2.0/users/{userId}/OS-KSS3/credentials/s3credentials

Gets user credentials.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/OS-KSS3/s3Credentials-show-response.json
   :language: javascript












Grant credential to user
========================

.. rest_method::  POST /v2.0/users/{userId}/OS-KSS3/credentials

Grants a credential to a user.

Error response codes:201,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml


Request Example
---------------

.. literalinclude:: ../samples/OS-KSS3/s3Credentials-create-request.json
   :language: javascript
















List credentials
================

.. rest_method::  GET /v2.0/users/{userId}/OS-KSS3/credentials

Lists credentials.


Normal response codes: 200
Error response codes:203,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/OS-KSS3/credentialswiths3-list-response.json
   :language: javascript











