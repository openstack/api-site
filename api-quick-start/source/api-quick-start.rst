.. _openstack_API_quick_guide:

==============
OpenStack APIs
==============

To authenticate access to OpenStack services, you must first issue an
authentication request to OpenStack Identity to acquire an
authentication token. To request an authentication token, you must
supply a payload of credentials in the authentication request.

Credentials are usually a combination of your user name and password,
and optionally, the name or ID of the tenant in which your cloud runs.
Ask your cloud administrator for your user name, password, and tenant so
that you can generate authentication tokens. Alternatively, you can
supply a token rather than a user name and password.

When you send API requests, you include the token in the
``X-Auth-Token`` header. If you access multiple OpenStack services, you
must get a token for each service. A token is valid for a limited time
before it expires. A token can also become invalid for other reasons.
For example, if the roles for a user change, existing tokens for that
user are invalid.

Authentication and API request workflow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#. Request an authentication token from the Identity endpoint that your
   cloud administrator gave you. Send a payload of credentials in the
   request as shown in :ref:`authenticate`. If the request succeeds, the server
   returns an authentication token.

#. Send API requests and include the token in the ``X-Auth-Token``
   header. Continue to send API requests with that token until the service
   completes the request or a 401 Unauthorized error occurs.

#. If the 401 Unauthorized error occurs, request another token.

The examples in this section use cURL commands. For information about
cURL, see http://curl.haxx.se/. For information about the OpenStack
APIs, see `OpenStack API
Reference <http://developer.openstack.org/api-ref.html>`__.


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
|                       |                | are optional, but should not be      |
|                       |                | specified together. If both          |
|                       |                | attributes are specified, the server |
|                       |                | responds with a 400 Bad Request.     |
+-----------------------+----------------+--------------------------------------+
| *tenantId*            | xsd:string     | The tenant ID. Both the              |
|  (Optional)           |                | *tenantId* and *tenantName*          |
|                       |                | are optional, but should not be      |
|                       |                | specified together. If both          |
|                       |                | attributes are specified, the server |
|                       |                | responds with a 400 Bad Request. If  |
|                       |                | you do not know the tenantId, you    |
|                       |                | can send a request with "" for the   |
|                       |                | tenantId and get the ID returned to  |
|                       |                | you in the response.                 |
+-----------------------+----------------+--------------------------------------+
| token (Optional)      | xsd:string     | A token. If you do not provide a     |
|                       |                | token, you must provide a user name  |
|                       |                | and password.                        |
+-----------------------+----------------+--------------------------------------+


For a typical OpenStack deployment that runs Identity, use the following cURL
command to request a token with your tenantName and ID:

.. code::

    $ curl -s -X POST http://8.21.28.222:5000/v2.0/tokens \
                -H "Content-Type: application/json" \
                -d '{"auth": {"tenantName": "'"$OS_TENANT_NAME"'", "passwordCredentials":
                {"username": "'"$OS_USERNAME"'", "password": "'"$OS_PASSWORD"'"}}}' \
                | python -m json.tool

If the request succeeds, you receive a 200 OK response followed by a
response body that contains a token in the form ``"id":"token"`` and an
expiration date and time in the form ``"expires":"datetime"``.

.. note::
   If you do not know your tenant name or ID, you can send an
   authentication request with an empty tenantName, as follows:

    .. code::

        $ curl -s -X POST http://8.21.28.222:5000/v2.0/tokens \
                        -H "Content-Type: application/json" \
                        -d '{"auth": {"tenantName": "", "passwordCredentials":
                        {"username": "'"$OS_USERNAME"'", "password": "'"$OS_PASSWORD"'"}}}' \
                        | python -m json.tool

The following example shows a successful response:

.. code::

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
                            "adminURL": "http://10.100.0.222:8774/v2/TENANT_ID",
                            "id": "0eb78b6d3f644438aea327d9c57b7b5a",
                            "internalURL": "http://10.100.0.222:8774/v2/TENANT_ID",
                            "publicURL": "http://8.21.28.222:8774/v2/TENANT_ID",
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
                            "adminURL": "http://10.100.0.222:9696/",
                            "id": "3f4b6015a2f9481481ca03dace8acf32",
                            "internalURL": "http://10.100.0.222:9696/",
                            "publicURL": "http://8.21.28.222:9696/",
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
                            "adminURL": "http://10.100.0.222:8776/v2/TENANT_ID",
                            "id": "16f6416588f64946bdcdf4a431a8f252",
                            "internalURL": "http://10.100.0.222:8776/v2/TENANT_ID",
                            "publicURL": "http://8.21.28.222:8776/v2/TENANT_ID",
                            "region": "RegionOne"
                        }
                    ],
                    "endpoints_links": [],
                    "name": "cinder_v2",
                    "type": "volumev2"
                },
                {
                    "endpoints": [
                        {
                            "adminURL": "http://10.100.0.222:8779/v1.0/TENANT_ID",
                            "id": "be48765ae31e425cb06036b1ebab694a",
                            "internalURL": "http://10.100.0.222:8779/v1.0/TENANT_ID",
                            "publicURL": "http://8.21.28.222:8779/v1.0/TENANT_ID",
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
                            "adminURL": "http://10.100.0.222:9292",
                            "id": "1adfcb5414304f3596fb81edb2dfb514",
                            "internalURL": "http://10.100.0.222:9292",
                            "publicURL": "http://8.21.28.222:9292",
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
                            "adminURL": "http://10.100.0.222:8777",
                            "id": "350f3b91d73f4b3ab8a061c94ac31fbb",
                            "internalURL": "http://10.100.0.222:8777",
                            "publicURL": "http://8.21.28.222:8777",
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
                            "adminURL": "http://10.100.0.222:8000/v1/",
                            "id": "2198b0d32a604e75a5cc1e13276a813d",
                            "internalURL": "http://10.100.0.222:8000/v1/",
                            "publicURL": "http://8.21.28.222:8000/v1/",
                            "region": "RegionOne"
                        }
                    ],
                    "endpoints_links": [],
                    "name": "heat-cfn",
                    "type": "cloudformation"
                },
                {
                    "endpoints": [
                        {
                            "adminURL": "http://10.100.0.222:8776/v1/TENANT_ID",
                            "id": "7c193c4683d849ca8e8db493722a4d8c",
                            "internalURL": "http://10.100.0.222:8776/v1/TENANT_ID",
                            "publicURL": "http://8.21.28.222:8776/v1/TENANT_ID",
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
                            "adminURL": "http://10.100.0.222:8773/services/Admin",
                            "id": "11fac8254be74d7d906110f0069e5748",
                            "internalURL": "http://10.100.0.222:8773/services/Cloud",
                            "publicURL": "http://8.21.28.222:8773/services/Cloud",
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
                            "adminURL": "http://10.100.0.222:8004/v1/TENANT_ID",
                            "id": "38fa4f9afce34d4ca0f5e0f90fd758dd",
                            "internalURL": "http://10.100.0.222:8004/v1/TENANT_ID",
                            "publicURL": "http://8.21.28.222:8004/v1/TENANT_ID",
                            "region": "RegionOne"
                        }
                    ],
                    "endpoints_links": [],
                    "name": "heat",
                    "type": "orchestration"
                },
                {
                    "endpoints": [
                        {
                            "adminURL": "http://10.100.0.222:35357/v2.0",
                            "id": "256cdf78ecb04051bf0f57ec11070222",
                            "internalURL": "http://10.100.0.222:5000/v2.0",
                            "publicURL": "http://8.21.28.222:5000/v2.0",
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
                    "gsjrNoqFSQeuLUo0QeJprQ"
                ],
                "expires": "2014-12-15T15:09:29Z",
                "id": "TOKEN_ID",
                "issued_at": "2014-12-15T14:09:29.794527",
                "tenant": {
                    "description": "Auto created account",
                    "enabled": true,
                    "id": "TENANT_ID",
                    "name": "USERNAME"
                }
            },
            "user": {
                "id": "USER_ID",
                "name": "USERNAME",
                "roles": [
                    {
                        "name": "_member_"
                    }
                ],
                "roles_links": [],
                "username": "USERNAME"
            }
        }
    }

Send API requests
~~~~~~~~~~~~~~~~~

This section shows how to make some basic Compute API calls. For a
complete list of Compute API v2.0 calls, see `Compute APIs and
Extensions <http://developer.openstack.org/api-ref-compute-v2.html>`__.

Use the Compute API to list flavors, as follows:

.. code::

    $ curl -s -H \
                "X-Auth-Token:token" \
                http://8.21.28.222:8774/v2/tenant_id/flavors \
                | python -m json.tool

.. code::

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

Use the Compute API to list images, as follows:

.. code::

    $ curl -s -H \
                "X-Auth-Token:token" \
                http://8.21.28.222:8774/v2/tenant_id/images \
                | python -m json.tool

.. code::

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

Use the Compute API to list servers, as follows:

.. code::

    $ curl -s -H \
                "X-Auth-Token:token" \
                http://8.21.28.222:8774/v2/tenant_id/servers \
                | python -m json.tool

.. code::

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
includes Python API bindings and a CLI.

For information about the command-line clients, see `OpenStack
Command-Line Interface Reference <http://docs.openstack.org/cli-reference/content/>`__.

Install the clients
-------------------

Use ``pip`` to install the OpenStack clients on a Mac OS X or Linux
system. It is easy and ensures that you get the latest version of the
client from the `Python Package Index <http://pypi.python.org/pypi>`__.
Also, ``pip`` lets you update or remove a package.

You must install each project's client separately, but the
python-openstackclient covers multiple projects.

Run this command to install or update a client package:

.. code::

    $ sudo pip install [--upgrade] python-PROJECTclient

Where *PROJECT* is the project name.

For example, to install the ``openstack`` client, run this command:

.. code::

    $ sudo pip install python-openstackclient

To update the ``openstack`` client, run this command:

.. code::

    $ sudo pip install --upgrade python-openstackclient

To remove the ``openstack`` client, run this command:

.. code::

    $ sudo pip uninstall python-openstackclient

Before you can issue client commands, you must download and source the
``openrc`` file to set environment variables.

For complete information about the OpenStack clients, including how to
source the ``openrc`` file, see `OpenStack End User
Guide <http://docs.openstack.org/user-guide/>`__, `OpenStack Admin
User Guide <http://docs.openstack.org/user-guide-admin/>`__, and
`OpenStack Command-Line Interface
Reference <http://docs.openstack.org/cli-reference/content/>`__.

Launch an instance
------------------

To launch instances, you must choose a name, an image, and a flavor for
your instance.

To list available images, call the Compute API through the ``openstack``
client, as follows:

.. code::

    $ openstack image list

.. code::

    +--------------------------------------+------------------+
    | ID                                   | Name             |
    +--------------------------------------+------------------+
    | a5604931-af06-4512-8046-d43aabf272d3 | fedora-20.x86_64 |
    +--------------------------------------+------------------+

To list flavors, run this command:

.. code::

    $ openstack flavor list

.. code::

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

To launch an instance named ``my_instance``, run the ``openstack server
create`` command with the image and flavor IDs and the server name, as follows:

.. code::

    $ openstack server create --image 949c80c8-b4ac-4315-844e-69f9bef39ed1 --flavor 1 my_instance

.. code::

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
   For information about the default ports that the OpenStack components
   use, see `Firewalls and default ports`_ in the *OpenStack Configuration
   Reference*.

.. _Firewalls and default ports: http://docs.openstack.org/liberty/config-reference/content/firewalls-default-ports.html
