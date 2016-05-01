.. -*- rst -*-

=========================
Image data (images, file)
=========================

Uploads and downloads raw image data.


Upload binary image data
========================

.. rest_method::  PUT /v2/images/{image_id}/file

(Since Image API v2.0) Uploads binary image data.

Set the ``Content-Type`` request header to ``application/octet-
stream``.

Example call:

::

   curl -i -X PUT -H "X-Auth-Token: $token" -H "Content-Type: application/octet-stream" \
      -d @/home/glance/ubuntu-12.10.qcow2 $image_url/v2/images/{image_id}/file

Preconditions

Before you can store binary image data, you must meet the following
preconditions:

- The image must exist.

- You must set the disk and container formats in the image.

- The image status must be ``queued``.

- Your image storage quota must be sufficient.

- The size of the data that you want to store must not exceed the
  size that the OpenStack Image service allows.

Synchronous Postconditions

- With correct permissions, you can see the image status as
  ``active`` through API calls.

- With correct access, you can see the stored data in the storage
  system that OpenStack Image service manages.

Troubleshooting

- If you cannot store the data, either your request lacks required
  information or you exceeded your allotted quota. Ensure that you
  meet the preconditions and run the request again. If the request
  fails again, review your API request.

- The storage back ends for storing the data must have enough free
  storage space to accommodate the size of the data.

Error response codes:204,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id






Download binary image data
==========================

.. rest_method::  GET /v2/images/{image_id}/file

(Since Image API v2.0) Downloads binary image data.

Example call: ``curl -i -X GET -H "X-Auth-Token: $token"
$image_url/v2/images/{image_id}/file``

The response body contains the raw binary data that represents the
actual virtual disk. The ``Content-Type`` header contains the
``application/octet-stream`` value. The ``Content-MD5`` header
contains an MD5 checksum of the image data. Use this checksum to
verify the integrity of the image data.



Preconditions

- The images must exist.

Synchronous Postconditions

- You can download the binary image data in your machine if the
  image has image data.

- If image data exists, the call returns the HTTP ``200`` response
  code.

- If no image data exists, the call returns the HTTP ``204``
  response code.


Normal response codes: 200
Error response codes:404,403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id
   - Content-Range: Content-Range




Response Example
----------------

.. literalinclude:: 
   :language: javascript






