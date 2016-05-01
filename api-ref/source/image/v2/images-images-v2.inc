.. -*- rst -*-

===============
Images (images)
===============

Creates, lists, updates, and deletes images.

Image operations show all fields in the response body. Any field
with no value is set to ``null`` value (JSON null data type).

The possible status values for images are:

**Image status**

+----------------+---------------------------------------------------------------------+
| Status         | Description                                                         |
+----------------+---------------------------------------------------------------------+
| queued         | The Image service reserved an image ID for the image in the         |
|                | registry but did not yet upload any image data.                     |
+----------------+---------------------------------------------------------------------+
| saving         | The Image service is currently uploading the raw data for the       |
|                | image.                                                              |
+----------------+---------------------------------------------------------------------+
| active         | The image is active and fully available in the Image service.       |
+----------------+---------------------------------------------------------------------+
| killed         | An image data upload error occurred.                                |
+----------------+---------------------------------------------------------------------+
| deleted        | The Image service retains information about the image but the image |
|                | is no longer available for use.                                     |
+----------------+---------------------------------------------------------------------+
| pending_delete | Similar to the ``deleted`` status. An image in this state is not    |
|                | recoverable.                                                        |
+----------------+---------------------------------------------------------------------+


Update image
============

.. rest_method::  PATCH /v2/images/{image_id}

(Since Image API v2.0) Updates an image.

Depending on the referenced target location, this operation
performs one of these actions:

**Image update actions**

+--------------------------------------+----------------------------------------------------------+
| Target location                      | Update action                                            |
+--------------------------------------+----------------------------------------------------------+
| An array index                       | The API inserts a new value into the array at the index. |
+--------------------------------------+----------------------------------------------------------+
| An object member that does not exist | The API adds a member to the object.                     |
+--------------------------------------+----------------------------------------------------------+
| An object member that exists         | The member value is replaced.                            |
+--------------------------------------+----------------------------------------------------------+

The operation object must contain a ``value`` member that contains
the value to add. For example:

.. code-block:: json

   {
       "op": "add",
       "path": "/a/b/c",
       "value": [
           "foo",
           "bar"
       ]
   }

The target location must reference one of these values:

- The root of the target document. The value is the entire content
  of the target document.

- A member value to add to an object. The API adds the value to the
  object at the location. If the member already exists, the API
  replaces it with the value.

- An element to add to the array. The API adds the element value to
  the array at the location. The API shifts any element that is at
  or above the index one position to the right. The index must not
  be greater than the number of elements in the array. If you use
  the hyphen (-) character to index the end of the array, the API
  appends the value to the array. See `JavaScript Object Notation
  (JSON) Pointer <http://tools.ietf.org/html/rfc6901>`_.

Because this operation adds to existing objects and arrays, its
target location often does not exist.

The request body must conform to one of these media types:

- ``application/openstack-images-v2.0-json-patch``

- ``application/openstack-images-v2.1-json-patch`` (since Image API
  v2.2)

You can also use the PATCH method to add or remove image
properties.

For information about the PATCH method and the available media
types, see `Image API v2 HTTP PATCH media types
<http://specs.openstack.org/openstack/glance-specs/specs/api/v2
/http-patch-image-api-v2.html>`_.

Preconditions

- When you add a location to or replace a location in the image, you
  must set the ``disk_format`` and ``container_format`` parameters
  in the image.

- When you replace a location, that location must be previously set
  in the image.

Synchronous Postconditions

- With correct permissions, you can view the updated values of the
  attributes of the image.

- After you add a location to an image that had no location and with
  correct permissions, you can use API calls to view the image
  status as ``active``.

- After you remove all locations from the image and with correct
  permissions, you can use API calls to view the image status as
  ``queued``.

Troubleshooting

- If you cannot update locations, your request might be missing some
  information. Make sure that you meet the preconditions and run
  the request again. If the request fails again, review your API
  request.


Normal response codes: 200
Error response codes:404,


Request
-------

.. rest_parameters:: parameters.yaml

   - url: url
   - path: path
   - op: op
   - value: value
   - metadata: metadata
   - image_id: image_id

Request Example
---------------

.. literalinclude:: ../samples/image-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - container_format: container_format
   - min_ram: min_ram
   - updated_at: updated_at
   - file: file
   - owner: owner
   - id: id
   - size: size
   - self: self
   - disk_format: disk_format
   - direct_url: direct_url
   - schema: schema
   - status: status
   - tags: tags
   - visibility: visibility
   - locations: locations
   - min_disk: min_disk
   - properties: properties
   - name: name
   - checksum: checksum
   - created_at: created_at
   - protected: protected
   - metadata: metadata



Response Example
----------------

.. literalinclude:: ../samples/image-update-response.json
   :language: javascript





Show image details
==================

.. rest_method::  GET /v2/images/{image_id}

(Since Image API v2.0) Shows details for an image.

The response body contains a single image entity.

Preconditions

- The image must exist.


Normal response codes: 200
Error response codes:404,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - container_format: container_format
   - min_ram: min_ram
   - updated_at: updated_at
   - file: file
   - owner: owner
   - id: id
   - size: size
   - self: self
   - disk_format: disk_format
   - direct_url: direct_url
   - schema: schema
   - status: status
   - tags: tags
   - visibility: visibility
   - locations: locations
   - min_disk: min_disk
   - properties: properties
   - name: name
   - checksum: checksum
   - created_at: created_at
   - protected: protected
   - metadata: metadata



Response Example
----------------

.. literalinclude:: ../samples/image-show-response.json
   :language: javascript





Delete image
============

.. rest_method::  DELETE /v2/images/{image_id}

(Since Image API v2.0) Deletes an image.

You cannot delete images with the ``protected`` attribute set to
``true`` (boolean).

Preconditions

- You can delete an image in any status except ``deleted``.

- First, set the ``protected`` attribute to ``false`` (boolean).
  Then, perform the delete.

Synchronous Postconditions

- The response is empty and returns the HTTP ``204`` response code.

- The API deletes the image from the images index.

- If the image stores binary image data in the storage node, the
  OpenStack Image service deletes the data from the node.

Troubleshooting

- The call returns the HTTP ``403`` response code when the
  ``protected`` attribute is set to ``true`` even if you have
  correct permissions. Ensure that you meet the preconditions and
  run the request again. If the request fails again, review your
  API request.

Error response codes:404,403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id








Reactivate image
================

.. rest_method::  POST /v2/images/{image_id}/actions/reactivate

(Since Image API v2.0) Reactivates an image.

The reactivate operation returns an error if the image status is
not ``active`` or ``deactivated``.

Preconditions

- The image must exist.

Error response codes:404,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id







List images
===========

.. rest_method::  GET /v2/images

(Since Image API v2.0) Lists public virtual machine (VM) images.

Returns a subset of the larger collection of images and a link that
you can use to get the next set of images. You should always check
for the presence of a ``next`` link and use it as the URI in a
subsequent HTTP GET request. You should follow this pattern until a
``next`` link is no longer provided. The next link preserves any
query parameters that you send in your initial request. You can use
the ``first`` link to jump back to the first page of the
collection. If you prefer to paginate through images manually, use
the ``limit`` and ``marker`` parameters.

The list operation accepts query parameters to filter the response.

A client can provide direct comparison filters by using most image
attributes, such as ``name=Ubuntu``, ``visibility=public``, and so
on. A client cannot use tags or any ``link`` in the json-schema,
such as self, file, or schema, to filter the response.

You can use the ``size_min`` and ``size_max`` query parameters to
filter images that are greater than or less than the image size.
The size, in bytes, is the size of an image on disk.

For example, to filter the container to include only images that
are from 1 to 4 MB, set the ``size_min`` query parameter to
``1048576`` and the ``size_max`` query parameter to ``4194304``.

You can list VM images that have a status of ``active``,
``queued``, or ``saving``.

You can use query parameters to sort the results of this operation.

- ``sort_key``. Sorts by an image attribute. Sorts in the natural
  sorting direction of the image attribute.

- ``sort_dir``. Sorts in a sort direction.

- ``sort``. Sorts by one or more sets of attribute and sort
  direction combinations. If you omit the sort direction in a set,
  the default is ``desc``.

To sort the response, use the ``sort_key`` and ``sort_dir`` query
parameters:

.. code-block:: json

   GET /v2/images?sort_key=name
   &
   sort_dir=asc
   &
   sort_key=status
   &
   sort_dir=desc

Alternatively, specify the ``sort`` query parameter:

.. code-block:: json

   GET /v2/images?sort=name:asc,status:desc


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - limit: limit
   - marker: marker
   - name: name
   - visibility: visibility
   - member_status: member_status
   - owner: owner
   - status: status
   - size_min: size_min
   - size_max: size_max
   - sort_key: sort_key
   - sort_dir: sort_dir
   - sort: sort
   - tag: tag
   - created_at: created_at
   - updated_at: updated_at


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - min_ram: min_ram
   - status: status
   - virtual_size: virtual_size
   - name: name
   - tags: tags
   - checksum: checksum
   - created_at: created_at
   - size: size
   - disk_format: disk_format
   - updated_at: updated_at
   - owner: owner
   - self: self
   - min_disk: min_disk
   - protected: protected
   - visibility: visibility
   - file: file
   - container_format: container_format
   - images: images
   - schema: schema
   - id: id
   - first: first



Response Example
----------------

.. literalinclude:: ../samples/images-list-response.json
   :language: javascript




Create image
============

.. rest_method::  POST /v2/images

(Since Image API v2.0) Creates a virtual machine (VM) image.

The ``Location`` response header contains the URI for the image.
The response body contains the new image entity.

Synchronous Postconditions

- With correct permissions, you can see the image status as
  ``queued`` through API calls.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name
   - tags: tags
   - container_format: container_format
   - min_ram: min_ram
   - disk_format: disk_format
   - visibility: visibility
   - properties: properties
   - protected: protected
   - min_disk: min_disk
   - id: id

Request Example
---------------

.. literalinclude:: ../samples/image-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - min_ram: min_ram
   - status: status
   - virtual_size: virtual_size
   - name: name
   - tags: tags
   - updated_at: updated_at
   - checksum: checksum
   - created_at: created_at
   - disk_format: disk_format
   - locations: locations
   - visibility: visibility
   - properties: properties
   - self: self
   - owner: owner
   - protected: protected
   - file: file
   - container_format: container_format
   - min_disk: min_disk
   - size: size
   - id: id
   - schema: schema





Deactivate image
================

.. rest_method::  POST /v2/images/{image_id}/actions/deactivate

(Since Image API v2.0) Deactivates an image.

If you try to download a deactivated image, the call returns the
``Forbidden (403)`` response code. Also, only administrative users
can view image locations for deactivated images.

The deactivate operation returns an error if the image status is
not ``active`` or ``deactivated``.

Preconditions

- The image must exist.

Error response codes:404,403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id







