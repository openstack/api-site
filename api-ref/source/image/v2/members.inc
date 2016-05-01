.. -*- rst -*-

=========================
Members (images, members)
=========================

Creates, lists, updates, and deletes image members.


Show image member details
=========================

.. rest_method::  GET /v2/images/{image_id}/members/{member_id}

(Since Image API v2.2) Shows image member details.

Response body is a single image member entity.

Preconditions

- The image must exist.

- You must be the owner or a member of the image.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id
   - member_id: member_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - created_at: created_at
   - updated_at: updated_at
   - image_id: image_id
   - member_id: member_id
   - schema: schema



Response Example
----------------

.. literalinclude:: ../samples/image-member-details-response.json
   :language: javascript




Update image member
===================

.. rest_method::  PUT /v2/images/{image_id}/members/{member_id}

(Since Image API v2.1) Sets the status for an image member.

Preconditions

- The images must exist.

- You must be a member of the image.

Synchronous Postconditions

- If you update the member status to ``accepted`` and have the
  correct permissions, you see the image in list images responses.

- With correct permissions, you can make API calls to see the
  updated member status of the image.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - status: status
   - image_id: image_id
   - member_id: member_id

Request Example
---------------

.. literalinclude:: ../samples/image-member-update-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - created_at: created_at
   - schema: schema
   - updated_at: updated_at
   - member_id: member_id



Response Example
----------------

.. literalinclude:: ../samples/image-member-update-response.json
   :language: javascript




Delete image member
===================

.. rest_method::  DELETE /v2/images/{image_id}/members/{member_id}

(Since Image API v2.1) Deletes a tenant ID from the member list of an image.

Preconditions

- The image must exist.

- You must be the owner of the image.

Synchronous Postconditions

- The API removes the member from the image members.

Troubleshooting

- Even if you have correct permissions, if you are not the owner of
  the image or you specify an incorrect image ID or member ID, the
  call returns the HTTP ``403`` or ``404`` response code. Ensure
  that you meet the preconditions and run the request again. If the
  request fails again, review your API request URI.

Error response codes:404,403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id
   - member_id: member_id








List image members
==================

.. rest_method::  GET /v2/images/{image_id}/members

(Since Image API v2.1) Lists the tenants that share this image.

If a user who shares this image makes this call, the member list
contains only information for that user.

If a user who does not share this image makes this call, the call
returns the HTTP ``404`` response code.

Preconditions

- The image must exist.

- You must be the owner or a member of the image.


Normal response codes: 200
Error response codes:404,


Request
-------

.. rest_parameters:: parameters.yaml

   - image_id: image_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - created_at: created_at
   - updated_at: updated_at
   - members: members
   - schema: schema



Response Example
----------------

.. literalinclude:: ../samples/image-members-list-response.json
   :language: javascript





Create image member
===================

.. rest_method::  POST /v2/images/{image_id}/members

(Since Image API v2.1) Adds a tenant ID as an image member.

This call accepts either the ``member_id`` or ``member`` attribute
in the request body. If you specify both attributes, the API uses
the ``member_id`` value and ignores the ``member`` value. Use of
the ``member`` attribute is supported but deprecated. Use of the
``member_id`` attribute is preferred.

Preconditions

- The images must exist.

- You can add a member to a private image.

- You must be the owner of the image.

Synchronous Postconditions

- With correct permissions, you can see the member status of the
  image as ``pending`` through API calls.

Troubleshooting

- Even if you have correct permissions, if the ``visibility``
  attribute is set to ``public``, the request returns the HTTP
  ``403`` response code. Ensure that you meet the preconditions and
  run the request again. If the request fails again, review your
  API request.

- If the member is already a member for the image, the service
  returns the ``Conflict (409)`` response code. If you meant to
  specify a different member, run the request again.


Normal response codes: 200
Error response codes:403,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - member: member
   - member_id: member_id
   - image_id: image_id

Request Example
---------------

.. literalinclude:: ../samples/image-member-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - created_at: created_at
   - schema: schema
   - updated_at: updated_at
   - member_id: member_id



Response Example
----------------

.. literalinclude:: ../samples/image-member-create-response.json
   :language: javascript





