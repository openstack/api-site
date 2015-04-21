============================
Section One: Getting Started
============================

Who should read this book
-------------------------

This book has been written for software developers who wish to deploy
applications to OpenStack clouds.

We've assumed that you're an experienced programmer, but that you haven't
necessarily created an application for cloud in general, or for OpenStack in
particular.

If you're already familiar with OpenStack, you'll save time learning about the
general concepts, and you'll still find value in learning how to work
programmatically with it's components.

What you will learn
-------------------

Deploying applications in a cloud environment can be very different from the
traditional siloed approachyou see in traditional IT, so in addition to learning
to deploy applications on OpenStack, you will also learn some best practices for
cloud application development.  Overall, this guide covers the following:

* :doc:`/section1` - The most basic cloud application -- creating and destroying virtual resources
* :doc:`/section2` - The architecture of a sample cloud-based application
* :doc:`/section3` - The importance of message queues
* :doc:`/section4` - Scaling up and down in response to changes in application load
* :doc:`/section5` - Using object or block storage to create persistance
* :doc:`/section6` - Orchestrating your cloud for better control of the environment
* :doc:`/section7` - Networking choices and actions to help relieve potential congestion
* :doc:`/section8` - Advice for developers who may not have been exposed to operations tasks before
* :doc:`/section9` - Taking your application to the next level by spreading it across multiple regions or clouds

A general overview
------------------

This tutorial actually involves two applications; the first, a fractal
generator, simply uses mathematical equations to generate images. We'll provide
that application to you in its entirety, because really, it's just an excuse;
the real application we will be showing you is the code that enables you to make
use of OpenStack to run it.  That application includes:

* Creating and destroying compute resources.  (Those are the virtual machine instances on which the Fractals app runs.)
* Cloud-related architecture decisions, such as breaking individual functions out into microservices and modularizing them.
* Scaling up and down to customize the amount of available resources.
* Object and block storage for persistance of files and databases.
* Orchestration services to automatically adjust to the environment.
* Networking customization for better performance and segregation.
* A few other crazy things we think ordinary folks won't want to do ;).


Choosing your OpenStack SDK
---------------------------

Future versions of this book will cover completing these tasks with various
toolkits, such as the OpenStack SDK, and using various languages, such as Java
or Ruby. For now, however, this initial incarnation focuses on using Python with
Apache Libcloud. That said, if you're not a master Python programmer,
don't despair; the code is fairly straightforward, and should be readable to
anyone with a programming background.

If you're a developer for an alternate toolkit and would like to see this book
support it, great!  Please feel free to submit alternate code snippets, or to
contact any of the authors or members of the Documentation team to coordinate.

Although this guide (initially) covers only Libcloud, you actually have several
choices when it comes to building an application for an OpenStack cloud.
These choices include:

============= ============= ================================================================= ====================================================
Language      Name          Description                                                       URL
============= ============= ================================================================= ====================================================
Python        Libcloud      A Python-based library managed by the Apache Foundation.
                            This library enables you to work with multiple types of clouds.   https://libcloud.apache.org
Python        OpenStack SDK A python-based libary specifically developed for OpenStack.       https://github.com/stackforge/python-openstacksdk
Java          jClouds       A Java-based library. Like libcloud, it's also managed by the     https://jclouds.apache.org
                            Apache Foundation and works with multiple types of clouds.
Ruby          fog           A Ruby-based SDK for multiple clouds.                             http://www.fogproject.org
node.js       pkgcloud      A Node.js-based SDK for multiple clouds.                          https://github.com/pkgcloud/pkgcloud
PHP           php-opencloud A library for developers using PHP to work with OpenStack clouds. http://php-opencloud.com/
NET Framework OpenStack SDK A .NET based library that can be used to write C++ applications.  https://www.nuget.org/packages/OpenStack-SDK-DotNet
              for Microsoft
              .NET
============= ============= ================================================================= ====================================================

A list of all available SDKs is available on the
`OpenStack wiki <https://wiki.openstack.org/wiki/SDKs>`_.


What you need
-------------

We assume you already have access to an OpenStack cloud.
You should have a project (tenant) with a quota of at least
6 instances.  The Fractals application itself runs in Ubuntu, Debian, and Fedora-based and
openSUSE-based distributions, so you'll need to be creating instances using one
of these operating systems.

Interact with the cloud itself, you will also need to have

.. only:: dotnet

      `OpenStack SDK for Microsoft .NET 0.9.1 or better installed <https://www.nuget.org/packages/OpenStack-SDK-DotNet>`_.
      .. warning:: This document has not yet been completed for the .NET SDK

.. only:: fog

      `fog 1.19 or better installed <http://www.fogproject.org/wiki/index.php?title=FOGUserGuide#Installing_FOG>`_ and working
      with ruby gems 1.9
      .. warning:: This document has not yet been completed for the fog SDK

.. only:: jclouds

    `jClouds 1.8 or better installed <https://jclouds.apache.org/start/install>`_.
    .. warning:: This document has not yet been completed for the jclouds SDK

.. only:: libcloud

  `libcloud 0.15.1 or better installed <https://libcloud.apache.org/getting-started.html>`_.

.. only:: node

      `a recent version of pkgcloud installed <https://github.com/pkgcloud/pkgcloud#getting-started>`_.
      .. warning:: This document has not yet been completed for the pkgcloud SDK

.. only:: openstacksdk

    the OpenStack SDK installed.
    .. warning:: This document has not yet been completed for the OpenStack SDK

.. only:: phpopencloud

    `a recent version of php-opencloud installed <http://docs.php-opencloud.com/en/latest/>`_.
    .. warning:: This document has not yet been completed for the php-opencloud SDK


You will need the following 5 pieces of information, which you can obtain from
your cloud provider:

* auth URL
* username
* password
* project id or name (Projects are also known as tenants.)
* cloud region

You can also get this information by downloading the OpenStack RC file from the
OpenStack Dashboard. To download this file, log into the Horizon dashboard and
click Project->Access & Security->API Access->Download OpenStack RC file.
If you choose this route, be aware that the "auth URL" doesn't include the path.
In other words, if your openrc.sh file shows:

.. code-block:: bash

        export OS_AUTH_URL=http://controller:5000/v2.0

the actual auth URL will be

.. code-block:: python

        http://controller:5000



How you'll interact with OpenStack
----------------------------------

Throughout this tutorial, you'll be interacting with your OpenStack cloud
through code, using one of the SDKs listed in section "Choosing your OpenStack
SDK". In this initial version, the code snippets assume that you're using
libcloud.

.. only:: fog

    .. literalinclude:: ../../samples/fog/section1.rb
        :start-after: step-1
        :end-before: step-2

.. only:: libcloud

    To try it out, add the following code to a Python script (or use an
    interactive Python shell) by calling :code:`python -i`.

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-1
        :end-before: step-2

.. only:: openstacksdk

    .. code-block:: python

      from openstack import connection
      conn = connection.Connection(auth_url="http://controller:5000/v3",
                                   user_name="your_auth_username", password="your_auth_password", ...)


.. Note:: We'll use the :code:`conn` object throughout the tutorial, so ensure you always have one handy.

.. only:: libcloud

    .. Note:: If you receive the exception :code:`libcloud.common.types.InvalidCredsError: 'Invalid credentials with the provider'` while
              trying to run one of the following API calls please double-check your credentials.

    .. Note:: If your provider says they do not use regions, try a blank string ('') for the region_name.

Flavors and Images
------------------

In order to run your application, the first thing you'll need to do is create a
virtual machine, or launch an instance. This instance behaves (for all intents
and purposes) as a normal server.

In order to launch an instance, you will need to choose a flavor and an image.
The flavor is essentially the size of the instance, such as its number of CPUs,
amount of RAM and disk. An image is a prepared OS instalation from which your
instance is cloned. Keep in mind when booting instances that larger flavors can
be more expensive (in terms of resources, and therefore monetary cost, if you're
working in a public cloud) than smaller ones.

You can easily find out the images available in your cloud by
running some API calls:

.. only:: fog

    .. literalinclude:: ../../samples/fog/section1.rb
        :start-after: step-2
        :end-before: step-3

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-2
        :end-before: step-3

    You should see a result something like:

    .. code-block:: python

        <NodeImage: id=2cccbea0-cea9-4f86-a3ed-065c652adda5, name=ubuntu-14.04, driver=OpenStack  ...>
        <NodeImage: id=f2a8dadc-7c7b-498f-996a-b5272c715e55, name=cirros-0.3.3-x86_64, driver=OpenStack  ...>

You can also get information on the various flavors:

.. only:: fog

    .. literalinclude:: ../../samples/fog/section1.rb
        :start-after: step-3
        :end-before: step-4

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-3
        :end-before: step-4

    This code should produce output something like:

    .. code-block:: python

        <OpenStackNodeSize: id=1, name=m1.tiny, ram=512, disk=1, bandwidth=None, price=0.0, driver=OpenStack, vcpus=1,  ...>
        <OpenStackNodeSize: id=2, name=m1.small, ram=2048, disk=20, bandwidth=None, price=0.0, driver=OpenStack, vcpus=1,  ...>
        <OpenStackNodeSize: id=3, name=m1.medium, ram=4096, disk=40, bandwidth=None, price=0.0, driver=OpenStack, vcpus=2,  ...>
        <OpenStackNodeSize: id=4, name=m1.large, ram=8192, disk=80, bandwidth=None, price=0.0, driver=OpenStack, vcpus=4,  ...>
        <OpenStackNodeSize: id=5, name=m1.xlarge, ram=16384, disk=160, bandwidth=None, price=0.0, driver=OpenStack, vcpus=8,  ...>


Your images and flavors will be different, of course.

Choose an image and flavor to use for your first instance. To start with, we
only need about 1GB of RAM, 1 CPU and a GB of disk, so in this example, the
:code:`m1.small` flavor, which exceeds these requirements, in conjuction with
the Ubuntu image, is a safe choice.
The flavor and image you choose here will be used throughout this guide, so you
will need to change the IDs in the following tutorial sections to correspond to
your desired flavor and image.

If you don't see the image you want available in your cloud, you can usually
upload a new one - depending on your cloud's policy settings. There is a guide
on how to aquire images
`available here <http://docs.openstack.org/image-guide/content/ch_obtaining_images.html>`_.

Set the image and size variables to appropriate values for your cloud. We'll use
these in later sections.

First tell the connection to retrieve a specific image, using the ID of the
image you have chosen to work with in the previous section:


.. only:: fog

    .. literalinclude:: ../../samples/fog/section1.rb
        :start-after: step-4
        :end-before: step-5

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-4
        :end-before: step-5

    You should see output something like this:

    .. code-block:: python

         <NodeImage: id=2cccbea0-cea9-4f86-a3ed-065c652adda5, name=ubuntu-14.04, driver=OpenStack  ...>

Next tell the script what flavor you want to use:

.. only:: fog

    .. literalinclude:: ../../samples/fog/section1.rb
        :start-after: step-5
        :end-before: step-6


.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-5
        :end-before: step-6

    You should see output something like this:

    .. code-block:: python

        <OpenStackNodeSize: id=3, name=m1.medium, ram=4096, disk=40, bandwidth=None, price=0.0, driver=OpenStack, vcpus=2,  ...>

Now you're ready to actually launch the instance.

Booting an instance
-------------------

Now that you have selected an image and flavor, use it to create an instance.

.. only:: libcloud

    .. note:: The following instance creation assumes that you only have one
       tenant network.  If you have multiple tenant networks defined, you will
       need to add a networks parameter to the create_node call.  You'll know
       this is the case if you see an error stating 'Exception: 400 Bad Request
       Multiple possible networks found, use a Network ID to be more specific.'
       See :doc:`/appendix` for details.

Start by creating the instance.

.. note:: An instance may be called a 'node' or 'server' by your SDK.

.. only:: fog

    .. literalinclude:: ../../samples/fog/section1.rb
        :start-after: step-6
        :end-before: step-7

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-6
        :end-before: step-7

    You should see output something like:

    .. code-block:: python

       <Node: uuid=1242d56cac5bcd4c110c60d57ccdbff086515133, name=testing, state=PENDING, public_ips=[], private_ips=[], provider=OpenStack ...>

.. only:: openstacksdk

    .. code-block:: python

       args = {
           "name": "testing",
           "flavorRef": flavor,
           "imageRef": image,
       }
       instance = conn.compute.create_server(**args)

If you then output a list of existing instances...

.. only:: fog

    .. literalinclude:: ../../samples/fog/section1.rb
        :start-after: step-7
        :end-before: step-8

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-7
        :end-before: step-8

... you should see the new instance appear.

.. only:: libcloud

    .. code-block:: python

       <Node: uuid=1242d56cac5bcd4c110c60d57ccdbff086515133, name=testing, state=RUNNING, public_ips=[], private_ips=[], provider=OpenStack ...>

.. only:: openstacksdk

    .. code-block:: python

       instances = conn.compute.list_servers()
       for instance in instances:
           print(instance)

Before we move on, there's one more thing you need to do.

Destroying an instance
----------------------

It is important to keep in mind that cloud resources (including running
instances you are no longer using) can cost money.  Learning to remove cloud
resources will help you avoid any unexpected costs incurred by unnecessary
cloud resources.

.. only:: fog

    .. literalinclude:: ../../samples/fog/section1.rb
        :start-after: step-8
        :end-before: step-9

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-8
        :end-before: step-9


If you then list the instances again, you'll see that the instance no longer appears.

Leave your shell open, as you will use it for another instance deployment in this section.

Deploy the application to a new instance
----------------------------------------

Now that you are familiar with how to create and destroy instances, it is time
to deploy the sample application.  The instance you create for the app will be
similar to the first instance you created, but this time, we'll briefly
introduce a few extra concepts.

.. note:: Internet connectivity from your cloud instance is required to download the application.

When you create an instance for the application, you're going to want to give it
a bit more information than the bare instance we created and destroyed a little
while ago. We'll go into more detail in later sections, but for now, simply create
these resources so you can feed them to the instance:

* A key pair. In order to access your instance, you will need to import an SSH
  public key into OpenStack to create a key pair. This key pair will be installed
  on the new instance by OpenStack. Typically, your public key is written to
  :code:`.ssh/id_rsa.pub`. If you do not have an SSH public key file, follow
  the instructions `here <https://help.github.com/articles/generating-ssh-keys/>`_
  first. We'll cover this in depth in section 2.

.. only:: fog

    .. warning:: This section has not been completed

.. only:: libcloud

    In the following example, :code:`pub_key_file` should be set to the location
    of your public SSH key file.

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-9
        :end-before: step-10

    ::

       <KeyPair name=demokey fingerprint=aa:bb:cc... driver=OpenStack>

* Network access. By default, OpenStack will filter all traffic.  You'll need to
  create a security group that will allow HTTP and SSH access and apply it to
  your instance. We'll go into more detail in section 2.

.. only:: fog

    .. literalinclude:: ../../samples/fog/section1.rb
        :start-after: step-10
        :end-before: step-11

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-10
        :end-before: step-11

* Userdata. During instance creation, userdata may be provided to OpenStack in
  order to configure instances after they boot.  The userdata is applied to an
  instance by the cloud-init service.  This service should be pre-installed on
  the image you have chosen. We'll go into more detail in section 2.

.. only:: fog

    .. warning:: This section has not been completed

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-11
        :end-before: step-12

Now you're ready to boot and configure the new instance.

Booting and configuring an instance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Use the image, flavor, key pair, and userdata to create a new instance.  After
requesting the new instance, wait for it to finish.

.. only:: fog

    .. warning:: This section has not been completed

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-12
        :end-before: step-13

When the instance boots up, the information in the ex_userdata variable tells it
to go ahead and deploy the Fractals app.

Associating a Floating IP for external connectivity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We'll cover networking in greater detail in section 7, but in order to actually
see the application running, you'll need to know where to look for it. Your
instance will have outbound network access by default, but in order to provision
inbound network access (in other words, to make it reachable from the Internet)
you will need  an IP address. In some cases, your instance may be provisioned
with a publicly routable IP by default. You'll be able to tell in this case
because when you list the instances you'll see an IP address listed under
public_ips or private_ips.

If not, then you'll need to create a floating IP and attach it to your instance.

.. only:: fog

    .. warning:: This section has not been completed

.. only:: libcloud

    Use :code:`ex_list_floating_ip_pools()` and select the first pool of
    Floating IP addresses.  Allocate this to your project and attach it
    to your instance.

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-13
        :end-before: step-14

.. todo:: remove extra blank line after break

    You should see the Floating IP output to the command line:

    ::

        <OpenStack_1_1_FloatingIpAddress: id=4536ed1e-4374-4d7f-b02c-c3be2cb09b67, ip_addr=203.0.113.101, pool=<OpenStack_1_1_FloatingIpPool: name=floating001>, driver=<libcloud.compute.drivers.openstack.OpenStack_1_1_NodeDriver object at 0x1310b50>>

    You can then go ahead and attach it to the instance:

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-14
        :end-before: step-15

Now go ahead and run the script to start the deployment.

Accessing the application
~~~~~~~~~~~~~~~~~~~~~~~~~

Deploying application data and configuration to the instance can take some time.  Consider
enjoying a cup of coffee while you wait. After the application has been deployed, you will be able to
visit the awesome graphic interface at the link provided below using your
preferred browser.

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
        :start-after: step-15

.. note:: If you are not using floating IPs, substitute another IP address as appropriate

.. figure:: images/screenshot_webinterface.png
    :width: 800px
    :align: center
    :height: 600px
    :alt: screenshot of the webinterface
    :figclass: align-center

Next Steps
----------

Don't worry if you don't understand every part of what just happened. As we move
on to :doc:`/section2`, we'll go into these concepts in more detail.

* :doc:`/section3` - to learn how to scale the application further
* :doc:`/section4` - to learn how to make your application more durable using Object Storage
* :doc:`/section5` - to migrate the database to block storage, or use the database-as-as-service component
* :doc:`/section6` - to automatically orchestrate the application
* :doc:`/section7` - to learn about more complex networking
* :doc:`/section8` - for advice for developers new to operations
* :doc:`/section9` - to see all the crazy things we think ordinary folks won't want to do ;)

Full example code
-----------------

Here's every code snippet into a single file, in case you want to run it all in one, or
you are so experienced you don't need instruction ;) If you are going to use this,
don't forget to set your authentication information and the flavor and image ID.

.. only:: libcloud

    .. literalinclude:: ../../samples/libcloud/section1.py
       :language: python

