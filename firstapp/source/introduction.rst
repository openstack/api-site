=====================================================
Introduction to the fractals application architecture
=====================================================

This section introduces the application architecture and explains how it was
designed to take advantage of cloud features in general and OpenStack in
particular. It also describes some commands in the previous section.

.. todo:: (for Nick) Improve the architecture discussion.

.. only:: dotnet

    .. warning:: This section has not yet been completed for the .NET SDK.

.. only:: fog

    .. warning:: This section has not yet been completed for the fog SDK.

.. only:: jclouds

    .. warning:: This section has not yet been completed for the jclouds SDK.

.. only:: pkgcloud

    .. warning:: This section has not yet been completed for the pkgcloud SDK.

.. only:: openstacksdk

    .. warning:: This section has not yet been completed for the OpenStack SDK.

.. only:: phpopencloud

    .. warning:: This section has not yet been completed for the
                 PHP-OpenCloud SDK.


Cloud application architecture principles
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Cloud applications typically share several design principles.
These principles influenced the design of the Fractals application.

.. todo:: Do you want to state the core design principles or assume
          the reader can follow below.


Modularity and micro-services
-----------------------------

`Micro-services <http://en.wikipedia.org/wiki/Microservices>`_ are an
important design pattern that helps achieve application modularity. Separating
logical application functions into independent services simplifies maintenance
and re-use. Decoupling components also makes it easier to selectively scale
individual components, as required. Further, application modularity is a
required feature of applications that scale out well and are fault tolerant.

Scalability
-----------

Cloud applications often use many small instances rather than a few large
instances. Provided that an application is sufficiently modular, you can
easily distribute micro-services across as many instances as required. This
architecture enables an application to grow past the limit imposed by the
maximum size of an instance. It's like trying to move a large number of people
from one place to another; there's only so many people you can put on the
largest bus, but you can use an unlimited number of buses or small cars, which
provide just the capacity you need - and no more.

Fault tolerance
---------------

In cloud programming, there's a well-known analogy known as "cattle vs
pets". If you haven't heard it before, it goes like this:

When you're dealing with pets, you name them and care for them and if
they get sick, you nurse them back to health. Nursing pets back to
health can be difficult and very time consuming. When you're dealing
with cattle, you attach a numbered tag to their ear and if they get
sick you put them down and move on.

That, as it happens, is the new reality of programming. Applications
and systems used to be created on large, expensive servers, cared for
by operations staff dedicated to keeping them healthy. If something
went wrong with one of those servers, the staff's job was to do
whatever it took to make it right again and save the server and the
application.

In cloud programming, it's very different. Rather than large,
expensive servers, you're dealing with virtual machines that are
literally disposable; if something goes wrong, you shut it down and
spin up a new one. There's still operations staff, but rather than
nursing individual servers back to health, their job is to monitor the
health of the overall system.

There are definite advantages to this architecture. It's easy to get a
"new" server, without any of the issues that inevitably arise when a
server has been up and running for months, or even years.

As with classical infrastructure, failures of the underpinning cloud
infrastructure (hardware, networks, and software) are
unavoidable. When you're designing for the cloud, it's crucial that
your application is designed for an environment where failures can
happen at any moment. This may sound like a liability, but it's not;
by designing your application with a high degree of fault tolerance,
you're also making it resilient in the face of change, and therefore
more adaptable.

Fault tolerance is essential to the cloud-based application.

Automation
----------

If an application is meant to automatically scale up and down to meet
demand, it is not feasible have any manual steps in the process of
deploying any component of the application. Automation also decreases
the time to recovery for your application in the event of component
failures, increasing fault tolerance and resilience.

Programmatic interfaces (APIs)
------------------------------

Like many cloud applications, the Fractals application has a
`RESTful API <http://en.wikipedia.org/wiki/Representational_state_transfer>`_.
You can connect to it directly and generate fractals, or you can integrate it
as a component of a larger application. Any time a standard interface such as
an API is available, automated testing becomes much more feasible, increasing
software quality.

Fractals application architecture
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Fractals application was designed with the principles of the previous
subsection in mind. You'll note that in :doc:`getting_started`, we deployed the
application in an all-in-one style, on a single virtual machine. This isn't
good practice, but because the application uses micro-services to decouple
logical application functions, we can change this easily.

.. graphviz:: images/architecture.dot

Message queues are used to facilitate communication between the
Fractal application services. The Fractal application uses a `work queue
<https://www.rabbitmq.com/tutorials/tutorial-two-python.html>`_ (or
task queue) to distribute tasks to the worker services.

Message queues work in a way similar to a queue (or a line, for those
of us on the other side of the ocean) in a bank being served by
multiple clerks. The message queue in our application provides a feed
of work requests that can be taken one-at-a-time by worker services,
whether there is a single worker service or hundreds of them.

This is a `useful pattern <https://msdn.microsoft.com/en-us/library/dn568101.aspx>`_
for many cloud applications that have long lists of requests coming in and a
pool of resources from which to service them. This also means that a
worker may crash and the tasks will be processed by other workers.

.. note:: The `RabbitMQ getting started tutorial
          <https://www.rabbitmq.com/getstarted.html>`_ provides a
          great introduction to message queues.

.. graphviz:: images/work_queue.dot

The worker service consumes messages from the work queue and then processes
them to create the corresponding fractal image file.

Of course there's also a web interface which offers a more human
friendly way of accessing the API to view the created fractal images,
and a simple command line interface.

.. figure:: images/screenshot_webinterface.png
    :width: 800px
    :align: center
    :height: 600px
    :alt: screenshot of the webinterface
    :figclass: align-center


There are also multiple storage back ends (to store the generated
fractal images) and a database component (to store the state of
tasks), but we'll talk about those in :doc:`/durability` and
:doc:`/block_storage` respectively.

How the Fractals application interacts with OpenStack
-----------------------------------------------------

.. todo:: Description of the components of OpenStack and how they
          relate to the Fractals application and how it runs on the cloud.
          TF notes this is already covered in the guide, just split
          across each section. Adding it here forces the
          introduction of block storage, object storage, orchestration
          and neutron networking too early, which could seriously
          confuse users who don't have these services in their
          cloud. Therefore, this should not be done here.


The magic revisited
~~~~~~~~~~~~~~~~~~~

So what exactly was that request doing at the end of the previous
section?  Let's look at it again. (Note that in this subsection, we're
just explaining what you've already done in the previous section; you
don't need to execute these commands again.)

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-1
        :end-before: step-2

We explained image and flavor in :doc:`getting_started`, so in the following
sections, we will explain the other parameters in detail, including
:code:`ex_userdata` (cloud-init) and :code:`ex_keyname` (key pairs).


Introduction to cloud-init
--------------------------

`cloud-init <https://cloudinit.readthedocs.org/en/latest/>`_ is a tool
that performs instance configuration tasks during the boot of a cloud
instance, and comes installed on most cloud
images. :code:`ex_userdata`, which was passed to :code:`create_node`,
is the configuration data passed to cloud-init.

In this case, we are presenting a shell script as the `userdata
<https://cloudinit.readthedocs.org/en/latest/topics/format.html#user-data-script>`_.
When :code:`create_node` creates the instance, :code:`cloud-init`
executes the shell script in the :code:`userdata` variable.

When an SSH public key is provided during instance creation,
cloud-init installs this key on a user account. (The user name
varies between cloud images.)  See the `Obtaining Images <http://docs.openstack.org/image-guide/content/ch_obtaining_images.html>`_
section of the image guide for guidance about which user name you
should use when SSHing. If you still have problems logging in, ask
your cloud provider to confirm the user name.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-2
        :end-before: step-3


After the instance is created, cloud-init downloads and runs a script called
:code:`install.sh`. This script installs the Fractals application. Cloud-init
can consume bash scripts and a number of different types of data. You
can even provide multiple types of data. You can find more information
about cloud-init in the `official documentation <https://cloudinit.readthedocs.org/en/latest/>`_.

Introduction to key pairs
-------------------------

Security is important when it comes to your instances; you can't have just
anyone accessing them. To enable logging into an instance, you must provide
the public key of an SSH key pair during instance creation. In section one,
you created and uploaded a key pair to OpenStack, and cloud-init installed it
for the user account.

Even with a key in place, however, you must have the appropriate
security group rules in place to access your instance.

Introduction to security groups
-------------------------------

Security groups are sets of network access rules that are applied to
an instance's networking. By default, only egress (outbound) traffic
is allowed. You must explicitly enable ingress (inbound) network
access by creating a security group rule.

.. warning:: Removing the egress rule created by OpenStack will cause
             your instance networking to break.

Start by creating a security group for the all-in-one instance and
adding the appropriate rules, such as HTTP (TCP port 80) and SSH (TCP
port 22):

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-3
        :end-before: step-4


.. note:: :code:`ex_create_security_group_rule()` takes ranges of
          ports as input. This is why ports 80 and 22 are passed
          twice.

You can list available security groups with:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-4
        :end-before: step-5


Once you've created a rule or group, you can also delete it:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-5
        :end-before: step-6


To see which security groups apply to an instance, you can:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-6
        :end-before: step-7


.. todo:: print() ?

Once you've configured permissions, you'll need to know where to
access the application.

Introduction to Floating IPs
----------------------------

As in traditional IT, cloud instances are accessed through IP addresses that
OpenStack assigns. How this is actually done depends on the networking setup
for your cloud. In some cases, you will simply get an Internet rout-able IP
address assigned directly to your instance.

The most common way for OpenStack clouds to allocate Internet rout-able
IP addresses to instances, however, is through the use of floating
IPs. A floating IP is an address that exists as an entity unto
itself, and can be associated to a specific instance network
interface. When a floating IP address is associated to an instance
network interface, OpenStack re-directs traffic bound for that address
to the address of the instance's internal network interface
address. Your cloud provider will generally offer pools of floating
IPs for your use.

To use a floating IP, you must first allocate an IP to your project,
then associate it to your instance's network interface.

.. note::

    Allocating a floating IP address to an instance does not change
    the IP address of the instance, it causes OpenStack to establish
    the network translation rules to allow an *additional* IP address.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-7
        :end-before: step-8


If you have no free floating IPs that have been previously allocated
for your project, first select a floating IP pool offered by your
provider. In this example, we have selected the first one and assume
that it has available IP addresses.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-8
        :end-before: step-9

Now request that an address from this pool be allocated to your project.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-9
        :end-before: step-10

Now that you have an unused floating IP address allocated to your
project, attach it to an instance.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-10
        :end-before: step-11

That brings us to where we ended up at the end of
:doc:`/getting_started`. But where do we go from here?

Splitting services across multiple instances
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We've talked about separating functions into different micro-services,
and how that enables us to make use of the cloud architecture. Now
let's see that in action.

The rest of this tutorial won't reference the all-in-one instance you
created in section one. Take a moment to delete this instance.

It's easy to split out services into multiple instances. We will
create a controller instance called :code:`app-controller`, which
hosts the API, database, and messaging services. We'll also create a
worker instance called :code:`app-worker-1`, which just generates
fractals.

The first step is to start the controller instance. The instance has
the API service, the database, and the messaging service, as you can
see from the parameters passed to the installation script.

========== ====================== =============================
Parameter  Description            Values
========== ====================== =============================
:code:`-i` Install a service      :code:`messaging` (install RabbitMQ) and :code:`faafo` (install the Faafo app).
:code:`-r` Enable/start something :code:`api` (enable and start the API service), :code:`worker` (enable and start the worker service), and :code:`demo` (run the demo mode to request random fractals).
========== ====================== =============================

.. todo:: https://bugs.launchpad.net/openstack-manuals/+bug/1439918

.. only:: libcloud


    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-11
        :end-before: step-12

Note that this time, when you create a security group, you're
including a rule that only applies for instances that are part of the
worker_group.

Next, start a second instance, which will be the worker instance:

.. todo :: more text necessary here...


.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-12
        :end-before: step-13

Notice that you've added this instance to the worker_group, so it can
access the controller.

As you can see from the parameters passed to the installation script, you are
specifying that this is the worker instance, but you're also passing the
address of the API instance and the message queue so the worker can pick up
requests. The Fractals application installation script can take several
parameters.

========== ==================================================== ====================================
Parameter  Description                                          Example
========== ==================================================== ====================================
:code:`-e` The endpoint URL of the API service.                 http://localhost/
:code:`-m` The transport URL of the messaging service.          amqp://guest:guest@localhost:5672/
:code:`-d` The connection URL for the database (not used here). sqlite:////tmp/sqlite.db
========== ==================================================== ====================================

Now if you make a request for a new fractal, you connect to the
controller instance, :code:`app-controller`, but the work will
actually be performed by a separate worker instance -
:code:`app-worker-1`.

Login with SSH and use the Fractal app
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Login to the worker instance, :code:`app-worker-1`, with SSH, using
the previous added SSH key pair "demokey". Start by getting the IP
address of the worker:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
        :start-after: step-13
        :end-before: step-14

Now you can SSH into the instance:

::

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_WORKER_1

.. note:: Replace :code:`IP_WORKER_1` with the IP address of the
          worker instance and USERNAME to the appropriate user name.

Once you've logged in, check to see whether the worker service process
is running as expected.  You can find the logs of the worker service
in the directory :code:`/var/log/supervisor/`.

::

    worker # ps ax | grep faafo-worker
    17210 ?        R      7:09 /usr/bin/python /usr/local/bin/faafo-worker

Open :code:`top` to monitor the CPU usage of the :code:`faafo-worker` process.

Now log into the controller instance, :code:`app-controller`, also
with SSH, using the previously added SSH key pair "demokey".

::

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_CONTROLLER

.. note:: Replace :code:`IP_CONTROLLER` with the IP address of the
          controller instance and USERNAME to the appropriate user name.

Check to see whether the API service process is running like
expected. You can find the logs for the API service in the directory
:file:`/var/log/supervisor/`.

::

    controller # ps ax | grep faafo-api
    17209 ?        Sl     0:19 /usr/bin/python /usr/local/bin/faafo-api

Now call the Fractal application's command line interface (:code:`faafo`) to
request a few new fractals. The following command requests a few
fractals with random parameters:

::

    controller # faafo --endpoint-url http://localhost --verbose create
    2015-04-02 03:55:02.708 19029 INFO faafo.client [-] generating 6 task(s)

Watch :code:`top` on the worker instance. Right after calling
:code:`faafo` the :code:`faafo-worker` process should start consuming
a lot of CPU cycles.

::

      PID USER      PR  NI    VIRT    RES    SHR S %CPU %MEM     TIME+ COMMAND
    17210 root      20   0  157216  39312   5716 R 98.8  3.9  12:02.15 faafo-worker

To show the details of a specific fractal use the subcommand
:code:`show` of the Faafo CLI.

::

    controller # faafo show 154c7b41-108e-4696-a059-1bde9bf03d0a
    +------------+------------------------------------------------------------------+
    | Parameter  | Value                                                            |
    +------------+------------------------------------------------------------------+
    | uuid       | 154c7b41-108e-4696-a059-1bde9bf03d0a                             |
    | duration   | 4.163147 seconds                                                 |
    | dimensions | 649 x 869 pixels                                                 |
    | iterations | 362                                                              |
    | xa         | -1.77488588389                                                   |
    | xb         | 3.08249829401                                                    |
    | ya         | -1.31213919301                                                   |
    | yb         | 1.95281690897                                                    |
    | size       | 71585 bytes                                                      |
    | checksum   | 103c056f709b86f5487a24dd977d3ab88fe093791f4f6b6d1c8924d122031902 |
    +------------+------------------------------------------------------------------+

There are more commands available; find out more details about them
with :code:`faafo get --help`, :code:`faafo list --help`, and
:code:`faafo delete --help`.

.. note:: The application stores the generated fractal images directly
          in the database used by the API service instance.  Storing
          image files in a database is not good practice. We're doing it
          here as an example only as an easy way to allow multiple
          instances to have access to the data. For best practice, we
          recommend storing objects in Object Storage, which is
          covered in :doc:`durability`.

Next steps
~~~~~~~~~~

You should now have a basic understanding of the architecture of
cloud-based applications. In addition, you have had practice
starting new instances, automatically configuring them at boot, and
even modularizing an application so that you may use multiple
instances to run it. These are the basic steps for requesting and
using compute resources in order to run your application on an
OpenStack cloud.

From here, you should go to :doc:`/scaling_out` to learn how to scale your
application further. Alternatively, you may jump to any of these
sections:

* :doc:`/durability`: Learn how to use Object Storage to make your application more durable
* :doc:`/block_storage`: Migrate the database to block storage, or use
  the database-as-a-service component
* :doc:`/orchestration`: Automatically orchestrate the application
* :doc:`/networking`: Learn about more complex networking
* :doc:`/advice`: Get advice about operations
* :doc:`/craziness`: Learn some crazy things that you might not think to do ;)


Complete code sample
~~~~~~~~~~~~~~~~~~~~

The following file contains all of the code from this section of the tutorial.
This comprehensive code sample lets you view and run the code as a single script.

Before you run this script, confirm that you have set your authentication
information, the flavor ID, and image ID.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/introduction.py
       :language: python
