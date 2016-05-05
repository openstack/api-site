.. -*- rst -*-

=========================
Image tags (images, tags)
=========================

Adds and deletes image tags.


Add image tag
=============

.. rest_method::  PUT /v2/images/{image_id}/tags/{tag}

(Since Image API v2.0) Adds a tag to an image.

Error response codes:404,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id
   - tag: tag







Delete image tag
================

.. rest_method::  DELETE /v2/images/{image_id}/tags/{tag}

(Since Image API v2.0) Deletes a tag from an image.

Error response codes:404,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id
   - tag: tag






