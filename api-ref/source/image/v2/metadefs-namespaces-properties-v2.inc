.. -*- rst -*-

==================================================================================
Metadata definition properties (since API v2.0) (metadefs, namespaces, properties)
==================================================================================

Creates, lists, shows details for, updates, and deletes metadata
definition properties.


Show property definition
========================

.. rest_method::  GET /v2/metadefs/namespaces/{namespace_id}/properties/{property_name}

Shows the definition for a property.

If you use the ``resource_type`` query parameter, the API removes
the prefix of the resource type from the property name before it
submits the query. This enables you to look for a property name
that starts with a prefix from an associated resource type.

The response body shows a single property entity.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - property_name: property_name
   - namespace_id: namespace_id
   - property_name: property_name
   - resource_type: resource_type


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - additionalItems: additionalItems
   - description: description
   - title: title
   - default: default
   - items: items
   - operators: operators
   - enum: enum
   - maximum: maximum
   - minItems: minItems
   - readonly: readonly
   - minimum: minimum
   - maxItems: maxItems
   - maxLength: maxLength
   - uniqueItems: uniqueItems
   - pattern: pattern
   - type: type
   - minLength: minLength
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/metadef-property-details-response.json
   :language: javascript




Update property definition
==========================

.. rest_method::  PUT /v2/metadefs/namespaces/{namespace_id}/properties/{property_name}

Updates a property definition.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - additionalItems: additionalItems
   - description: description
   - title: title
   - default: default
   - items: items
   - operators: operators
   - enum: enum
   - maximum: maximum
   - minItems: minItems
   - readonly: readonly
   - minimum: minimum
   - property_name: property_name
   - maxItems: maxItems
   - maxLength: maxLength
   - uniqueItems: uniqueItems
   - pattern: pattern
   - type: type
   - minLength: minLength
   - namespace_id: namespace_id
   - property_name: property_name

Request Example
---------------

.. literalinclude:: ../samples/metadef-property-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - additionalItems: additionalItems
   - description: description
   - title: title
   - default: default
   - items: items
   - operators: operators
   - enum: enum
   - maximum: maximum
   - minItems: minItems
   - readonly: readonly
   - minimum: minimum
   - maxItems: maxItems
   - maxLength: maxLength
   - uniqueItems: uniqueItems
   - pattern: pattern
   - type: type
   - minLength: minLength
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/metadef-property-update-response.json
   :language: javascript




Remove property definition
==========================

.. rest_method::  DELETE /v2/metadefs/namespaces/{namespace_id}/properties/{property_name}

Removes a property definition in a namespace.

To remove a property, first make an update namespace request to set
the ``protected`` attribute to false (boolean) on the namespace.
Then, remove the property. If the operation succeeds, the response
returns the HTTP 204 status code.

If you try to remove a property in a namespace with the
``protected`` attribute set to true (boolean), the operation fails
and the response returns the HTTP 403 error code.

Error response codes:403,204,


Request
-------

.. rest_parameters:: parameters.yaml

   - property_name: property_name
   - namespace_id: namespace_id
   - property_name: property_name







Create property
===============

.. rest_method::  POST /v2/metadefs/namespaces/{namespace_id}/properties

Creates a property definition in a namespace.

The schema is a subset of the JSON property definition schema.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml

   - additionalItems: additionalItems
   - description: description
   - title: title
   - default: default
   - items: items
   - operators: operators
   - enum: enum
   - maximum: maximum
   - minItems: minItems
   - readonly: readonly
   - minimum: minimum
   - maxItems: maxItems
   - maxLength: maxLength
   - uniqueItems: uniqueItems
   - pattern: pattern
   - type: type
   - minLength: minLength
   - name: name
   - namespace_id: namespace_id

Request Example
---------------

.. literalinclude:: ../samples/metadef-property-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - additionalItems: additionalItems
   - description: description
   - title: title
   - default: default
   - items: items
   - operators: operators
   - enum: enum
   - maximum: maximum
   - minItems: minItems
   - readonly: readonly
   - minimum: minimum
   - maxItems: maxItems
   - maxLength: maxLength
   - uniqueItems: uniqueItems
   - pattern: pattern
   - type: type
   - minLength: minLength
   - name: name





List property definitions
=========================

.. rest_method::  GET /v2/metadefs/namespaces/{namespace_id}/properties

Lists property definitions in a namespace.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - namespace_id: namespace_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - additionalItems: additionalItems
   - description: description
   - title: title
   - default: default
   - items: items
   - operators: operators
   - enum: enum
   - maximum: maximum
   - minItems: minItems
   - readonly: readonly
   - minimum: minimum
   - maxItems: maxItems
   - maxLength: maxLength
   - uniqueItems: uniqueItems
   - pattern: pattern
   - type: type
   - properties: properties
   - minLength: minLength
   - name: name



Response Example
----------------

.. literalinclude:: ../samples/metadef-properties-list-response.json
   :language: javascript



