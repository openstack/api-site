=========================
Section Seven: Networking
=========================

.. todo:: Latter part of the chapter (LBaaS) needs to use Fractals app entities for the examples.

Prior to this chapter, all of the nodes that comprise the fractal application
were attached to the same network.

In this section of the tutorial, we introduce the Networking API,
which will enable us to build networking topologies that separate
public traffic accessing the application from traffic between the API
instances and the worker components, introduce load balancing for
resilience, and create a secure backend network for communication between the
database, webserver, file storage, and worker components.

.. only:: dotnet

    .. warning:: This section has not yet been completed for the .NET SDK

.. only:: fog

    .. warning:: fog `supports <http://www.rubydoc.info/gems/fog/1.8.0/Fog/Network/OpenStack>`_ the OpenStack Networking API, but this section has not yet been completed.

.. only:: jclouds

    .. warning:: jClouds supports the OpenStack Networking API, but section has not yet been completed. Please see `this <https://gist.github.com/everett-toews/8701756>`_ in the meantime.

.. only:: libcloud

    .. warning:: Libcloud does not support the OpenStack Networking API

.. only:: node

    .. warning:: Pkgcloud supports the OpenStack Networking API, but this section has not been completed

.. only:: openstacksdk

    .. warning:: This section has not yet been completed for the OpenStack SDK

.. only:: phpopencloud

    .. warning:: PHP-OpenCloud supports the OpenStack Networking API, but this section has not been completed

Working with the CLI
--------------------

As SDKs don't currently support the OpenStack Networking API this section uses
the commandline.

Install the 'neutron' commandline client by following this guide:
http://docs.openstack.org/cli-reference/content/install_clients.html

Then set up the necessary variables for your cloud in an 'openrc' file using this guide:
http://docs.openstack.org/cli-reference/content/cli_openrc.html

Ensure you have an openrc.sh file, source it and then check your neutron client works:
::

    $ cat openrc.sh
    export OS_USERNAME=your_auth_username
    export OS_PASSWORD=your_auth_password
    export OS_TENANT_NAME=your_project_name
    export OS_AUTH_URL=http://controller:5000/v2.0
    export OS_REGION_NAME=your_region_name

    $ source openrc.sh

    $ neutron --version
    2.3.11

Networking Segmentation
-----------------------

In traditional datacenters, multiple network segments are
dedicated to specific types of network traffic.

The fractal application we are building contains three types of network traffic:

* public-facing wev traffic
* API traffic
* internal worker traffic

For performance reasons, it makes sense to have a network for each tier,
so that traffic from one tier does not "crowd out" other types of traffic
and cause the application to fail. In addition, having separate networks makes
controlling access to parts of the application easier to manage, improving the overall
security of the application.

Prior to this section, the network layout for the Fractal application would be similar to the following diagram:

.. nwdiag::

        nwdiag {

            network public {
                    address = "203.0.113.0/24"
                    tenant_router [ address = "203.0.113.20" ];
            }

            network tenant_network {
                    address = "10.0.0.0/24"
                    tenant_router [ address = "10.0.0.1" ];
                    api [ address = "203.0.113.20, 10.0.0.3" ];
                    webserver1 [ address = "203.0.113.21, 10.0.0.4" ];
                    webserver2 [ address = "203.0.113.22, 10.0.0.5" ];
                    worker1 [ address = "203.0.113.23, 10.0.0.6" ];
                    worker2 [ address = "203.0.113.24, 10.0.0.7" ];
            }
        }

In this network layout, we are assuming that the OpenStack cloud in which
you have been building your application has a public
network and tenant router that was already created in advance, either by the
administrators of the cloud you are running the Fractal application on,
or by you, following the instructions in the appendix.

Many of the network concepts that are discussed in this section are
already present in the diagram above. A tenant router provides
routing and external access for the worker nodes, and floating IP addresses
are already associated with each node in the Fractal application cluster
to facilitate external access.

At the end of this section, we will be making some slight changes to the networking topology
by using the OpenStack Networking API to create a new network to which the worker nodes will attach
(10.0.1.0/24). We will use the API network (10.0.3.0/24) to attach the Fractal API servers. Webserver instances have their own network (10.0.2.0/24), and
will be accessible by fractal aficionados worldwide, by allocating floating IPs from the public network.

.. nwdiag::

        nwdiag {

            network public {
                    address = "203.0.113.0/24"
                    tenant_router [ address = "203.0.113.60"];
            }

            network webserver_network{
                    address = "10.0.2.0/24"
                    tenant_router [ address = "10.0.2.1"];
                    webserver1 [ address = "203.0.113.21, 10.0.2.3"];
                    webserver2 [ address = "203.0.113.22, 10.0.2.4"];
            }
            network api_network {
                    address = "10.0.3.0/24"
                    tenant_router [ address = "10.0.3.1" ];
                    api1 [ address = "10.0.3.3" ];
                    api2 [ address = "10.0.3.4" ];
            }

            network worker_network {
                    address = "10.0.1.0/24"
                    tenant_router [ address = "10.0.1.1" ];
                    worker1 [ address = "10.0.1.5" ];
                    worker2 [ address = "10.0.1.6" ];
            }
        }

Introduction to Tenant Networking
---------------------------------

With the OpenStack Networking API, the workflow for creating a network topology that separates the public-facing
Fractals app API from the worker backend is as follows:

* Create a network for the web server nodes.

* Create a network for the worker nodes. This is the private data network.

* Create a subnet for the private data network to use for addressing. In other words, when worker instances are created, their IP addresses will come from this subnet.

* Create a subnet for the web server network to use for addressing. In other words, when web server instances are created, their IP addresses will come from this subnet.

* Create a router for the private data network.

* Allocate floating ips and assign them to the web server nodes.

Creating Networks
-----------------

We assume that the public network, with the subnet that floating IPs can be allocated from, was provisioned
for you by your cloud operator. This is due to the nature of L3 routing, where the IP address range that
is used for floating IPs is configured in other parts of the operator's network, so that traffic is properly routed.

.. todo:: Rework the console outputs in these sections to be more comprehensive, based on the outline above

Next, create a private data network, worker_network:

::

        $ neutron net-create worker_network
        Created a new network:
        +-----------------+--------------------------------------+
        | Field           | Value                                |
        +-----------------+--------------------------------------+
        | admin_state_up  | True                                 |
        | id              | 953224c6-c510-45c5-8a29-37deffd3d78e |
        | name            | worker_network                       |
        | router:external | False                                |
        | shared          | False                                |
        | status          | ACTIVE                               |
        | subnets         |                                      |
        | tenant_id       | f77bf3369741408e89d8f6fe090d29d2     |
        +-----------------+--------------------------------------+

Now let's just confirm that we have both the worker network, and a public
network by getting a list of all networks in the cloud. The public network
doesn't have to be named public - it could be 'external', 'net04_ext' or
something else - the important thing is it exists and can be used to reach
the internet.

::

        $ neutron net-list
        +--------------------------------------+------------------+--------------------------------------------------+
        | id                                   | name             | subnets                                          |
        +--------------------------------------+------------------+--------------------------------------------------+
        | 29349515-98c1-4f59-922e-3809d1b9707c | public           | 7203dd35-7d17-4f37-81a1-9554b3316ddb             |
        | 953224c6-c510-45c5-8a29-37deffd3d78e | worker_network   |                                                  |
        +--------------------------------------+------------------+--------------------------------------------------+

Next create the subnet from which addresses will be allocated for instances on the worker network:

::

        $ neutron subnet-create --name worker_cidr worker_network 10.0.1.0/24
        Created a new subnet:
        +-------------------+--------------------------------------------+
        | Field             | Value                                      |
        +-------------------+--------------------------------------------+
        | allocation_pools  | {"start": "10.0.1.2", "end": "10.0.1.254"} |
        | cidr              | 10.0.1.0/24                                |
        | dns_nameservers   |                                            |
        | enable_dhcp       | True                                       |
        | gateway_ip        | 10.0.1.1                                   |
        | host_routes       |                                            |
        | id                | a0e2ebe4-5d4e-46b3-82b5-4179d778e615       |
        | ip_version        | 4                                          |
        | ipv6_address_mode |                                            |
        | ipv6_ra_mode      |                                            |
        | name              | worker_cidr                                |
        | network_id        | 953224c6-c510-45c5-8a29-37deffd3d78e       |
        | tenant_id         | f77bf3369741408e89d8f6fe090d29d2           |
        +-------------------+--------------------------------------------+

Now create a network for the webservers ...

::

    $ neutron net-create webserver_network
    Created a new network:
    +-----------------+--------------------------------------+
    | Field           | Value                                |
    +-----------------+--------------------------------------+
    | admin_state_up  | True                                 |
    | id              | 28cf9704-2b43-4925-b23e-22a892e354f2 |
    | mtu             | 0                                    |
    | name            | webserver_network                    |
    | router:external | False                                |
    | shared          | False                                |
    | status          | ACTIVE                               |
    | subnets         |                                      |
    | tenant_id       | 0cb06b70ef67424b8add447415449722     |
    +-----------------+--------------------------------------+

... and a subnet from which they can pull IP addresses:

::

    $ neutron subnet-create webserver_network 10.0.2.0/24
    Created a new subnet:
    +-------------------+--------------------------------------------+
    | Field             | Value                                      |
    +-------------------+--------------------------------------------+
    | allocation_pools  | {"start": "10.0.2.2", "end": "10.0.2.254"} |
    | cidr              | 10.0.2.0/24                                |
    | dns_nameservers   |                                            |
    | enable_dhcp       | True                                       |
    | gateway_ip        | 10.0.2.1                                   |
    | host_routes       |                                            |
    | id                | 1e0d6a75-c40e-4be5-8e13-b2226fc8444a       |
    | ip_version        | 4                                          |
    | ipv6_address_mode |                                            |
    | ipv6_ra_mode      |                                            |
    | name              |                                            |
    | network_id        | 28cf9704-2b43-4925-b23e-22a892e354f2       |
    | tenant_id         | 0cb06b70ef67424b8add447415449722           |
    +-------------------+--------------------------------------------+

Next, create the network for the API servers:

::

    $ neutron net-create api_network
    Created a new network:
    +-----------------+--------------------------------------+
    | Field           | Value                                |
    +-----------------+--------------------------------------+
    | admin_state_up  | True                                 |
    | id              | 5fe4045a-65dc-4672-b44e-1f14a496a71a |
    | mtu             | 0                                    |
    | name            | api_network                          |
    | router:external | False                                |
    | shared          | False                                |
    | status          | ACTIVE                               |
    | subnets         |                                      |
    | tenant_id       | 0cb06b70ef67424b8add447415449722     |
    +-----------------+--------------------------------------+

Finally, create the subnet for the API network:

::

    $ neutron subnet-create api_network 10.0.3.0/24
    Created a new subnet:
    +-------------------+--------------------------------------------+
    | Field             | Value                                      |
    +-------------------+--------------------------------------------+
    | allocation_pools  | {"start": "10.0.3.2", "end": "10.0.3.254"} |
    | cidr              | 10.0.3.0/24                                |
    | dns_nameservers   |                                            |
    | enable_dhcp       | True                                       |
    | gateway_ip        | 10.0.3.1                                   |
    | host_routes       |                                            |
    | id                | 6ce4b60d-a940-4369-b8f0-2e9c196e4f20       |
    | ip_version        | 4                                          |
    | ipv6_address_mode |                                            |
    | ipv6_ra_mode      |                                            |
    | name              |                                            |
    | network_id        | 5fe4045a-65dc-4672-b44e-1f14a496a71a       |
    | tenant_id         | 0cb06b70ef67424b8add447415449722           |
    +-------------------+--------------------------------------------+

Now that you've got the networks created, go ahead and create two Floating IPs, for web servers.
Ensure that you replace 'public' with the name of the public/external network set up
by your cloud administrator.

::

    $ neutron floatingip-create public
    Created a new floatingip:
    +---------------------+--------------------------------------+
    | Field               | Value                                |
    +---------------------+--------------------------------------+
    | fixed_ip_address    |                                      |
    | floating_ip_address | 203.0.113.21                         |
    | floating_network_id | 7ad1ce2b-4b8c-4036-a77b-90332d7f4dbe |
    | id                  | 185df49f-7890-4c59-a66a-2456b6a87422 |
    | port_id             |                                      |
    | router_id           |                                      |
    | status              | DOWN                                 |
    | tenant_id           | 0cb06b70ef67424b8add447415449722     |
    +---------------------+--------------------------------------+

    $ neutron floatingip-create public
    Created a new floatingip:
    +---------------------+--------------------------------------+
    | Field               | Value                                |
    +---------------------+--------------------------------------+
    | fixed_ip_address    |                                      |
    | floating_ip_address | 203.0.113.22                         |
    | floating_network_id | 7ad1ce2b-4b8c-4036-a77b-90332d7f4dbe |
    | id                  | 185df49f-7890-4c59-a66a-2456b6a87422 |
    | port_id             |                                      |
    | router_id           |                                      |
    | status              | DOWN                                 |
    | tenant_id           | 0cb06b70ef67424b8add447415449722     |
    +---------------------+--------------------------------------+

.. note:: The world is running out of IPv4 addresses. If you get an error like
          "No more IP addresses available on network", contact your cloud
          administrator. You may also want to ask about IPv6 :)

Next we'll need to enable OpenStack to route traffic appropriately.

Creating the SNAT gateway
-------------------------

Because we are using cloud-init and other tools to deploy and bootstrap the application,
the Fractal app worker instances require Source Network Address Translation (SNAT).
If the Fractal app worker nodes were deployed from a "golden image"
that had all the software components already installed, there would be no need to create a
Neutron router to provide SNAT functionality.

.. todo :: nickchase doesn't understand the above paragraph.  Why wouldn't it be required?

::

        $ neutron router-create tenant_router
        Created a new router:
        +-----------------------+--------------------------------------+
        | Field                 | Value                                |
        +-----------------------+--------------------------------------+
        | admin_state_up        | True                                 |
        | external_gateway_info |                                      |
        | id                    | d380b29f-ca65-4718-9735-196cbed10fce |
        | name                  | tenant_router                        |
        | routes                |                                      |
        | status                | ACTIVE                               |
        | tenant_id             | f77bf3369741408e89d8f6fe090d29d2     |
        +-----------------------+--------------------------------------+

After creating the router, you need to set up the gateway for the router. For outbound access
we will set the router's gateway as the public network.

::

    $ neutron router-gateway-set worker_router public
    Set gateway for router tenant_router

    $ neutron router-show tenant_router

            +-----------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
            | Field                 | Value                                                                                                                                                                                    |
            +-----------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
            | admin_state_up        | True                                                                                                                                                                                     |
            | external_gateway_info | {"network_id": "29349515-98c1-4f59-922e-3809d1b9707c", "enable_snat": true, "external_fixed_ips": [{"subnet_id": "7203dd35-7d17-4f37-81a1-9554b3316ddb", "ip_address": "203.0.113.50"}]} |
            | id                    | d380b29f-ca65-4718-9735-196cbed10fce                                                                                                                                                     |
            | name                  | tenant_router                                                                                                                                                                            |
            | routes                |                                                                                                                                                                                          |
            | status                | ACTIVE                                                                                                                                                                                   |
            | tenant_id             | f77bf3369741408e89d8f6fe090d29d2                                                                                                                                                         |
            +-----------------------+------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


The final, most important step is to create an interface on the worker network and attach it to the router you just created.

::

        $ neutron router-interface-add tenant_router worker_cidr
        Added interface 0d8bd523-06c2-4ddd-8b33-8726af2daa0a to router worker_router.


::

        $ neutron net-list
        +--------------------------------------+----------------+--------------------------------------------------+
        | id                                   | name           | subnets                                          |
        +--------------------------------------+----------------+--------------------------------------------------+
        | 29349515-98c1-4f59-922e-3809d1b9707c | public         | 7203dd35-7d17-4f37-81a1-9554b3316ddb             |
        | 953224c6-c510-45c5-8a29-37deffd3d78e | worker_network | a0e2ebe4-5d4e-46b3-82b5-4179d778e615 10.0.1.0/24 |
        +--------------------------------------+----------------+--------------------------------------------------+

.. todo:
    Wire up the tenant router to the api_network and webserver_network

Booting a worker
~~~~~~~~~~~~~~~~

Now that you've prepared the networking infrastructure, you can go ahead and boot an instance on it.
Ensure you use appropriate flavor and image values for your cloud - see :doc:`section1` if you've not already.

.. todo:: Show how to create an instance in libcloud using the network we just created. - libcloud does not yet support this.

::

        $ nova boot --flavor m1.tiny --image cirros-0.3.3-x86_64-disk --nic net-id=953224c6-c510-45c5-8a29-37deffd3d78e worker1
        +--------------------------------------+-----------------------------------------------------------------+
        | Property                             | Value                                                           |
        +--------------------------------------+-----------------------------------------------------------------+
        | OS-DCF:diskConfig                    | MANUAL                                                          |
        | OS-EXT-AZ:availability_zone          | nova                                                            |
        | OS-EXT-STS:power_state               | 0                                                               |
        | OS-EXT-STS:task_state                | scheduling                                                      |
        | OS-EXT-STS:vm_state                  | building                                                        |
        | OS-SRV-USG:launched_at               | -                                                               |
        | OS-SRV-USG:terminated_at             | -                                                               |
        | accessIPv4                           |                                                                 |
        | accessIPv6                           |                                                                 |
        | adminPass                            | 9vU8KSY4oDht                                                    |
        | config_drive                         |                                                                 |
        | created                              | 2015-03-30T05:26:04Z                                            |
        | flavor                               | m1.tiny (1)                                                     |
        | hostId                               |                                                                 |
        | id                                   | 9e188a47-a246-463e-b445-027d6e2966e0                            |
        | image                                | cirros-0.3.3-x86_64-disk (ad605ff9-4593-4048-900b-846d6401c193) |
        | key_name                             | -                                                               |
        | metadata                             | {}                                                              |
        | name                                 | worker1                                                         |
        | os-extended-volumes:volumes_attached | []                                                              |
        | progress                             | 0                                                               |
        | security_groups                      | default                                                         |
        | status                               | BUILD                                                           |
        | tenant_id                            | f77bf3369741408e89d8f6fe090d29d2                                |
        | updated                              | 2015-03-30T05:26:04Z                                            |
        | user_id                              | a61292a5691d4c6c831b7a8f07921261                                |
        +--------------------------------------+-----------------------------------------------------------------+

Load Balancing
--------------

After separating the Fractal worker nodes into their own network,
the next logical step is to move the Fractal API service onto a load balancer,
so that multiple API workers can handle requests. By using a load balancer, the API
service can be scaled out in a similar fashion to the worker nodes.

Neutron LbaaS API
~~~~~~~~~~~~~~~~~

.. note:: This section is based on the Neutron LBaaS API version 1.0 http://docs.openstack.org/admin-guide-cloud/content/lbaas_workflow.html

.. todo:: libcloud support added 0.14: https://developer.rackspace.com/blog/libcloud-0-dot-14-released/ - this section needs rewriting to use the libcloud API

The OpenStack Networking API provides support for creating loadbalancers, which can be used to
scale the Fractal app web service. In the following example, we create two compute instances via the Compute
API, then instantiate a loadbalancer that will use a virtual IP (VIP) for accessing the web service offered by
the two compute nodes. The end result will be the following network topology:

.. nwdiag::

        nwdiag {

            network public {
                    address = "203.0.113.0/24"
                    tenant_router [ address = "203.0.113.60" ];
                    loadbalancer [ address = "203.0.113.63" ];
            }

            network webserver_network {
                    address = "10.0.2.0/24"
                    tenant_router [ address = "10.0.2.1"];
                    webserver1 [ address = "203.0.113.21, 10.0.2.3"];
                    webserver2 [ address = "203.0.113.22, 10.0.2.4"];
            }
         }

libcloud support added 0.14: https://developer.rackspace.com/blog/libcloud-0-dot-14-released/

Let's start by looking at what's already in place.

::

    $ neutron net-list
    +--------------------------------------+-------------------+-----------------------------------------------------+
    | id                                   | name              | subnets                                             |
    +--------------------------------------+-------------------+-----------------------------------------------------+
    | 3c826379-e896-45a9-bfe1-8d84e68e9c63 | webserver_network | 3eada497-36dd-485b-9ba4-90c5e3340a53 10.0.2.0/24    |
    | 7ad1ce2b-4b8c-4036-a77b-90332d7f4dbe | public            | 47fd3ff1-ead6-4d23-9ce6-2e66a3dae425 203.0.113.0/24 |
    +--------------------------------------+-------------------+-----------------------------------------------------+

Now let's go ahead and create 2 instances.

::

    $ nova boot --flavor 1 --image 53ff0943-99ba-42d2-a10d-f66656372f87 --min-count 2 test
    +--------------------------------------+-----------------------------------------------------------------+
    | Property                             | Value                                                           |
    +--------------------------------------+-----------------------------------------------------------------+
    | OS-DCF:diskConfig                    | MANUAL                                                          |
    | OS-EXT-AZ:availability_zone          | nova                                                            |
    | OS-EXT-STS:power_state               | 0                                                               |
    | OS-EXT-STS:task_state                | scheduling                                                      |
    | OS-EXT-STS:vm_state                  | building                                                        |
    | OS-SRV-USG:launched_at               | -                                                               |
    | OS-SRV-USG:terminated_at             | -                                                               |
    | accessIPv4                           |                                                                 |
    | accessIPv6                           |                                                                 |
    | adminPass                            | z84zWFCcpppH                                                    |
    | config_drive                         |                                                                 |
    | created                              | 2015-04-02T02:45:09Z                                            |
    | flavor                               | m1.tiny (1)                                                     |
    | hostId                               |                                                                 |
    | id                                   | 8d579f4a-116d-46b9-8db3-aa55b76f76d8                            |
    | image                                | cirros-0.3.3-x86_64-disk (53ff0943-99ba-42d2-a10d-f66656372f87) |
    | key_name                             | -                                                               |
    | metadata                             | {}                                                              |
    | name                                 | test-1                                                          |
    | os-extended-volumes:volumes_attached | []                                                              |
    | progress                             | 0                                                               |
    | security_groups                      | default                                                         |
    | status                               | BUILD                                                           |
    | tenant_id                            | 0cb06b70ef67424b8add447415449722                                |
    | updated                              | 2015-04-02T02:45:09Z                                            |
    | user_id                              | d95381d331034e049727e2413efde39f                                |
    +--------------------------------------+-----------------------------------------------------------------+

Confirm that they were added:

::

    $ nova list
    +--------------------------------------+--------+--------+------------+-------------+------------------+
    | ID                                   | Name   | Status | Task State | Power State | Networks         |
    +--------------------------------------+--------+--------+------------+-------------+------------------+
    | 8d579f4a-116d-46b9-8db3-aa55b76f76d8 | test-1 | ACTIVE | -          | Running     | private=10.0.2.4 |
    | 8fadf892-b6e9-44f4-b132-47c6762ffa2c | test-2 | ACTIVE | -          | Running     | private=10.0.2.3 |
    +--------------------------------------+--------+--------+------------+-------------+------------------+

Now let's look at what ports are available:

::

    $ neutron port-list
    +--------------------------------------+------+-------------------+---------------------------------------------------------------------------------+
    | id                                   | name | mac_address       | fixed_ips                                                                       |
    +--------------------------------------+------+-------------------+---------------------------------------------------------------------------------+
    | 1d9a0f79-bf05-443e-b65d-a05b0c635936 |      | fa:16:3e:10:f8:f0 | {"subnet_id": "3eada497-36dd-485b-9ba4-90c5e3340a53", "ip_address": "10.0.2.2"} |
    | 3f40c866-169b-48ec-8e0a-d9f1e70e5756 |      | fa:16:3e:8c:6f:25 | {"subnet_id": "3eada497-36dd-485b-9ba4-90c5e3340a53", "ip_address": "10.0.2.1"} |
    | 462c92c6-941c-48ab-8cca-3c7a7308f580 |      | fa:16:3e:d7:7d:56 | {"subnet_id": "3eada497-36dd-485b-9ba4-90c5e3340a53", "ip_address": "10.0.2.4"} |
    | 7451d01f-bc3b-46a6-9ae3-af260d678a63 |      | fa:16:3e:c6:d4:9c | {"subnet_id": "3eada497-36dd-485b-9ba4-90c5e3340a53", "ip_address": "10.0.2.3"} |
    +--------------------------------------+------+-------------------+---------------------------------------------------------------------------------+

Next create additional floating IPs by specifying the fixed IP addresses they should point to and the ports they should use:

::

    $ neutron floatingip-create public --fixed-ip-address 10.0.2.3 --port-id 7451d01f-bc3b-46a6-9ae3-af260d678a63
    Created a new floatingip:
    +---------------------+--------------------------------------+
    | Field               | Value                                |
    +---------------------+--------------------------------------+
    | fixed_ip_address    | 10.0.2.3                             |
    | floating_ip_address | 203.0.113.21                         |
    | floating_network_id | 7ad1ce2b-4b8c-4036-a77b-90332d7f4dbe |
    | id                  | dd2c838e-7c1b-480c-a18c-17f1526c96ea |
    | port_id             | 7451d01f-bc3b-46a6-9ae3-af260d678a63 |
    | router_id           | 7f8ee1f6-7211-40e8-b9a8-17582ecfe50b |
    | status              | DOWN                                 |
    | tenant_id           | 0cb06b70ef67424b8add447415449722     |
    +---------------------+--------------------------------------+
    $ neutron floatingip-create public --fixed-ip-address 10.0.2.4 --port-id 462c92c6-941c-48ab-8cca-3c7a7308f580
    Created a new floatingip:
    +---------------------+--------------------------------------+
    | Field               | Value                                |
    +---------------------+--------------------------------------+
    | fixed_ip_address    | 10.0.2.4                             |
    | floating_ip_address | 203.0.113.22                         |
    | floating_network_id | 7ad1ce2b-4b8c-4036-a77b-90332d7f4dbe |
    | id                  | 6eb510bf-c18f-4c6f-bb35-e21938ca8bd4 |
    | port_id             | 462c92c6-941c-48ab-8cca-3c7a7308f580 |
    | router_id           | 7f8ee1f6-7211-40e8-b9a8-17582ecfe50b |
    | status              | DOWN                                 |
    | tenant_id           | 0cb06b70ef67424b8add447415449722     |
    +---------------------+--------------------------------------+

All right, now you're ready to go ahead and create members for the load balancer pool, referencing the floating IPs:

::

    $ neutron lb-member-create --address 203.0.113.21 --protocol-port 80 mypool
    Created a new member:
    +--------------------+--------------------------------------+
    | Field              | Value                                |
    +--------------------+--------------------------------------+
    | address            | 203.0.113.21                         |
    | admin_state_up     | True                                 |
    | id                 | 679966a9-f719-4df0-86cf-3a24d0433b38 |
    | pool_id            | 600496f0-196c-431c-ae35-a0af9bb01d32 |
    | protocol_port      | 80                                   |
    | status             | PENDING_CREATE                       |
    | status_description |                                      |
    | tenant_id          | 0cb06b70ef67424b8add447415449722     |
    | weight             | 1                                    |
    +--------------------+--------------------------------------+

    $ neutron lb-member-create --address 203.0.113.22 --protocol-port 80 mypool
    Created a new member:
    +--------------------+--------------------------------------+
    | Field              | Value                                |
    +--------------------+--------------------------------------+
    | address            | 203.0.113.22                         |
    | admin_state_up     | True                                 |
    | id                 | f3ba0605-4926-4498-b86d-51002892e93a |
    | pool_id            | 600496f0-196c-431c-ae35-a0af9bb01d32 |
    | protocol_port      | 80                                   |
    | status             | PENDING_CREATE                       |
    | status_description |                                      |
    | tenant_id          | 0cb06b70ef67424b8add447415449722     |
    | weight             | 1                                    |
    +--------------------+--------------------------------------+

You should be able to see them in the member list:

::

    $ neutron lb-member-list
    +--------------------------------------+--------------+---------------+--------+----------------+--------+
    | id                                   | address      | protocol_port | weight | admin_state_up | status |
    +--------------------------------------+--------------+---------------+--------+----------------+--------+
    | 679966a9-f719-4df0-86cf-3a24d0433b38 | 203.0.113.21 |            80 |      1 | True           | ACTIVE |
    | f3ba0605-4926-4498-b86d-51002892e93a | 203.0.113.22 |            80 |      1 | True           | ACTIVE |
    +--------------------------------------+--------------+---------------+--------+----------------+--------+

Now let's create a healthmonitor that will ensure that members of the loadbalancer pool are active and able
to respond to requests. If a member in the pool dies or is unresponsive, the member is removed from the pool
so that client requests are routed to another active member.

::

    $ neutron lb-healthmonitor-create --delay 3 --type HTTP --max-retries 3 --timeout 3
    Created a new health_monitor:
    +----------------+--------------------------------------+
    | Field          | Value                                |
    +----------------+--------------------------------------+
    | admin_state_up | True                                 |
    | delay          | 3                                    |
    | expected_codes | 200                                  |
    | http_method    | GET                                  |
    | id             | 663345e6-2853-43b2-9ccb-a623d5912345 |
    | max_retries    | 3                                    |
    | pools          |                                      |
    | tenant_id      | 0cb06b70ef67424b8add447415449722     |
    | timeout        | 3                                    |
    | type           | HTTP                                 |
    | url_path       | /                                    |
    +----------------+--------------------------------------+
    $ neutron lb-healthmonitor-associate 663345e6-2853-43b2-9ccb-a623d5912345 mypool
    Associated health monitor 663345e6-2853-43b2-9ccb-a623d5912345

Now create a virtual IP that will be used to direct traffic between the various members of the pool:

::

    $ neutron lb-vip-create --name myvip --protocol-port 80 --protocol HTTP --subnet-id 47fd3ff1-ead6-4d23-9ce6-2e66a3dae425 mypool
    Created a new vip:
    +---------------------+--------------------------------------+
    | Field               | Value                                |
    +---------------------+--------------------------------------+
    | address             | 203.0.113.63                         |
    | admin_state_up      | True                                 |
    | connection_limit    | -1                                   |
    | description         |                                      |
    | id                  | f0bcb66e-5eeb-447b-985e-faeb67540c2f |
    | name                | myvip                                |
    | pool_id             | 600496f0-196c-431c-ae35-a0af9bb01d32 |
    | port_id             | bc732f81-2640-4622-b624-993a5ae185c5 |
    | protocol            | HTTP                                 |
    | protocol_port       | 80                                   |
    | session_persistence |                                      |
    | status              | PENDING_CREATE                       |
    | status_description  |                                      |
    | subnet_id           | 47fd3ff1-ead6-4d23-9ce6-2e66a3dae425 |
    | tenant_id           | 0cb06b70ef67424b8add447415449722     |
    +---------------------+--------------------------------------+

And confirm it's in place:

::

    $ neutron lb-vip-list
    +--------------------------------------+-------+--------------+----------+----------------+--------+
    | id                                   | name  | address      | protocol | admin_state_up | status |
    +--------------------------------------+-------+--------------+----------+----------------+--------+
    | f0bcb66e-5eeb-447b-985e-faeb67540c2f | myvip | 203.0.113.63 | HTTP     | True           | ACTIVE |
    +--------------------------------------+-------+--------------+----------+----------------+--------+

Now let's look at the big picture.

Final Result
------------

With the addition of the loadbalancer, the Fractal app's networking topology now reflects the modular
nature of the application itself.


.. nwdiag::

        nwdiag {

            network public {
                    address = "203.0.113.0/24"
                    tenant_router [ address = "203.0.113.60"];
                    loadbalancer [ address = "203.0.113.63" ];
            }

            network webserver_network{
                    address = "10.0.2.0/24"
                    tenant_router [ address = "10.0.2.1"];
                    webserver1 [ address = "203.0.113.21, 10.0.2.3"];
                    webserver2 [ address = "203.0.113.22, 10.0.2.4"];
            }
            network api_network {
                    address = "10.0.3.0/24"
                    tenant_router [ address = "10.0.3.1" ];
                    api1 [ address = "10.0.3.3" ];
                    api2 [ address = "10.0.3.4" ];
            }

            network worker_network {
                    address = "10.0.1.0/24"
                    tenant_router [ address = "10.0.1.1" ];
                    worker1 [ address = "10.0.1.5" ];
                    worker2 [ address = "10.0.1.6" ];
            }
        }


Next Steps
----------

You should now be fairly confident working with Network API.
There are several calls we did not cover. To see these and more,
refer to the volume documentation of your SDK, or try a different step in the tutorial, including:

* :doc:`/section8` - for advice for developers new to operations
* :doc:`/section9` - to see all the crazy things we think ordinary folks won't want to do ;)
