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

The OpenStack Orchestration API uses the stacks, resources, and templates
constructs.

You create stacks from templates, which contain resources. Resources are an
abstraction in the HOT (Heat Orchestration Template) template language, which
enables you to define different cloud resources by setting the :code:`type`
attribute.

For example, you might use the Orchestration API to create two compute
instances by creating a stack and by passing a template to the Orchestration
API. That template contains two resources with the :code:`type` attribute set
to :code:`OS::Nova::Server`.

That example is simplistic, of course, but the flexibility of the resource
object enables the creation of templates that contain all the required cloud
infrastructure to run an application, such as load balancers, block storage
volumes, compute instances, networking topology, and security policies.

.. note:: The Orchestration module is not deployed by default in every cloud.
          If these commands do not work, it means the Orchestration API is not
          available; ask your support team for assistance.

This section introduces the
`HOT templating language <http://docs.openstack.org/developer/heat/template_guide/hot_guide.html>`_,
and takes you through some common OpenStack Orchestration calls.

In previous sections, you used your SDK to programatically interact with
OpenStack. In this section, you use the 'heat' command-line client to access
the Orchestration API directly through template files.

Install the 'heat' command-line client by following this guide:
http://docs.openstack.org/cli-reference/content/install_clients.html

Use this guide to set up the necessary variables for your cloud in an 'openrc' file:
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

The
`hello_faafo <https://git.openstack.org/cgit/openstack/api-site/plain/firstapp/samples/heat/hello_faafo.yaml>`_ Hot template demonstrates
how to create a compute instance that builds and runs the Fractal application
as an all-in-one installation.

You pass in these configuration settings as parameters:

- The flavor
- Your ssh key name
- The unique identifier (UUID) of the image

::

    $ wget https://git.openstack.org/cgit/openstack/api-site/plain/firstapp/samples/heat/hello_faafo.yaml
    $ heat stack-create --template-file hello_faafo.yaml \
     --parameters flavor=m1.small\;key_name=test\;image_id=5bbe4073-90c0-4ec9-833c-092459cc4539 hello_faafo
    +--------------------------------------+-------------+--------------------+----------------------+
    | id                                   | stack_name  | stack_status       | creation_time        |
    +--------------------------------------+-------------+--------------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | hello_faafo | CREATE_IN_PROGRESS | 2015-04-01T03:20:25Z |
    +--------------------------------------+-------------+--------------------+----------------------+

The stack automatically creates a Nova instance, as follows:

::

    $ nova list
    +--------------------------------------+---------------------------------+--------+------------+-------------+------------------+
    | ID                                   | Name                            | Status | Task State | Power State | Networks         |
    +--------------------------------------+---------------------------------+--------+------------+-------------+------------------+
    | 9bdf0e2f-415e-43a0-90ea-63a5faf86cf9 | hello_faafo-server-dwmwhzfxgoor | ACTIVE | -          | Running     | private=10.0.0.3 |
    +--------------------------------------+---------------------------------+--------+------------+-------------+------------------+

Verify that the stack was successfully created:

::

    $ heat stack-list
    +--------------------------------------+-------------+-----------------+----------------------+
    | id                                   | stack_name  | stack_status    | creation_time        |
    +--------------------------------------+-------------+-----------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | hello_faafo | CREATE_COMPLETE | 2015-04-01T03:20:25Z |
    +--------------------------------------+-------------+-----------------+----------------------+

The stack reports an initial :code:`CREATE_IN_PROGRESS` status. When all
software is installed, the status changes to :code:`CREATE_COMPLETE`.

You might have to run the :code:`stack-list` command a few times before
the stack creation is complete.

**Show information about the stack**

Get more information about the stack:

::

    $ heat stack-show hello_faafo

The `outputs` property shows the URL through which you can access the Fractal
application. You can SSH into the instance.

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

While this stack starts a single instance that builds and runs the Fractal
application as an all-in-one installation, you can make very complicated
templates that impact dozens of instances or that add and remove instances on
demand. Continue to the next section to learn more.

Work with stacks: Advanced

With the Orchestration API, the Fractal application can create an auto-scaling
group for all parts of the application, to dynamically provision more compute
resources during periods of heavy utilization, and also terminate compute
instances to scale down, as demand decreases.

To learn about auto-scaling with the Orchestration API, read these articles:

* http://superuser.openstack.org/articles/simple-auto-scaling-environment-with-heat
* http://superuser.openstack.org/articles/understanding-openstack-heat-auto-scaling

Initially, the focus is on scaling the workers because they consume the most
resources.

The example template depends on the ceilometer project, which is part of the
`Telemetry service <https://wiki.openstack.org/wiki/Telemetry>`_.

.. note:: The Telemetry service is not deployed by default in every cloud.
          If the ceilometer commands do not work, this example does not work;
          ask your support team for assistance.

To better understand how the template works, use this guide to install the
'ceilometer' command-line client:

* http://docs.openstack.org/cli-reference/content/install_clients.html

To set up the necessary variables for your cloud in an 'openrc' file, use this
guide:

* http://docs.openstack.org/cli-reference/content/cli_openrc.html

The Telemetry service uses meters to measure a given aspect of a resources
usage. The meter that we are interested in is the :code:`cpu_util` meter.

The value of a meter is regularly sampled and saved with a timestamp.

These saved samples are aggregated to produce a statistic. The statistic that
we are interested in is **avg**: the average of the samples over a given period.

We are interested because the Telemetry service supports alarms: an alarm is
fired when our average statistic breaches a configured threshold. When the
alarm fires, an associated action is performed.

The stack we will be building uses the firing of alarms to control the
addition or removal of worker instances.

To verify that ceilometer is installed, list the known meters:

::

    $ ceilometer meter-list

This command returns a very long list of meters. After you create a meter, it
is never thrown away!

Launch the stack with auto-scaling workers:

::

    $ wget https://git.openstack.org/cgit/openstack/api-site/plain/firstapp/samples/heat/faafo_autoscaling_workers.yaml
    $ heat stack-create --template-file faafo_autoscaling_workers.yaml \
    --parameters flavor=m1.small\;key_name=test\;image_id=5bbe4073-90c0-4ec9-833c-092459cc4539 \
    faafo_autoscaling_workers
    +--------------------------------------+---------------------------+--------------------+----------------------+
    | id                                   | stack_name                | stack_status       | creation_time        |
    +--------------------------------------+---------------------------+--------------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | faafo_autoscaling_workers | CREATE_IN_PROGRESS | 2015-11-17T05:12:06Z |
    +--------------------------------------+---------------------------+--------------------+----------------------+


As before, pass in configuration settings as parameters.

And as before, the stack takes a few minutes to build!

Wait for it to reach the :code:`CREATE_COMPLETE` status:

::

    $ heat stack-list
    +--------------------------------------+---------------------------+-----------------+----------------------+
    | id                                   | stack_name                | stack_status    | creation_time        |
    +--------------------------------------+---------------------------+-----------------+----------------------+
    | 0db2c026-fb9a-4849-b51d-b1df244096cd | faafo_autoscaling_workers | CREATE_COMPLETE | 2015-11-17T05:12:06Z |
    +--------------------------------------+---------------------------+-----------------+----------------------+

Run the :code:`nova list` command. The template creates three instances:

::

    $ nova list
    +--------------------------------------+----------+--------+------------+-------------+----------------------+
    | ID                                   | Name     | Status | Task State | Power State | Networks             |
    +--------------------------------------+----------+--------+------------+-------------+----------------------+
    | 0de89b0a-5bfd-497b-bfa2-c13f6ef7a67e | api      | ACTIVE | -          | Running     | public=115.146.89.75 |
    | a6b9b334-e8ba-4c56-ab53-cacfc6f3ad43 | services | ACTIVE | -          | Running     | public=115.146.89.74 |
    | 10122bfb-881b-4122-9955-7e801dfc5a22 | worker   | ACTIVE | -          | Running     | public=115.146.89.80 |
    +--------------------------------------+----------+--------+------------+-------------+----------------------+

Note that the worker instance is part of an :code:`OS::Heat::AutoScalingGroup`.

Confirm that the stack created two alarms:

::

    $ ceilometer alarm-list
    +--------------------------------------+---------------------------------------+-------+----------+---------+------------+--------------------------------+------------------+
    | Alarm ID                             | Name                                  | State | Severity | Enabled | Continuous | Alarm condition                | Time constraints |
    +--------------------------------------+---------------------------------------+-------+----------+---------+------------+--------------------------------+------------------+
    | 2bc8433f-9f8a-4c2c-be88-d841d9de1506 | testFaafo-cpu_alarm_low-torkcwquons4  | ok    | low      | True    | True       | cpu_util < 15.0 during 1 x 60s | None             |
    | 7755cc9a-26f3-4e2b-a9af-a285ec8524da | testFaafo-cpu_alarm_high-qqtbvk36l6nq | ok    | low      | True    | True       | cpu_util > 90.0 during 1 x 60s | None             |
    +--------------------------------------+---------------------------------------+-------+----------+---------+------------+--------------------------------+------------------+

.. note:: If either alarm reports the :code:`insufficient data` state, the
          default sampling period of the stack is probably too low for your
          cloud; ask your support team for assistance. You can set the
          period through the :code:`period` parameter of the stack to match your
          clouds requirements.

Use the stack ID to get more information about the stack:

::

    $ heat stack-show 0db2c026-fb9a-4849-b51d-b1df244096cd

The outputs section of the stack contains two ceilometer command-line queries:

* :code:`ceilometer_sample_query`: shows the samples used to build the statistics.
* :code:`ceilometer_statistics_query`: shows the statistics used to trigger the alarms.

These queries provide a view into the behavior of the stack.

In a new Terminal window, SSH into the 'api' API instance. Use the key pair
name that you passed in as a parameter.

::

    $ ssh -i ~/.ssh/test USERNAME@IP_API


In your SSH session, confirm that no fractals were generated:

::

    $ faafo list
    201-11-18 11:07:20.464 8079 INFO faafo.client [-] listing all fractals
    +------+------------+----------+
    | UUID | Dimensions | Filesize |
    +------+------------+----------+
    +------+------------+----------+

Then, create a pair of large fractals:

::

    $ faafo create --height 9999 --width 9999 --tasks 2

In the Terminal window where you run ceilometer, run
:code:`ceilometer_sample_query` to see the samples.

::

    $ ceilometer sample-list -m cpu_util -q metadata.user_metadata.stack=0db2c026-fb9a-4849-b51d-b1df244096cd
    +--------------------------------------+----------+-------+----------------+------+---------------------+
    | Resource ID                          | Name     | Type  | Volume         | Unit | Timestamp           |
    +--------------------------------------+----------+-------+----------------+------+---------------------+
    | 10122bfb-881b-4122-9955-7e801dfc5a22 | cpu_util | gauge | 100.847457627  | %    | 2015-11-18T00:15:50 |
    | 10122bfb-881b-4122-9955-7e801dfc5a22 | cpu_util | gauge | 82.4754098361  | %    | 2015-11-18T00:14:51 |
    | 10122bfb-881b-4122-9955-7e801dfc5a22 | cpu_util | gauge | 0.45           | %    | 2015-11-18T00:13:50 |
    | 10122bfb-881b-4122-9955-7e801dfc5a22 | cpu_util | gauge | 0.466666666667 | %    | 2015-11-18T00:12:50 |
    +--------------------------------------+----------+-------+----------------+------+---------------------+

The CPU utilization across workers increases as workers start to create the fractals.

Run the :code:`ceilometer_statistics_query`: command to see the derived statistics.

::

    $ ceilometer statistics -m cpu_util -q metadata.user_metadata.stack=0db2c026-fb9a-4849-b51d-b1df244096cd -p 60 -a avg
    +--------+---------------------+---------------------+----------------+----------+---------------------+---------------------+
    | Period | Period Start        | Period End          | Avg            | Duration | Duration Start      | Duration End        |
    +--------+---------------------+---------------------+----------------+----------+---------------------+---------------------+
    | 60     | 2015-11-18T00:12:45 | 2015-11-18T00:13:45 | 0.466666666667 | 0.0      | 2015-11-18T00:12:50 | 2015-11-18T00:12:50 |
    | 60     | 2015-11-18T00:13:45 | 2015-11-18T00:14:45 | 0.45           | 0.0      | 2015-11-18T00:13:50 | 2015-11-18T00:13:50 |
    | 60     | 2015-11-18T00:14:45 | 2015-11-18T00:15:45 | 82.4754098361  | 0.0      | 2015-11-18T00:14:51 | 2015-11-18T00:14:51 |
    | 60     | 2015-11-18T00:15:45 | 2015-11-18T00:16:45 | 100.847457627  | 0.0      | 2015-11-18T00:15:50 | 2015-11-18T00:15:50 |
    +--------+---------------------+---------------------+----------------+----------+---------------------+---------------------+

.. note:: The samples and the statistics are listed in opposite time order!

See the state of the alarms set up by the template:

::

    $ ceilometer alarm-list
    +--------------------------------------+---------------------------------------+-------+----------+---------+------------+--------------------------------+------------------+
    | Alarm ID                             | Name                                  | State | Severity | Enabled | Continuous | Alarm condition                | Time constraints |
    +--------------------------------------+---------------------------------------+-------+----------+---------+------------+--------------------------------+------------------+
    | 56c3022e-f23c-49ad-bf59-16a6875f3bdf | testFaafo-cpu_alarm_low-miw5tmomewot  | ok    | low      | True    | True       | cpu_util < 15.0 during 1 x 60s | None             |
    | 70ff7b00-d56d-4a43-bbb2-e18952ae6605 | testFaafo-cpu_alarm_high-ffhsmylfzx43 | alarm | low      | True    | True       | cpu_util > 90.0 during 1 x 60s | None             |
    +--------------------------------------+---------------------------------------+-------+----------+---------+------------+--------------------------------+------------------+

Run the :code:`nova list` command to confirm that the
:code:`OS::Heat::AutoScalingGroup` created more instances:

::

    $ nova list
    +--------------------------------------+----------+--------+------------+-------------+----------------------+
    | ID                                   | Name     | Status | Task State | Power State | Networks             |
    +--------------------------------------+----------+--------+------------+-------------+----------------------+
    | 0de89b0a-5bfd-497b-bfa2-c13f6ef7a67e | api      | ACTIVE | -          | Running     | public=115.146.89.96 |
    | a6b9b334-e8ba-4c56-ab53-cacfc6f3ad43 | services | ACTIVE | -          | Running     | public=115.146.89.95 |
    | 10122bfb-881b-4122-9955-7e801dfc5a22 | worker   | ACTIVE | -          | Running     | public=115.146.89.97 |
    | 31e7c020-c37c-4311-816b-be8afcaef8fa | worker   | ACTIVE | -          | Running     | public=115.146.89.99 |
    | 3fff2489-488c-4458-99f1-0cc50363ae33 | worker   | ACTIVE | -          | Running     | public=115.146.89.98 |
    +--------------------------------------+----------+--------+------------+-------------+----------------------+

Now, wait until all the fractals are generated and the instances have idled
for some time.

Run the :code:`nova list` command to confirm that the
:code:`OS::Heat::AutoScalingGroup` removed the unneeded instances:

::

    $ nova list
    +--------------------------------------+----------+--------+------------+-------------+----------------------+
    | ID                                   | Name     | Status | Task State | Power State | Networks             |
    +--------------------------------------+----------+--------+------------+-------------+----------------------+
    | 0de89b0a-5bfd-497b-bfa2-c13f6ef7a67e | api      | ACTIVE | -          | Running     | public=115.146.89.96 |
    | a6b9b334-e8ba-4c56-ab53-cacfc6f3ad43 | services | ACTIVE | -          | Running     | public=115.146.89.95 |
    | 3fff2489-488c-4458-99f1-0cc50363ae33 | worker   | ACTIVE | -          | Running     | public=115.146.89.98 |
    +--------------------------------------+----------+--------+------------+-------------+----------------------+

.. note:: The :code:`OS::Heat::AutoScalingGroup` removes instances in creation order.
          So the worker instance that was created first is the first instance
          to be removed.

In the outputs section of the stack, you can run these web API calls:

* :code:`scale__workers_up_url`: A post to this url will add worker instances.
* :code:`scale_workers_down_url`: A post to this url will remove worker instances.

These demonstrate how the Ceilometer alarms add and remove instances.
To use them:

::

    $  curl -X POST "Put the very long url from the template outputs section between these quotes"

To recap:

The auto-scaling stack sets up an API instance, a services instance, and an
auto-scaling group with a single worker instance. It also sets up ceilometer
alarms that add worker instances to the auto-scaling group when it is under
load, and removes instances when the group is idling. To do this, the alarms
post to URLs.

In this template, the alarms use metadata that is attached to each worker
instance. The metadata is in the :code:`metering.stack=stack_id` format.

The prefix is `metering.` For example, `metering.some_name`.

::

    $ nova show <instance_id>
    ...
    | metadata | {"metering.some_name": "some_value"} |
    ...

You can aggregate samples and calculate statistics across all instances with
the `metering.some_name` metadata that has `some_value` by using a query of
the form:

::

    -q metadata.user_metadata.some_name=some_value

For example:

::

    $ ceilometer sample-list -m cpu_util -q metadata.user_metadata.some_name=some_value
    $ ceilometer statistics -m cpu_util -q metadata.user_metadata.some_name=some_value -p 6

The alarms have the form:

::

    matching_metadata: {'metadata.user_metadata.stack': {get_param: "OS::stack_id"}}

Spend some time playing with the stack and the Fractal app to see how it works.

.. note:: The message queue can take a while to notice that worker instances have died.

Next steps
----------

You should now be fairly confident working with the Orchestration
service. To see the calls that we did not cover and more, see the
volume documentation of your SDK. Or, try one of these steps in the
tutorial:

* :doc:`/networking`: Learn about complex networking.
* :doc:`/advice`: Get advice about operations.
* :doc:`/craziness`: Learn some crazy things that you might not think to do ;)
