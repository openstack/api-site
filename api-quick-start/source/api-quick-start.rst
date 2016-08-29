.. _openstack_API_quick_guide:

==============
OpenStack APIs
==============

To authenticate access to OpenStack services, you must first issue an
authentication request with a payload of credentials to OpenStack Identity to
get an authentication token.

Credentials are usually a combination of your user name and password,
and optionally, the name or ID of the tenant where your cloud runs.
Ask your cloud administrator for your user name, password, and tenant so
that you can generate authentication tokens. Alternatively, you can
supply a token rather than a user name and password.

When you send API requests, you include the token in the ``X-Auth-Token``
header. If you access multiple OpenStack services, you must get a token for
each service. A token is valid for a limited time before it expires. A token
can also become invalid for other reasons. For example, if the roles for a
user change, existing tokens for that user are no longer valid.

Authentication and API request workflow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#. Request an authentication token from the Identity endpoint that your
   cloud administrator gave you. Send a payload of credentials in the
   request as shown in :ref:`authenticate`. If the request succeeds, the server
   returns an authentication token.

#. Send API requests and include the token in the ``X-Auth-Token``
   header. Continue to send API requests with that token until the service
   completes the request or the Unauthorized (401) error occurs.

#. If the Unauthorized (401) error occurs, request another token.

The examples in this section use cURL commands. For information about cURL,
see http://curl.haxx.se/. For information about the OpenStack APIs, see
`OpenStack API Reference <http://developer.openstack.org/api-ref.html>`__.


.. _authenticate:

Authenticate
~~~~~~~~~~~~

The payload of credentials to authenticate contains these parameters:

+-----------------------+----------------+--------------------------------------+
| Parameter             | Type           | Description                          |
+=======================+================+======================================+
| username (required)   | xsd:string     | The user name. If you do not provide |
|                       |                | a user name and password, you must   |
|                       |                | provide a token.                     |
+-----------------------+----------------+--------------------------------------+
| password (required)   | xsd:string     | The password for the user.           |
+-----------------------+----------------+--------------------------------------+
| *tenantName*          | xsd:string     | The tenant name. Both the            |
| (Optional)            |                | *tenantId* and *tenantName*          |
|                       |                | are optional and mutually exclusive. |
|                       |                | If you specify both attributes, the  |
|                       |                | server returns the Bad Request (400) |
|                       |                | response code.                       |
+-----------------------+----------------+--------------------------------------+
| *tenantId*            | xsd:string     | The tenant ID. Both the *tenantId*   |
| (Optional)            |                | and *tenantName* are optional and    |
|                       |                | mutually exclusive. If you specify   |
|                       |                | both attributes, the server returns  |
|                       |                | the Bad Request (400) response code. |
|                       |                | If you do not know the tenant name   |
|                       |                | or ID, send a request with "" for    |
|                       |                | the tenant name or ID. The response  |
|                       |                | returns the tenant name or ID.       |
+-----------------------+----------------+--------------------------------------+
| token (Optional)      | xsd:string     | A token. If you do not provide a     |
|                       |                | token, you must provide a user name  |
|                       |                | and password.                        |
+-----------------------+----------------+--------------------------------------+


In a typical OpenStack deployment that runs Identity, you can specify your
tenant name, and user name and password credentials to authenticate.

First, export your tenant name to the `OS_PROJECT_NAME` environment variable,
your user name to the `OS_USERNAME` environment variable, and your password to
the `OS_PASSWORD` environment variable. The example below uses a TryStack endpoint
but you can also use `$OS_IDENTITYENDPOINT` as an environment variable as needed.

Then, run this cURL command to request a token:

.. code-block:: console

   $ curl -s -X POST $OS_AUTH_URL/tokens \
     -H "Content-Type: application/json" \
     -d '{"auth": {"tenantName": "'"$OS_PROJECT_NAME"'", "passwordCredentials": {"username": "'"$OS_USERNAME"'", "password": "'"$OS_PASSWORD"'"}}}' \
     | python -m json.tool

If the request succeeds, it returns the ``OK (200)`` response code followed by a
response body that contains a token in the form ``"id":"token"`` and an
expiration date and time in the form ``"expires":"datetime"``.

.. note::

   If you do not know the tenant name or ID, send a request with "" for the
   tenant name or ID. The response returns the tenant name or ID.

   .. code-block:: console

      $ curl -s -X POST $OS_AUTH_URL/tokens \
        -H "Content-Type: application/json" \
        -d '{"auth": {"tenantName": "", "passwordCredentials": {"username": "'"$OS_USERNAME"'", "password": "'"$OS_PASSWORD"'"}}}' \
        | python -m json.tool

The following example shows a successful response:

.. code-block:: json

   {
       "access": {
           "metadata": {
               "is_admin": 0,
               "roles": [
                   "9fe2ff9ee4384b1894a90878d3e92bab"
               ]
           },
           "serviceCatalog": [
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:8774/v2/2a124051e083457091cecc3aa553a5a9",
                           "id": "9484a876103048d6b6061405292a69ec",
                           "internalURL": "http://172.16.1.2:8774/v2/2a124051e083457091cecc3aa553a5a9",
                           "publicURL": "http://128.136.179.2:8774/v2/2a124051e083457091cecc3aa553a5a9",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "nova",
                   "type": "compute"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:9696/",
                           "id": "48bb1eaac6004287b569171d6eff3a8b",
                           "internalURL": "http://172.16.1.2:9696/",
                           "publicURL": "http://128.136.179.2:9696/",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "neutron",
                   "type": "network"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:8776/v2/2a124051e083457091cecc3aa553a5a9",
                           "id": "4914cc64592048ab823beeed6ff58add",
                           "internalURL": "http://172.16.1.2:8776/v2/2a124051e083457091cecc3aa553a5a9",
                           "publicURL": "http://128.136.179.2:8776/v2/2a124051e083457091cecc3aa553a5a9",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "cinderv2",
                   "type": "volumev2"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:8779/v1.0/2a124051e083457091cecc3aa553a5a9",
                           "id": "255f5bcfd284485ebf033f7488a1a0bd",
                           "internalURL": "http://172.16.1.2:8779/v1.0/2a124051e083457091cecc3aa553a5a9",
                           "publicURL": "http://128.136.179.2:8779/v1.0/2a124051e083457091cecc3aa553a5a9",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "trove",
                   "type": "database"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://128.136.179.2:8080",
                           "id": "18c55bdb3f4044958cc2257a9345d921",
                           "internalURL": "http://172.16.1.2:8080",
                           "publicURL": "http://128.136.179.2:8080",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "swift_s3",
                   "type": "s3"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:9292",
                           "id": "2b8be454ac394e4bb482c88a1876c987",
                           "internalURL": "http://172.16.1.2:9292",
                           "publicURL": "http://128.136.179.2:9292",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "glance",
                   "type": "image"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:8774/v3",
                           "id": "b806c63677334f5c8318234a9f8ce6be",
                           "internalURL": "http://172.16.1.2:8774/v3",
                           "publicURL": "http://128.136.179.2:8774/v3",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "novav3",
                   "type": "computev3"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.3:8786/v1/2a124051e083457091cecc3aa553a5a9",
                           "id": "83daad78b4e94ff98ed0dc9384d2287b",
                           "internalURL": "http://172.16.1.3:8786/v1/2a124051e083457091cecc3aa553a5a9",
                           "publicURL": "http://128.136.179.2:8786/v1/2a124051e083457091cecc3aa553a5a9",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "manila",
                   "type": "share"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:8777",
                           "id": "4d6b384ae0ad4f9c840d9841d2558fc2",
                           "internalURL": "http://172.16.1.2:8777",
                           "publicURL": "http://128.136.179.2:8777",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "ceilometer",
                   "type": "metering"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:8776/v1/2a124051e083457091cecc3aa553a5a9",
                           "id": "0504d7f8035a4149ba41842bae498a10",
                           "internalURL": "http://172.16.1.2:8776/v1/2a124051e083457091cecc3aa553a5a9",
                           "publicURL": "http://128.136.179.2:8776/v1/2a124051e083457091cecc3aa553a5a9",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "cinder",
                   "type": "volume"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:8773/services/Admin",
                           "id": "5b8d4c3357e04be78a8eb928a839cdd7",
                           "internalURL": "http://172.16.1.2:8773/services/Cloud",
                           "publicURL": "http://128.136.179.2:8773/services/Cloud",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "nova_ec2",
                   "type": "ec2"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://128.136.179.2:8080/",
                           "id": "1a4c96b000de4474908e45460017bf00",
                           "internalURL": "http://172.16.1.2:8080/v1/AUTH_2a124051e083457091cecc3aa553a5a9",
                           "publicURL": "http://128.136.179.2:8080/v1/AUTH_2a124051e083457091cecc3aa553a5a9",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "swift",
                   "type": "object-store"
               },
               {
                   "endpoints": [
                       {
                           "adminURL": "http://172.16.1.2:35357/v2.0",
                           "id": "40c9824d67dc4ef5b3b9495e117719a2",
                           "internalURL": "http://172.16.1.2:5000/v2.0",
                           "publicURL": "http://128.136.179.2:5000/v2.0",
                           "region": "RegionOne"
                       }
                   ],
                   "endpoints_links": [],
                   "name": "keystone",
                   "type": "identity"
               }
           ],
           "token": {
               "audit_ids": [
                   "a8ozqFkkSfCmUQpbCZlS-w"
               ],
               "expires": "2015-11-05T23:23:27Z",
               "id": "4b57c7d386a7438b829d1a8922e0eaac",
               "issued_at": "2015-11-05T22:23:27.166658",
               "tenant": {
                   "description": "Auto created account",
                   "enabled": true,
                   "id": "2a124051e083457091cecc3aa553a5a9",
                   "name": "facebook987654321"
               }
           },
           "user": {
               "id": "182d9ad16c2a4397bdceb595658b830f",
               "name": "facebook987654321",
               "roles": [
                   {
                       "name": "_member_"
                   }
               ],
               "roles_links": [],
               "username": "facebook987654321"
           }
       }
   }

Send API requests
~~~~~~~~~~~~~~~~~

This section shows how to make some basic Compute API calls. For a complete
list of Compute API calls, see
`Compute API <http://developer.openstack.org/api-ref/compute/>`__.

Export the token ID to the ``OS_TOKEN`` environment variable. For example:

.. code-block:: console

   export OS_TOKEN=4b57c7d386a7438b829d1a8922e0eaab

The token expires every hour by default,
though it can be configured differently - see
the ``expiration`` option in the
``Description of token configuration options`` section of the
`Identity Service Configuration <http://docs.openstack.org/mitaka/config-reference/identity/options.html#keystone-token>`__ page.

Export the tenant name to the ``OS_PROJECT_NAME`` environment variable. For example:

.. code-block:: console

   export OS_PROJECT_NAME=demo

Then, use the Compute API to list flavors, substituting the Compute API endpoint with
one containing your project ID below:

.. code-block:: console

   $ curl -s -H "X-Auth-Token: $OS_TOKEN" \
     $OS_COMPUTE_API/flavors \
     | python -m json.tool

.. code-block:: json

   {
       "flavors": [
           {
               "id": "1",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/flavors/1",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/flavors/1",
                       "rel": "bookmark"
                   }
               ],
               "name": "m1.tiny"
           },
           {
               "id": "2",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/flavors/2",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/flavors/2",
                       "rel": "bookmark"
                   }
               ],
               "name": "m1.small"
           },
           {
               "id": "3",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/flavors/3",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/flavors/3",
                       "rel": "bookmark"
                   }
               ],
               "name": "m1.medium"
           },
           {
               "id": "4",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/flavors/4",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/flavors/4",
                       "rel": "bookmark"
                   }
               ],
               "name": "m1.large"
           },
           {
               "id": "5",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/flavors/5",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/flavors/5",
                       "rel": "bookmark"
                   }
               ],
               "name": "m1.xlarge"
           }
       ]
   }

Export the $OS_PROJECT_ID from the token call, and then
use the Compute API to list images:

.. code-block:: console

   $ curl -s -H "X-Auth-Token: $OS_TOKEN" \
     http://8.21.28.222:8774/v2/$OS_PROJECT_ID/images \
     | python -m json.tool

.. code-block:: json

   {
       "images": [
           {
               "id": "2dadcc7b-3690-4a1d-97ce-011c55426477",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/images/2dadcc7b-3690-4a1d-97ce-011c55426477",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/images/2dadcc7b-3690-4a1d-97ce-011c55426477",
                       "rel": "bookmark"
                   },
                   {
                       "href": "http://8.21.28.222:9292/f9828a18c6484624b571e85728780ba8/images/2dadcc7b-3690-4a1d-97ce-011c55426477",
                       "type": "application/vnd.openstack.image",
                       "rel": "alternate"
                   }
               ],
               "name": "Fedora 21 x86_64"
           },
           {
               "id": "cfba3478-8645-4bc8-97e8-707b9f41b14e",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/images/cfba3478-8645-4bc8-97e8-707b9f41b14e",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/images/cfba3478-8645-4bc8-97e8-707b9f41b14e",
                       "rel": "bookmark"
                   },
                   {
                       "href": "http://8.21.28.222:9292/f9828a18c6484624b571e85728780ba8/images/cfba3478-8645-4bc8-97e8-707b9f41b14e",
                       "type": "application/vnd.openstack.image",
                       "rel": "alternate"
                   }
               ],
               "name": "Ubuntu 14.04 amd64"
           },
           {
               "id": "2e4c08a9-0ecd-4541-8a45-838479a88552",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/images/2e4c08a9-0ecd-4541-8a45-838479a88552",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/images/2e4c08a9-0ecd-4541-8a45-838479a88552",
                       "rel": "bookmark"
                   },
                   {
                       "href": "http://8.21.28.222:9292/f9828a18c6484624b571e85728780ba8/images/2e4c08a9-0ecd-4541-8a45-838479a88552",
                       "type": "application/vnd.openstack.image",
                       "rel": "alternate"
                   }
               ],
               "name": "CentOS 7 x86_64"
           },
           {
               "id": "c8dd9096-60c1-4e23-a486-82955481df9f",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/images/c8dd9096-60c1-4e23-a486-82955481df9f",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/images/c8dd9096-60c1-4e23-a486-82955481df9f",
                       "rel": "bookmark"
                   },
                   {
                       "href": "http://8.21.28.222:9292/f9828a18c6484624b571e85728780ba8/images/c8dd9096-60c1-4e23-a486-82955481df9f",
                       "type": "application/vnd.openstack.image",
                       "rel": "alternate"
                   }
               ],
               "name": "CentOS 6.5 x86_64"
           },
           {
               "id": "f97b8d36-935e-4666-9c58-8a0afc6d3796",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f9828a18c6484624b571e85728780ba8/images/f97b8d36-935e-4666-9c58-8a0afc6d3796",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f9828a18c6484624b571e85728780ba8/images/f97b8d36-935e-4666-9c58-8a0afc6d3796",
                       "rel": "bookmark"
                   },
                   {
                       "href": "http://8.21.28.222:9292/f9828a18c6484624b571e85728780ba8/images/f97b8d36-935e-4666-9c58-8a0afc6d3796",
                       "type": "application/vnd.openstack.image",
                       "rel": "alternate"
                   }
               ],
               "name": "Fedora 20 x86_64"
           }
       ]
   }

Export the $OS_PROJECT_ID from the token call, and then
use the Compute API to list servers:

.. code-block:: console

   $ curl -s -H "X-Auth-Token: $OS_TOKEN" \
     http://8.21.28.222:8774/v2/$OS_PROJECT_ID/servers \
     | python -m json.tool

.. code-block:: json

   {
       "servers": [
           {
               "id": "41551256-abd6-402c-835b-e87e559b2249",
               "links": [
                   {
                       "href": "http://8.21.28.222:8774/v2/f8828a18c6484624b571e85728780ba8/servers/41551256-abd6-402c-835b-e87e559b2249",
                       "rel": "self"
                   },
                   {
                       "href": "http://8.21.28.222:8774/f8828a18c6484624b571e85728780ba8/servers/41551256-abd6-402c-835b-e87e559b2249",
                       "rel": "bookmark"
                   }
               ],
               "name": "test-server"
           }
       ]
   }

.. _client-intro:

OpenStack command-line clients
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For scripting work and simple requests, you can use a command-line client like
the ``openstack-client`` client. This client enables you to use the Identity,
Compute, Block Storage, and Object Storage APIs through a command-line
interface. Also, each OpenStack project has a related client project that
includes Python API bindings and a command-line interface (CLI).

For information about the command-line clients, see `OpenStack
Command-Line Interface Reference <http://docs.openstack.org/cli-reference/>`__.

Install the clients
-------------------

Use ``pip`` to install the OpenStack clients on a Mac OS X or Linux system. It
is easy and ensures that you get the latest version of the client from the
`Python Package Index <http://pypi.python.org/pypi>`__. Also, ``pip`` lets you
update or remove a package.

You must install the client for each project separately, but the
``python-openstackclient`` covers multiple projects.

Install or update a client package:

.. code-block:: console

   $ sudo pip install [--upgrade] python-PROJECTclient

Where *PROJECT* is the project name.

For example, install the ``openstack`` client:

.. code-block:: console

   $ sudo pip install python-openstackclient

To update the ``openstack`` client, run this command:

.. code-block:: console

   $ sudo pip install --upgrade python-openstackclient

To remove the ``openstack`` client, run this command:

.. code-block:: console

   $ sudo pip uninstall python-openstackclient

Before you can issue client commands, you must download and source the
``openrc`` file to set environment variables.

For complete information about the OpenStack clients, including how to source
the ``openrc`` file, see `OpenStack End User Guide <http://docs.openstack.org/user-guide/>`__,
`OpenStack Administrator Guide <http://docs.openstack.org/admin-guide/>`__,
and `OpenStack Command-Line Interface Reference <http://docs.openstack.org/cli-reference/>`__.

Launch an instance
------------------

To launch instances, you must choose a name, an image, and a flavor for
your instance.

To list available images, call the Compute API through the ``openstack``
client:

.. code-block:: console

   $ openstack image list

.. code-block:: console

   +--------------------------------------+------------------+
   | ID                                   | Name             |
   +--------------------------------------+------------------+
   | a5604931-af06-4512-8046-d43aabf272d3 | fedora-20.x86_64 |
   +--------------------------------------+------------------+

To list flavors, run this command:

.. code-block:: console

   $ openstack flavor list

.. code-block:: console

   +----+-----------+-----------+------+-----------+------+-------+-----------+
   | ID | Name      | Memory_MB | Disk | Ephemeral | Swap | VCPUs | Is_Public |
   +----+-----------+-----------+------+-----------+------+-------+-----------+
   | 1  | m1.tiny   | 512       | 0    | 0         |      | 1     | True      |
   | 2  | m1.small  | 2048      | 20   | 0         |      | 1     | True      |
   | 3  | m1.medium | 4096      | 40   | 0         |      | 2     | True      |
   | 4  | m1.large  | 8192      | 80   | 0         |      | 4     | True      |
   | 42 | m1.nano   | 64        | 0    | 0         |      | 1     | True      |
   | 5  | m1.xlarge | 16384     | 160  | 0         |      | 8     | True      |
   | 84 | m1.micro  | 128       | 0    | 0         |      | 1     | True      |
   +----+-----------+-----------+------+-----------+------+-------+-----------+

To launch an instance, note the IDs of your desired image and flavor.

To launch the ``my_instance`` instance, run the ``openstack server create``
command with the image and flavor IDs and the server name:

.. code-block:: console

   $ openstack server create --image a5604931-af06-4512-8046-d43aabf272d3 --flavor 1 my_instance

.. code-block:: console

   +--------------------------------------+---------------------------------------------------------+
   | Field                                | Value                                                   |
   +--------------------------------------+---------------------------------------------------------+
   | OS-DCF:diskConfig                    | MANUAL                                                  |
   | OS-EXT-AZ:availability_zone          | nova                                                    |
   | OS-EXT-STS:power_state               | 0                                                       |
   | OS-EXT-STS:task_state                | scheduling                                              |
   | OS-EXT-STS:vm_state                  | building                                                |
   | OS-SRV-USG:launched_at               | None                                                    |
   | OS-SRV-USG:terminated_at             | None                                                    |
   | accessIPv4                           |                                                         |
   | accessIPv6                           |                                                         |
   | addresses                            |                                                         |
   | adminPass                            | 3vgzpLzChoac                                            |
   | config_drive                         |                                                         |
   | created                              | 2015-08-27T03:02:27Z                                    |
   | flavor                               | m1.tiny (1)                                             |
   | hostId                               |                                                         |
   | id                                   | 1553694c-d711-4954-9b20-84b8cb4598c6                    |
   | image                                | fedora-20.x86_64 (a5604931-af06-4512-8046-d43aabf272d3) |
   | key_name                             | None                                                    |
   | name                                 | my_instance                                             |
   | os-extended-volumes:volumes_attached | []                                                      |
   | progress                             | 0                                                       |
   | project_id                           | 9f0e4aa4fd3d4b0ea3184c0fe7a32210                        |
   | properties                           |                                                         |
   | security_groups                      | [{u'name': u'default'}]                                 |
   | status                               | BUILD                                                   |
   | updated                              | 2015-08-27T03:02:28Z                                    |
   | user_id                              | b3ce0cfc170641e98ff5e42b1be9c85a                        |
   +--------------------------------------+---------------------------------------------------------+

.. note::
   For information about the default ports that the OpenStack components use,
   see `Firewalls and default ports <http://docs.openstack.org/liberty/
   config-reference/content/firewalls-default-ports.html>`_ in the
   *OpenStack Configuration Reference*.
