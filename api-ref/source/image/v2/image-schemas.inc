.. -*- rst -*-

=======================================================
Image schemas (schemas, image, images, member, members)
=======================================================

Gets a JSON-schema document that represents an images or image
entity.


Show images schema
==================

.. rest_method::  GET /v2/schemas/images

(Since Images v2.0) Shows a JSON schema document that represents an images entity.

An images entity is a container of image entities.

The following schema is solely an example. Consider only the
response to the API call as authoritative.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/schemas-images-list-response.json
   :language: javascript




Show image member schema
========================

.. rest_method::  GET /v2/schemas/member

(Since Images v2.1) Shows a JSON schema document that represents an image member entity.

The following schema is solely an example. Consider only the
response to the API call as authoritative.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/schema-image-member-show-response.json
   :language: javascript




Show image members schema
=========================

.. rest_method::  GET /v2/schemas/members

(Since Images v2.1) Shows a JSON schema document that represents an image members entity.

An image members entity is a container of image member entities.

The following schema is solely an example. Consider only the
response to the API call as authoritative.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/schemas-image-members-list-response.json
   :language: javascript




Show image schema
=================

.. rest_method::  GET /v2/schemas/image

(Since Images v2.0) Shows a JSON schema document that represents an image entity.

The following schema is solely an example. Consider only the
response to the API call as authoritative.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml





Response Example
----------------

.. literalinclude:: ../samples/schema-image-show-response.json
   :language: javascript



