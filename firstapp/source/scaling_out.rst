===========
Scaling out
===========

.. todo:: For later versions of this guide: implement a service within
          the fractals app that simply returns the CPU load on the
          local server. Then add to this section a simple loop that
          checks to see if any servers are overloaded and adds a new
          one if they are. (Or do this via SSH and w)

One of the most-often cited reasons for designing applications using
cloud patterns is the ability to **scale out**. That is: to add
additional resources as required. This is in contrast to the previous
strategy of increasing capacity by scaling up the size of existing
resources. In order for scale out to be feasible, you'll need to
do two things:

* Architect your application to make use of additional resources.
* Make it possible to add new resources to your application.

.. todo:: nickchase needs to restate the second point

In section :doc:`/introduction`, we talked about various aspects of the
application architecture, such as building in a modular fashion,
creating an API, and so on. Now you'll see why those are so
important. By creating a modular application with decoupled services,
it is possible to identify components that cause application
performance bottlenecks and scale them out.

Just as importantly, you can also remove resources when they are no
longer necessary. It is very difficult to overstate the cost savings
that this feature can bring, as compared to traditional
infrastructure.

Of course, just having access to additional resources is only part of
the battle; while it's certainly possible to manually add or destroy
resources, you'll get more value -- and more responsiveness -- if the
application simply requests new resources automatically when it needs
them.

This section continues to illustrate the separation of services onto
multiple instances and highlights some of the choices we've made that
facilitate scalability in the app's architecture.

We'll progressively ramp up to use up to about six instances, so ensure
that your cloud account has appropriate quota to handle that many.

In the previous section, we used two virtual machines - one 'control'
service and one 'worker'. In our application, the speed at which
fractals can be generated depends on the number of workers. With just
one worker, we can only produce one fractal at a time. Before long, it
will be clear that we need more resources.

.. note:: If you don't have a working application, follow the steps in
          :doc:`introduction` to create one.

.. todo:: Ensure we have the controller_ip even if this is a new
          python session.

Generate load
~~~~~~~~~~~~~

You can test for yourself what happens when the Fractals application is under
load by:

* maxing out the CPU of the existing worker instances (loading the worker)
* generating a lot of API requests (load up the API)


Create a greater number of tasks
--------------------------------

Use SSH to login to the controller instance, :code:`app-controller`,
using the previous added SSH keypair.

::

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_CONTROLLER

.. note:: Replace :code:`IP_CONTROLLER` with the IP address of the
          controller instance and USERNAME to the appropriate
          username.

Call the Fractal application's command line interface (:code:`faafo`) to
request the generation of 5 large fractals.

::

    $ faafo create --height 9999 --width 9999 --tasks 5

Now if you check the load on the worker, you can see that the instance
is not doing well. On our single CPU flavor instance, a load average
of more than 1 means we are at capacity.

::

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_WORKER uptime
    10:37:39 up  1:44,  2 users,  load average: 1.24, 1.40, 1.36

.. note:: Replace :code:`IP_WORKER` with the IP address of the worker
          instance and USERNAME to the appropriate username.


Create a greater number of API service requests
-----------------------------------------------

API load is a slightly different problem to the previous one regarding
capacity to work. We can simulate many requests to the API as follows:

Use SSH to login to the controller instance, :code:`app-controller`,
using the previous added SSH keypair.

::

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_CONTROLLER

.. note:: Replace :code:`IP_CONTROLLER` with the IP address of the
          controller instance and USERNAME to the appropriate
          username.

Call the Fractal application's command line interface (:code:`faafo`) in a for
loop to send many requests to the API. The following command will
request a random set of fractals, 500 times:

::

    $ for i in $(seq 1 500); do faafo --endpoint-url http://IP_CONTROLLER create &; done

.. note:: Replace :code:`IP_CONTROLLER` with the IP address of the
          controller instance.

Now if you check the load on the API service instance,
:code:`app-controller`, you can see that the instance is not doing
well. On our single CPU flavor instance, a load average of more than
1 means we are at capacity.

::

    $ uptime
    10:37:39 up  1:44,  2 users,  load average: 1.24, 1.40, 1.36

The number of requests coming in means that some requests for fractals
may not even get onto the message queue to be processed. To ensure we
can cope with demand, we need to scale out our API services as well.

As you can see, we need to scale out the Fractals application's API capability.

Scaling out
~~~~~~~~~~~

Remove the old app
------------------

Go ahead and delete the existing instances and security groups you
created in previous sections. Remember, when instances in the cloud
are no longer working, remove them and re-create something new.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-1
        :end-before: step-2


Extra security groups
---------------------

As you change the topology of your applications, you will need to
update or create new security groups. Here, we will re-create the
required security groups.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-2
        :end-before: step-3

A Floating IP helper function
-----------------------------

Define a short function to locate unused IPs or allocate a new floating
IP. This saves a few lines of code and prevents you from
reaching your Floating IP quota too quickly.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-3
        :end-before: step-4

Splitting off the database and message queue
--------------------------------------------

Prior to scaling out our application services, like the API service or
the workers, we have to add a central database and messaging instance,
called :code:`app-services`. The database and messaging queue will be used
to track the state of the fractals and to coordinate the communication
between the services.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-4
        :end-before: step-5

Scaling the API service
-----------------------

With multiple workers producing fractals as fast as they can, we also
need to make sure we can receive the requests for fractals as quickly
as possible. If our application becomes popular, we may have many
thousands of users trying to connect to our API to generate fractals.

Armed with our security group, image and flavor size we can now add
multiple API services:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-5
        :end-before: step-6

These are client-facing services, so unlike the workers they do not
use a message queue to distribute tasks. Instead, we'll need to
introduce some kind of load balancing mechanism to share incoming
requests between the different API services.

One simple way might be to give half of our friends one address and
half the other, but that's certainly not a sustainable solution.
Instead, we can do that automatically using a `DNS round robin
<http://en.wikipedia.org/wiki/Round-robin_DNS>`_. However, OpenStack
networking can provide Load Balancing as a Service, which we'll
explain in :doc:`/networking`.

.. todo:: Add a note that we demonstrate this by using the first API
          instance for the workers and the second API instance for the
          load simulation.


Scaling the workers
-------------------

To increase the overall capacity, we will now add 3 workers:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
        :start-after: step-6
        :end-before: step-7


Adding this capacity enables you to deal with a higher number of
requests for fractals. As soon as these worker instances come up,
they'll start checking the message queue looking for requests,
reducing the overall backlog like a new register opening in the
supermarket.

This was obviously a very manual process - figuring out we needed more
workers and then starting new ones required some effort. Ideally the
system would do this itself. If your application has been built to
detect these situations, you can have it automatically request and
remove resources, but you don't actually need to do this work
yourself. Instead, the OpenStack Orchestration service can monitor
load and start instances as appropriate. See :doc:`orchestration` to find
out how to set that up.

Verifying we've had an impact
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the steps above, we've split out several services and expanded
capacity. SSH to one of the app instances and create a few fractals.
You will see that the Fractals app has a few new features.

::

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_API_1

.. note:: Replace :code:`IP_API_1` with the IP address of the first
          API instance and USERNAME to the appropriate username.

Use the Fractal application's command line interface to generate fractals
:code:`faafo create`. Watch the progress of fractal generation with
the :code:`faafo list`. Use :code:`faafo UUID` to examine some of the
fractals. The generated_by field will show which worker created the
fractal. The fact that multiple worker instances are sharing the work
means that fractals will be generated more quickly and the death of a
worker probably won't even be noticed.

::

    root@app-api-1:/var/log/supervisor# faafo list
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

The fractals are now available from any of the app-api hosts. Visit
http://IP_API_1/fractal/FRACTAL_UUID and
http://IP_API_2/fractal/FRACTAL_UUID to verify. Now you have multiple
redundant web services. If one dies, the others can be used.

.. note:: Replace :code:`IP_API_1` and :code:`IP_API_2` with the
          corresponding Floating IPs. Replace FRACTAL_UUID the UUID
          of an existing fractal.

Go ahead and test the fault tolerance. Start destroying workers and API
instances. As long as you have one of each, your application should
be fine. There is one weak point though. The database contains the
fractals and fractal metadata. If you lose that instance, the
application will stop. Future sections will work to address this weak
point.

If we had a load balancer, we could distribute this load between the
two different API services. As mentioned previously, there are several
options. We will show one in :doc:`networking`.

You could in theory use a simple script to monitor the load on your
workers and API services and trigger the creation of new instances,
which you already know how to do. If you can see how to do that -
congratulations, you're ready to create scalable cloud applications.

Of course, creating a monitoring system just for one application may
not always be the best way. We recommend you look at :doc:`orchestration`
to find out about how you can use OpenStack Orchestration's monitoring
and autoscaling capabilities to do steps like this automatically.


Next steps
~~~~~~~~~~

You should be fairly confident now about starting new instances, and
distributing services from an application amongst the instances.

As mentioned in :doc:`/introduction` the generated fractal images will be
saved on the local filesystem of the API service instances. Because we
now have multiple API instances up and running, the fractal
images will be spread across multiple API services. This results in a number of
:code:`IOError: [Errno 2] No such file or directory` exceptions when trying to download a
fractal image from an API service instance not holding the fractal
image on its local filesystem.

From here, you should go to :doc:`/durability` to learn how to use
Object Storage to solve this problem in a elegant way. Alternatively,
you may jump to any of these sections:

* :doc:`/block_storage`: Migrate the database to block storage, or use
  the database-as-a-service component
* :doc:`/orchestration`: Automatically orchestrate your application
* :doc:`/networking`: Learn about complex networking
* :doc:`/advice`: Get advice about operations
* :doc:`/craziness`: Learn some crazy things that you might not think to do ;)


Complete code sample
~~~~~~~~~~~~~~~~~~~~

The following file contains all of the code from this
section of the tutorial. This comprehensive code sample lets you view
and run the code as a single script.

Before you run this script, confirm that you have set your authentication
information, the flavor ID, and image ID.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/scaling_out.py
       :language: python
