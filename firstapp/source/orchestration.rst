=============
Orchestration
=============

This chapter explains the importance of durability and scalability for
your cloud-based applications. In most cases, really achieving these
qualities means automating tasks such as scaling and other operational
tasks.

The Orchestration module provides a template-based way to describe a
cloud application, then coordinates running the needed OpenStack API
calls to run cloud applications. The templates enable you to create
most OpenStack resource types, such as instances, networking
information, volumes, security groups, and even users. It also provides
more advanced functionality, such as instance high availability,
instance auto-scaling, and nested stacks.

The OpenStack Orchestration API contains these constructs:

* Stacks
* Resources
* Templates

You create stacks from templates, which contain resources. Resources are an
abstraction in the HOT (Heat Orchestration Template) template language, which
enables you to define different cloud resources by setting the :code:`type`
attribute.

For example, you might use the Orchestration API to create two compute
instances by creating a stack and by passing a template to the Orchestration
API. That template would contain two resources with the :code:`type` attribute
set to :code:`OS::Nova::Server`.

That is a simplistic example, of course, but the flexibility of the resource
object enables the creation of templates that contain all the required cloud
infrastructure to run an application, such as load balancers, block storage
volumes, compute instances, networking topology, and security policies.

.. note:: The Orchestration module is not deployed by default in every cloud.
          If these commands do not work, it means the Orchestration API is not
          available; ask your support team for assistance.

This section introduces the
`HOT templating language <http://docs.openstack.org/developer/heat/template_guide/hot_guide.html>`_,
and takes you through some common OpenStack Orchestration calls.

In previous sections of this guide, you used your SDK to
programatically interact with OpenStack. In this section you work from
the command line to use the Orchestration API directly through
template files.

Install the 'heat' command-line client by following this guide:
http://docs.openstack.org/cli-reference/content/install_clients.html

Then, use this guide to set up the necessary variables for your cloud in an 'openrc' file:
http://docs.openstack.org/cli-reference/content/cli_openrc.html

.. only:: dotnet

    .. warning:: the .NET SDK does not currently support OpenStack Orchestration.

.. only:: fog

    .. note:: fog `does support OpenStack Orchestration
              <https://github.com/fog/fog/tree/master/lib/fog/openstack/models/orchestration>`_.

.. only:: jclouds

    .. warning:: Jclouds does not currently support OpenStack Orchestration.
                 See this `bug report <https://issues.apache.org/jira/browse/JCLOUDS-693>`_.

.. only:: libcloud

    .. warning:: libcloud does not currently support OpenStack Orchestration.

.. only:: pkgcloud

   .. note:: Pkgcloud supports OpenStack Orchestration :D:D:D but this section
             is `not written yet <https://github.com/pkgcloud/pkgcloud/blob/master/docs/providers/openstack/orchestration.md>`_

.. only:: openstacksdk

    .. warning:: The OpenStack SDK does not currently support OpenStack Orchestration.

.. only:: phpopencloud

    .. note:: PHP-opencloud supports OpenStack Orchestration :D:D:D but this section is not written yet.

HOT templating language
-----------------------

To learn about the template syntax for OpenStack Orchestration, how to
create basic templates, and their inputs and outputs, see
`Heat Orchestration Template (HOT) Guide <http://docs.openstack.org/developer/heat/template_guide/hot_guide.html>`_.

Work with stacks: Basics
------------------------

**Stack create**

The following example uses the
`hello_faafo <https://git.openstack.org/cgit/openstack/api-site/plain/firstapp/samples/heat/hello_faafo.yaml>`_ Hot template to
demonstrate how to create a compute instance that builds and runs the Fractal
application as an all-in-one installation. These configuration settings are
passed in as parameters:

- The flavor to use
- Your ssh key name
- The unique identifier (UUID) of the image to use

::

    $ wget https://git.openstack.org/cgit/openstack/api-site/plain/firstapp/samples/heat/hello_faafo.yaml
    $ heat stack-create --template-file hello_faafo.yaml \
     --parameters flavor=m1.small\;key_name=test\;image_id=5bbe4073-90c0-4ec9-833c-092459cc4539 hello_faafo
    +--------------------------------------+-------------+--------------------+----------------------+
    | id                                   | stack_name  | stack_status       | creation_time        |
    +--------------------------------------+-------------+--------------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | hello_faafo | CREATE_IN_PROGRESS | 2015-04-01T03:20:25Z |
    +--------------------------------------+-------------+--------------------+----------------------+

The resulting stack automatically creates a Nova instance, as follows:

::

    $ nova list
    +--------------------------------------+---------------------------------+--------+------------+-------------+------------------+
    | ID                                   | Name                            | Status | Task State | Power State | Networks         |
    +--------------------------------------+---------------------------------+--------+------------+-------------+------------------+
    | 9bdf0e2f-415e-43a0-90ea-63a5faf86cf9 | hello_faafo-server-dwmwhzfxgoor | ACTIVE | -          | Running     | private=10.0.0.3 |
    +--------------------------------------+---------------------------------+--------+------------+-------------+------------------+

Use the following command to verify that the stack was successfully created:

::

    $ heat stack-list
    +--------------------------------------+-------------+-----------------+----------------------+
    | id                                   | stack_name  | stack_status    | creation_time        |
    +--------------------------------------+-------------+-----------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | hello_faafo | CREATE_COMPLETE | 2015-04-01T03:20:25Z |
    +--------------------------------------+-------------+-----------------+----------------------+

The stack reports an initial :code:`CREATE_IN_PROGRESS` status. When all
software has been installed, the status changes to :code:`CREATE_COMPLETE`.

You might have to run the :code:`stack-list` command a few times before
the stack creation is complete.

**Show information about the stack**

Run this command to get more information about the stack:

::

    $ heat stack-show hello_faafo

The `outputs` property shows the URL through which you can access the Fractal
app. You can SSH into the instance.

**Remove the stack**

::

    $ heat stack-delete hello_faafo
    +--------------------------------------+-------------+--------------------+----------------------+
    | id                                   | stack_name  | stack_status       | creation_time        |
    +--------------------------------------+-------------+--------------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | hello_faafo | DELETE_IN_PROGRESS | 2015-04-01T03:20:25Z |
    +--------------------------------------+-------------+--------------------+----------------------+

Verify the nova instance was deleted when the stack was removed:

::

    $ nova list
    +----+------+--------+------------+-------------+----------+
    | ID | Name | Status | Task State | Power State | Networks |
    +----+------+--------+------------+-------------+----------+
    +----+------+--------+------------+-------------+----------+

While this stack starts a single instance that builds and runs the Fractal app
as an all-in-one installation, you can make very complicated templates that
impact dozens of instances or that add and remove instances on demand.
Continue to the next section to learn more.

Work with stacks: Advanced

.. todo:: needs more explanatory material

.. todo:: needs a heat template that uses fractal app

With the Orchestration API, the Fractal app can create an auto-scaling group
for all parts of the application to dynamically provision more compute
resources during periods of heavy utilization, and also terminate compute
instances to scale down as demand decreases.

To learn about auto-scaling with the Orchestration API, read these articles:

* http://superuser.openstack.org/articles/simple-auto-scaling-environment-with-heat
* http://superuser.openstack.org/articles/understanding-openstack-heat-auto-scaling

For an example template that creates an auto-scaling Wordpress instance, see
`the heat template repository <https://github.com/openstack/heat-templates/blob/master/hot/autoscaling.yaml>`_


Next steps
----------

You should now be fairly confident working with the Orchestration
service. To see the calls that we did not cover and more, see the
volume documentation of your SDK. Or, try one of these steps in the
tutorial:

* :doc:`/networking`: Learn about complex networking.
* :doc:`/advice`: Get advice about operations.
* :doc:`/craziness`: Learn some crazy things that you might not think to do ;)
