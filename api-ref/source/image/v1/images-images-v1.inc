.. -*- rst -*-

======
Images
======




Create image
============

.. rest_method::  POST /v1/images

Registers a virtual machine (VM) image.

Error response codes:202,


Request
-------

.. rest_parameters:: parameters.yaml

   - createImage: createImage
   - container_format: container_format
   - disk_format: disk_format
   - name: name


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location





List images
===========

.. rest_method::  GET /v1/images

Lists all public VM images.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name
   - container_format: container_format
   - disk_format: disk_format
   - status: status
   - size_min: size_min
   - size_max: size_max
   - changes-since: changes-since


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name
   - container_format: container_format
   - disk_format: disk_format
   - uri: uri
   - images: images
   - size: size



Response Example
----------------

.. literalinclude:: ../samples/images-list-response.json
   :language: javascript




Update image
============

.. rest_method::  PUT /v1/images/{image_id}

Updates an image, uploads an image file, or updates metadata for an image.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - location: location



Response Example
----------------

.. literalinclude:: 
   :language: javascript




Show image details and image binary
===================================

.. rest_method::  GET /v1/images/{image_id}

Shows the image details as headers and the image binary in the body of the response.


Normal response codes: 200
Error response codes:403,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id




Response Example
----------------

.. literalinclude:: ../samples/images-list-details-response.json
   :language: javascript





Show image metadata
===================

.. rest_method::  HEAD /v1/images/{image_id}

Shows the image metadata information in the body of the response.

The Image system does not return a response body for the HEAD
operation.

Example requests and responses:

- Show image metadata:

  ::

     http://glance.example.com/v1/images/03bc0a8b-659c-4de9-b6bd-13c6e86e6455




  ::

     X-Image-Meta-Checksum → 8a40c862b5735975d82605c1dd395796
     X-Image-Meta-Container_format → aki
     X-Image-Meta-Created_at → 2016-01-06T03:22:20.000000
     X-Image-Meta-Deleted → false
     X-Image-Meta-Disk_format → aki
     X-Image-Meta-Id → 03bc0a8b-659c-4de9-b6bd-13c6e86e6455
     X-Image-Meta-Is_public → true
     X-Image-Meta-Min_disk → 0
     X-Image-Meta-Min_ram → 0
     X-Image-Meta-Name → cirros-0.3.4-x86_64-uec-kernel
     X-Image-Meta-Owner → 13cc6052265b41529e2fd0fc461fa8ef
     X-Image-Meta-Protected → false
     X-Image-Meta-Size → 4979632
     X-Image-Meta-Status → deactivated
     X-Image-Meta-Updated_at → 2016-02-25T03:02:05.000000
     X-Openstack-Request-Id → req-d5208320-28ed-4c22-b628-12dc6456d983


If the request succeeds, the operation returns the ``200`` response
code.

If there is an image size mismatch detected with the ``X-Image-
Meta-Size``, the operation returns a ``409`` response code.


Normal response codes: 200
Error response codes:404,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id




Response Example
----------------

.. literalinclude:: 
   :language: javascript






Delete image
============

.. rest_method::  DELETE /v1/images/{image_id}

Deletes an image.

Error response codes:204,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id






List images with details
========================

.. rest_method::  GET /v1/images/detail

Lists all available images with details.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name
   - container_format: container_format
   - disk_format: disk_format
   - status: status
   - size_min: size_min
   - size_max: size_max
   - changes-since: changes-since


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - previous: previous
   - next: next



Response Example
----------------

.. literalinclude:: ../samples/images-list-details-response.json
   :language: javascript



