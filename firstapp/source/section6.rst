=============
Orchestration
=============

.. todo:: Needs to be restructured so that the fractals app is used as the example for the explanatory material.

.. note:: Sorry! We're not quite happy with this chapter. It will give you an introduction to heat,
          but it's a little dry at the moment. We'd like to write a template for the Fractals app instead
          of using the "hello world" style ones, so stay tuned!

Throughout this guide, we've talked about the importance of durability and scalability
for your cloud-based applications. In most cases, really achieving these qualities means
automating tasks such as scaling and other operational tasks.

The Orchestration module provides a template-based way to describe a cloud
application, then coordinates running the needed OpenStack API calls to run
cloud applications. The templates allow you to create most OpenStack resource
types, such as instances, networking information, volumes, security groups
and even users. It also provides more advanced functionality, such as
instance high availability, instance auto-scaling, and nested stacks.

The OpenStack Orchestration API contains the following constructs:

* Stacks
* Resources
* Templates

Stacks are created from Templates, which contain Resources. Resources
are an abstraction in the HOT (Heat Orchestration Template) template language, which enables you to define different
cloud resources by setting the `type` attibute.

For example, you might use the Orchestration API to create two compute
instances by creating a Stack and by passing a Template to the Orchestration API.
That Template would contain two Resources with the `type` attribute set to `OS::Nova::Server`.

That's a simplistic example, of course, but the flexibility of the Resource object
enables the creation of Templates that contain all the required cloud
infrastructure to run an application, such as load balancers, block storage volumes,
compute instances, networking topology, and security policies.

.. note:: The Orchestration module isn't deployed by default in every cloud. If these commands don't work, it means the Orchestration API isn't available; ask your support team for assistance.

This section introduces the `HOT templating language <http://docs.openstack.org/developer/heat/template_guide/hot_guide.html>`_,
and takes you throughsome of the common calls you will make when working with OpenStack Orchestration.

Unlike previous sections of this guide, in which you used your SDK to programmatically interact with
OpenStack, in this section you'll be using the Orchestration API directly through Template files,
so we'll work from the command line.

Install the 'heat' commandline client by following this guide:
http://docs.openstack.org/cli-reference/content/install_clients.html

then set up the necessary variables for your cloud in an 'openrc' file using this guide:
http://docs.openstack.org/cli-reference/content/cli_openrc.html

.. only:: dotnet

    .. warning:: the .NET SDK does not currently support OpenStack Orchestration

.. only:: fog

    .. note:: fog `does support OpenStack Orchestration <https://github.com/fog/fog/tree/master/lib/fog/openstack/models/orchestration>`_.

.. only:: jclouds

    .. warning:: Jclouds does not currently support OpenStack Orchestration. See this `bug report <https://issues.apache.org/jira/browse/JCLOUDS-693>`_.

.. only:: libcloud

    .. warning:: libcloud does not currently support OpenStack Orchestration.

.. only:: node

   .. note:: Pkgcloud supports OpenStack Orchestration :D:D:D but this section is `not written yet <https://github.com/pkgcloud/pkgcloud/blob/master/docs/providers/openstack/orchestration.md>`_

.. only:: openstacksdk

    .. warning:: OpenStack SDK does not currently support OpenStack Orchestration.

.. only:: phpopencloud

    .. note:: PHP-opencloud supports orchestration :D:D:D but this section is not written yet.

HOT Templating Language
-----------------------

The best place to learn about the template syntax for OpenStack Orchestration is the
`Heat Orchestration Template (HOT) Guide <http://docs.openstack.org/developer/heat/template_guide/hot_guide.html>`_
You should read the HOT Guide first to learn how to create basic templates, their inputs and outputs.

Working with Stacks: Basics
---------------------------

.. todo::

    This section needs to have a HOT template written for deploying the Fractal Application

.. todo::

    Replace the hello_world.yaml templte with the Fractal template

* Stack create

In the following example, we use the `hello_world <https://github.com/openstack/heat-templates/blob/master/hot/hello_world.yaml>`_ Hot template to demonstrate creating
a Nova compute instance, with a few configuration settings passed in, such as an administrative password and the unique identifier (UUID)
of an image:

::

    $ wget https://raw.githubusercontent.com/openstack/heat-templates/master/hot/hello_world.yaml
    $ heat stack-create --template-file hello_world.yaml \
     --parameters admin_pass=Test123\;key_name=test\;image=5bbe4073-90c0-4ec9-833c-092459cc4539 hello_world
    +--------------------------------------+-------------+--------------------+----------------------+
    | id                                   | stack_name  | stack_status       | creation_time        |
    +--------------------------------------+-------------+--------------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | hello_world | CREATE_IN_PROGRESS | 2015-04-01T03:20:25Z |
    +--------------------------------------+-------------+--------------------+----------------------+

The resulting stack creates a Nova instance automatically, which you can see here:

::

    $ nova list
    +--------------------------------------+---------------------------------+--------+------------+-------------+------------------+
    | ID                                   | Name                            | Status | Task State | Power State | Networks         |
    +--------------------------------------+---------------------------------+--------+------------+-------------+------------------+
    | 9bdf0e2f-415e-43a0-90ea-63a5faf86cf9 | hello_world-server-dwmwhzfxgoor | ACTIVE | -          | Running     | private=10.0.0.3 |
    +--------------------------------------+---------------------------------+--------+------------+-------------+------------------+

Verify that the stack was successfully created using the following command:

::

    $ heat stack-list
    +--------------------------------------+-------------+-----------------+----------------------+
    | id                                   | stack_name  | stack_status    | creation_time        |
    +--------------------------------------+-------------+-----------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | hello_world | CREATE_COMPLETE | 2015-04-01T03:20:25Z |
    +--------------------------------------+-------------+-----------------+----------------------+

Remove the stack:

::

    $ heat stack-delete hello_world
    +--------------------------------------+-------------+--------------------+----------------------+
    | id                                   | stack_name  | stack_status       | creation_time        |
    +--------------------------------------+-------------+--------------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | hello_world | DELETE_IN_PROGRESS | 2015-04-01T03:20:25Z |
    +--------------------------------------+-------------+--------------------+----------------------+

Verify that the removal of the stack has deleted the nova instance:

::

    $ nova list
    +----+------+--------+------------+-------------+----------+
    | ID | Name | Status | Task State | Power State | Networks |
    +----+------+--------+------------+-------------+----------+
    +----+------+--------+------------+-------------+----------+

While this stack is not very interesting - it just starts a single instance - it
is possible to make very complicated templates that involve dozens of instances
or adds and removes instances based on demand. Continue to the next section to
learn more.

Working with Stacks: Advanced
-----------------------------

.. todo:: needs more explanatory material

.. todo:: needs a heat template that uses fractal app

With the use of the Orchestration API, the Fractal app can create an autoscaling
group for all parts of the application, in order to dynamically provision more
compute resources during periods of heavy utilization, and also terminate compute
instances to scale down, as demand decreases.

There are two helpful articles available to learn about autoscaling with the
Orchestration API:

* http://superuser.openstack.org/articles/simple-auto-scaling-environment-with-heat
* http://superuser.openstack.org/articles/understanding-openstack-heat-auto-scaling

An example template that creates an auto-scaling wordpress instance can be found in
`the heat template repository <https://github.com/openstack/heat-templates/blob/master/hot/autoscaling.yaml>`_


Next Steps
----------

You should now be fairly confident working with the Orchestration service.
There are several calls we did not cover. To see these and more,
refer to the volume documentation of your SDK, or try a different step in the tutorial, including:

* :doc:`/section7` - to learn about more complex networking
* :doc:`/section8` - for advice for developers new to operations
* :doc:`/section9` - to see all the crazy things we think ordinary folks won't want to do ;)
