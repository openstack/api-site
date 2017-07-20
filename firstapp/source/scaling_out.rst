===========
Scaling out
===========

.. todo:: For later versions of this guide: implement a service within
          the fractals app that simply returns the CPU load on the
          local server. Then add to this section a simple loop that
          checks to see if any servers are overloaded and adds a new
          one if they are. (Or do this through SSH and w)

An often-cited reason for designing applications by using cloud
patterns is the ability to **scale out**. That is: to add additional
resources, as required. Contrast this strategy to the previous one of
increasing capacity by scaling up the size of existing resources. To
scale out, you must:

* Architect your application to make use of additional resources.
* Make it possible to add new resources to your application.

.. todo:: nickchase needs to restate the second point

The :doc:`/introduction` section describes how to build in a modular
fashion, create an API, and other aspects of the application
architecture. Now you will see why those strategies are so important.
By creating a modular application with decoupled services, you can
identify components that cause application performance bottlenecks and
scale them out. Just as importantly, you can also remove resources
when they are no longer necessary. It is very difficult to overstate
the cost savings that this feature can bring, as compared to
traditional infrastructure.

Of course, having access to additional resources is only part of the
game plan; while you can manually add or delete resources, you get
more value and more responsiveness if the application automatically
requests additional resources when it needs them.

This section continues to illustrate the separation of services onto
multiple instances and highlights some of the choices that we have
made that facilitate scalability in the application architecture.

You will progressively ramp up to use up six instances, so make sure that your
cloud account has the appropriate quota.

The previous section uses two virtual machines - one 'control' service
and one 'worker'. The speed at which your application can generate
fractals depends on the number of workers. With just one worker, you
can produce only one fractal at a time. Before long, you will need more
resources.

.. note:: If you do not have a working application, follow the steps in
          :doc:`introduction` to create one.

.. todo:: Ensure we have the controller_ip even if this is a new
          python session.

Generate load
~~~~~~~~~~~~~

To test what happens when the Fractals application is under load, you
can:

* Load the worker: Create a lot of tasks to max out the CPU of existing
  worker instances
* Load the API: Create a lot of API service requests

Create more tasks
-----------------

Use SSH with the existing SSH keypair to log in to the
:code:`app-controller` controller instance.

.. code-block:: console

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_CONTROLLER

.. note:: Replace :code:`IP_CONTROLLER` with the IP address of the
          controller instance and USERNAME with the appropriate
          user name.

Call the :code:`faafo` command-line interface to request the
generation of five large fractals.

.. code-block:: console

    $ faafo create --height 9999 --width 9999 --tasks 5

If you check the load on the worker, you can see that the instance is
not doing well. On the single CPU flavor instance, a load average
greater than 1 means that the server is at capacity.

.. code-block:: console

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_WORKER uptime
    10:37:39 up  1:44,  2 users,  load average: 1.24, 1.40, 1.36

.. note:: Replace :code:`IP_WORKER` with the IP address of the worker
          instance and USERNAME with the appropriate user name.


Create more API service requests
--------------------------------

API load is a slightly different problem than the previous one regarding
capacity to work. We can simulate many requests to the API, as follows:

Use SSH with the existing SSH keypair to log in to the
:code:`app-controller` controller instance.

.. code-block:: console

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_CONTROLLER

.. note:: Replace :code:`IP_CONTROLLER` with the IP address of the
          controller instance and USERNAME with the appropriate
          user name.

Use a for loop to call the :code:`faafo` command-line interface to
request a random set of fractals 500 times:

.. code-block:: console

    $ for i in $(seq 1 500); do faafo --endpoint-url http://IP_CONTROLLER create & done

.. note:: Replace :code:`IP_CONTROLLER` with the IP address of the
          controller instance.

If you check the load on the :code:`app-controller` API service
instance, you see that the instance is not doing well. On your single
CPU flavor instance, a load average greater than 1 means that the server is
at capacity.

.. code-block:: console

    $ uptime
    10:37:39 up  1:44,  2 users,  load average: 1.24, 1.40, 1.36

The sheer number of requests means that some requests for fractals
might not make it to the message queue for processing. To ensure that
you can cope with demand, you must also scale out the API capability
of the Fractals application.

Scaling out
~~~~~~~~~~~

Remove the existing app
-----------------------

Go ahead and delete the existing instances and security groups that
you created in previous sections. Remember, when instances in the
cloud are no longer working, remove them and re-create something new.

.. only:: shade

    .. literalinclude:: ../samples/shade/scaling_out.py
        :language: python
        :start-after: step-1
        :end-before: step-2

.. only:: fog

    .. literalinclude:: ../samples/fog/scaling_out.rb
        :language: ruby
        :start-after: step-1
        :end-before: step-2

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-1
        :end-before: step-2

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/ScalingOut.java
        :language: java
        :start-after: step-1
        :end-before: step-2


Extra security groups
---------------------

As you change the topology of your applications, you must update or
create security groups. Here, you re-create the required security
groups.

.. only:: shade

    .. literalinclude:: ../samples/shade/scaling_out.py
        :language: python
        :start-after: step-2
        :end-before: step-3

.. only:: fog

    .. literalinclude:: ../samples/fog/scaling_out.rb
        :language: ruby
        :start-after: step-2
        :end-before: step-3

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-2
        :end-before: step-3

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/ScalingOut.java
        :language: java
        :start-after: step-2
        :end-before: step-3

A floating IP helper function
-----------------------------

Define a short function to locate unused or allocate floating IPs.
This saves a few lines of code and prevents you from reaching your
floating IP quota too quickly.

.. only:: shade

    .. literalinclude:: ../samples/shade/scaling_out.py
        :language: python
        :start-after: step-3
        :end-before: step-4

.. only:: fog

    .. literalinclude:: ../samples/fog/scaling_out.rb
        :language: ruby
        :start-after: step-3
        :end-before: step-4

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-3
        :end-before: step-4

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/ScalingOut.java
        :language: java
        :start-after: step-3
        :end-before: step-4

Split the database and message queue
------------------------------------

Before you scale out your application services, like the API service or the
workers, you must add a central database and an :code:`app-services` messaging
instance. The database and messaging queue will be used to track the state of
fractals and to coordinate the communication between the services.

.. only:: shade

    .. literalinclude:: ../samples/shade/scaling_out.py
        :language: python
        :start-after: step-4
        :end-before: step-5

.. only:: fog

    .. literalinclude:: ../samples/fog/scaling_out.rb
        :language: ruby
        :start-after: step-4
        :end-before: step-5

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-4
        :end-before: step-5

 .. only:: jclouds

    .. literalinclude:: ../samples/jclouds/ScalingOut.java
        :language: java
        :start-after: step-4
        :end-before: step-5

Scale the API service
---------------------

With multiple workers producing fractals as fast as they can, the
system must be able to receive the requests for fractals as quickly as
possible. If our application becomes popular, many thousands of users
might connect to our API to generate fractals.

Armed with a security group, image, and flavor size, you can add
multiple API services:

.. only:: shade

    .. literalinclude:: ../samples/shade/scaling_out.py
        :language: python
        :start-after: step-5
        :end-before: step-6

.. only:: fog

    .. literalinclude:: ../samples/fog/scaling_out.rb
        :language: ruby
        :start-after: step-5
        :end-before: step-6

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-5
        :end-before: step-6

 .. only:: jclouds

    .. literalinclude:: ../samples/jclouds/ScalingOut.java
        :language: java
        :start-after: step-5
        :end-before: step-6

These services are client-facing, so unlike the workers they do not
use a message queue to distribute tasks. Instead, you must introduce
some kind of load balancing mechanism to share incoming requests
between the different API services.

A simple solution is to give half of your friends one address and half
the other, but that solution is not sustainable. Instead, you can use
a `DNS round robin <http://en.wikipedia.org/wiki/Round- robin_DNS>`_
to do that automatically. However, OpenStack networking can provide
Load Balancing as a Service, which :doc:`/networking` explains.

.. todo:: Add a note that we demonstrate this by using the first API
          instance for the workers and the second API instance for the
          load simulation.


Scale the workers
-----------------

To increase the overall capacity, add three workers:

.. only:: shade

    .. literalinclude:: ../samples/shade/scaling_out.py
        :language: python
        :start-after: step-6

.. only:: fog

    .. literalinclude:: ../samples/fog/scaling_out.rb
        :language: ruby
        :start-after: step-6
        :end-before: step-7

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-6
        :end-before: step-7

 .. only:: jclouds

    .. literalinclude:: ../samples/jclouds/ScalingOut.java
        :language: java
        :start-after: step-6
        :end-before: step-7

Adding this capacity enables you to deal with a higher number of
requests for fractals. As soon as these worker instances start, they
begin checking the message queue for requests, reducing the overall
backlog like a new register opening in the supermarket.

This process was obviously a very manual one. Figuring out that we
needed more workers and then starting new ones required some effort.
Ideally the system would do this itself. If you build your application
to detect these situations, you can have it automatically request and
remove resources, which saves you the effort of doing this work
yourself. Instead, the OpenStack Orchestration service can monitor
load and start instances, as appropriate. To find out how to set that
up, see :doc:`orchestration`.

Verify that we have had an impact
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the previous steps, you split out several services and expanded
capacity. To see the new features of the Fractals application, SSH to
one of the app instances and create a few fractals.

.. code-block:: console

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_API_1

.. note:: Replace :code:`IP_API_1` with the IP address of the first
          API instance and USERNAME with the appropriate user name.

Use the :code:`faafo create` command to generate fractals.

Use the :code:`faafo list` command to watch the progress of fractal
generation.

Use the :code:`faafo UUID` command to examine some of the fractals.

The `generated_by` field shows the worker that created the fractal.
Because multiple worker instances share the work, fractals are
generated more quickly and users might not even notice when a worker
fails.

.. code-block:: console

    root@app-api-1:# faafo list
    +--------------------------------------+------------------+-------------+
    |                 UUID                 |    Dimensions    |   Filesize  |
    +--------------------------------------+------------------+-------------+
    | 410bca6e-baa7-4d82-9ec0-78e409db7ade | 295 x 738 pixels | 26283 bytes |
    | 66054419-f721-492f-8964-a5c9291d0524 | 904 x 860 pixels | 78666 bytes |
    | d123e9c1-3934-4ffd-8b09-0032ca2b6564 | 952 x 382 pixels | 34239 bytes |
    | f51af10a-084d-4314-876a-6d0b9ea9e735 | 877 x 708 pixels | 93679 bytes |
    +--------------------------------------+------------------+-------------+

    root@app-api-1:# faafo show d123e9c1-3934-4ffd-8b09-0032ca2b6564
    +--------------+------------------------------------------------------------------+
    | Parameter    | Value                                                            |
    +--------------+------------------------------------------------------------------+
    | uuid         | d123e9c1-3934-4ffd-8b09-0032ca2b6564                             |
    | duration     | 1.671410 seconds                                                 |
    | dimensions   | 952 x 382 pixels                                                 |
    | iterations   | 168                                                              |
    | xa           | -2.61217                                                         |
    | xb           | 3.98459                                                          |
    | ya           | -1.89725                                                         |
    | yb           | 2.36849                                                          |
    | size         | 34239 bytes                                                      |
    | checksum     | d2025a9cf60faca1aada854d4cac900041c6fa762460f86ab39f42ccfe305ffe |
    | generated_by | app-worker-2                                                     |
    +--------------+------------------------------------------------------------------+
    root@app-api-1:# faafo show 66054419-f721-492f-8964-a5c9291d0524
    +--------------+------------------------------------------------------------------+
    | Parameter    | Value                                                            |
    +--------------+------------------------------------------------------------------+
    | uuid         | 66054419-f721-492f-8964-a5c9291d0524                             |
    | duration     | 5.293870 seconds                                                 |
    | dimensions   | 904 x 860 pixels                                                 |
    | iterations   | 348                                                              |
    | xa           | -2.74108                                                         |
    | xb           | 1.85912                                                          |
    | ya           | -2.36827                                                         |
    | yb           | 2.7832                                                           |
    | size         | 78666 bytes                                                      |
    | checksum     | 1f313aaa36b0f616b5c91bdf5a9dc54f81ff32488ce3999f87a39a3b23cf1b14 |
    | generated_by | app-worker-1                                                     |
    +--------------+------------------------------------------------------------------+

The fractals are now available from any of the app-api hosts. To
verify, visit http://IP_API_1/fractal/FRACTAL_UUID and
http://IP_API_2/fractal/FRACTAL_UUID. You now have multiple redundant
web services. If one fails, you can use the others.

.. note:: Replace :code:`IP_API_1` and :code:`IP_API_2` with the
          corresponding floating IPs. Replace FRACTAL_UUID with the UUID
          of an existing fractal.

Go ahead and test the fault tolerance. Start deleting workers and API
instances. As long as you have one of each, your application is fine.
However, be aware of one weak point. The database contains the
fractals and fractal metadata. If you lose that instance, the
application stops. Future sections will explain how to address this
weak point.

If you had a load balancer, you could distribute this load between the
two different API services. You have several options. The
:doc:`networking` section shows you one option.

In theory, you could use a simple script to monitor the load on your
workers and API services and trigger the creation of instances, which
you already know how to do. Congratulations! You are ready to create
scalable cloud applications.

Of course, creating a monitoring system for a single application might
not make sense. To learn how to use the OpenStack Orchestration
monitoring and auto-scaling capabilities to automate these steps, see
:doc:`orchestration`.

Next steps
~~~~~~~~~~

You should be fairly confident about starting instances and
distributing services from an application among these instances.

As mentioned in :doc:`/introduction`, the generated fractal images are
saved on the local file system of the API service instances. Because
you have multiple API instances up and running, the fractal images are
spread across multiple API services, which causes a number of
:code:`IOError: [Errno 2] No such file or directory` exceptions when
trying to download a fractal image from an API service instance that
does not have the fractal image on its local file system.

Go to :doc:`/durability` to learn how to use Object Storage to solve
this problem in an elegant way. Or, you can proceed to one of these
sections:

* :doc:`/block_storage`: Migrate the database to block storage, or use
  the database-as-a-service component.
* :doc:`/orchestration`: Automatically orchestrate your application.
* :doc:`/networking`: Learn about complex networking.
* :doc:`/advice`: Get advice about operations.
* :doc:`/craziness`: Learn some crazy things that you might not think to do ;)

Complete code sample
~~~~~~~~~~~~~~~~~~~~

This file contains all the code from this tutorial section. This
comprehensive code sample lets you view and run the code as a single
script.

Before you run this script, confirm that you have set your
authentication information, the flavor ID, and image ID.

.. only:: fog

    .. literalinclude:: ../samples/fog/scaling_out.rb
       :language: ruby

.. only:: shade

    .. literalinclude:: ../samples/shade/scaling_out.py
       :language: python

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
       :language: python

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/ScalingOut.java
       :language: java
