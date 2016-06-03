===============
Make it durable
===============

.. todo:: https://github.com/apache/libcloud/pull/492

.. todo:: For later versions of the guide:  Extend the Fractals app to use Swift directly, and show the actual code from there.

.. todo:: Explain how to get objects back out again.

.. todo:: Large object support in Swift
          http://docs.openstack.org/developer/swift/overview_large_objects.html

This section introduces object storage.

`OpenStack Object Storage <http://www.openstack.org/software/openstack-storage/>`_
(code-named swift) is open-source software that enables you to create
redundant, scalable data storage by using clusters of standardized servers to
store petabytes of accessible data. It is a long-term storage system for large
amounts of static data that you can retrieve, leverage, and update. Unlike
more traditional storage systems that you access through a file system, you
access Object Storage through an API.

The Object Storage API is organized around objects and containers.

Similar to the UNIX programming model, an object, such as a document or an
image, is a "bag of bytes" that contains data. You use containers to group
objects. You can place many objects inside a container, and your account can
have many containers.

If you think about how you traditionally make what you store durable, you
quickly conclude that keeping multiple copies of your objects on separate
systems is a good way strategy. However, keeping track of those multiple
copies is difficult, and building that into an app requires complicated logic.

OpenStack Object Storage automatically replicates each object at least twice
before returning 'write success' to your API call. A good strategy is to keep
three copies of objects, by default, at all times, replicating them across the
system in case of hardware failure, maintenance, network outage, or another
kind of breakage. This strategy is very convenient for app creation. You can
just dump objects into object storage and not worry about the additional work
that it takes to keep them safe.


Use Object Storage to store fractals
------------------------------------

The Fractals app currently uses the local file system on the instance to store
the images that it generates. For a number of reasons, this approach is not
scalable or durable.

Because the local file system is ephemeral storage, the fractal images are
lost along with the instance when the instance is terminated. Block-based
storage, which the :doc:`/block_storage` section discusses, avoids that
problem, but like local file systems, it requires administration to ensure
that it does not fill up, and immediate attention if disks fail.

The Object Storage service manages many of the tasks normally managed by the
application owner. The Object Storage service provides a scalable and durable
API that you can use for the fractals app, eliminating the need to be aware of
the low level details of how objects are stored and replicated, and how to
grow the storage pool. Object Storage handles replication for you. It stores
multiple copies of each object. You can use the Object Storage API to return
an object, on demand.

First, learn how to connect to the Object Storage endpoint:

.. only:: dotnet

    .. warning:: This section has not yet been completed for the .NET SDK.

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-1
        :end-before: step-2

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-1
        :end-before: step-2

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-1
        :end-before: step-2


    .. warning::

        Libcloud 0.16 and 0.17 are afflicted with a bug that means
        authentication to a swift endpoint can fail with `a Python
        exception
        <https://issues.apache.org/jira/browse/LIBCLOUD-635>`_. If
        you encounter this, you can upgrade your libcloud version, or
        apply a simple `2-line patch
        <https://github.com/fifieldt/libcloud/commit/ec58868c3344a9bfe7a0166fc31c0548ed22ea87>`_.

    .. note:: Libcloud uses a different connector for Object Storage
              to all other OpenStack services, so a conn object from
              previous sections will not work here and we have to create
              a new one named :code:`swift`.

.. only:: pkgcloud

    .. warning:: This section has not yet been completed for the pkgcloud SDK.

.. only:: openstacksdk

    .. warning:: This section has not yet been completed for the OpenStack SDK.

.. only:: phpopencloud

    .. warning:: This section has not yet been completed for the
                 PHP-OpenCloud SDK.

.. only:: shade

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-1
        :end-before: step-2

To begin to store objects, we must first make a container.
Call yours :code:`fractals`:

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-2
        :end-before: step-3

    You should see output such as:

    .. code-block:: ruby

        TBC

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-2
        :end-before: step-3

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-2
        :end-before: step-3

    You should see output such as:

    .. code-block:: python

        <Container: name=fractals, provider=OpenStack Swift>

.. only:: shade

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-2
        :end-before: step-3

    You should see output such as:

    .. code-block:: python

        Munch({u'content-length': u'0', u'x-container-object-count': u'0',
        u'accept-ranges': u'bytes', u'x-container-bytes-used': u'0',
        u'x-timestamp': u'1463950178.11674', u'x-trans-id':
        u'txc6262b9c2bc1445b9dfe3-00574277ff', u'date': u'Mon, 23 May 2016
        03:24:47 GMT', u'content-type': u'text/plain; charset=utf-8'})


You should now be able to see this container appear in a listing of
all containers in your account:

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-3
        :end-before: step-4

    You should see output such as:

    .. code-block:: ruby

        TBC

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-3
        :end-before: step-4

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-3
        :end-before: step-4

    You should see output such as:

    .. code-block:: python

        [<Container: name=fractals, provider=OpenStack Swift>]

.. only:: shade

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-3
        :end-before: step-4

    .. code-block:: python

        [Munch({u'count': 0, u'bytes': 0, u'name': u'fractals'}),
        Munch({u'count': 0, u'bytes': 0, u'name': u'fractals_segments'})]

The next logical step is to upload an object. Find a photo of a goat
on line, name it :code:`goat.jpg`, and upload it to your
:code:`fractals` container:

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-4
        :end-before: step-5

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-4
        :end-before: step-5

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-4
        :end-before: step-5

.. only:: shade

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-4
        :end-before: step-5

List objects in your :code:`fractals` container to see if the upload
was successful. Then, download the file to verify that the md5sum is
the same:

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-5
        :end-before: step-6

    ::

       TBC


    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-6
        :end-before: step-7

    ::

        TBC

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-7
        :end-before: step-8

    ::

        7513986d3aeb22659079d1bf3dc2468b

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-5
        :end-before: step-6

    ::

       Objects in fractals:
       SwiftObject{name=an amazing goat,
        uri=https://swift.some.org:8888/v1/AUTH_8997868/fractals/an%20amazing%20goat,
        etag=439884df9c1c15c59d2cf43008180048,
        lastModified=Wed Nov 25 15:09:34 AEDT 2015, metadata={}}

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-6
        :end-before: step-7

    ::

        Fetched: an amazing goat

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-7
        :end-before: step-8

    ::

        MD5 for file goat.jpg: 439884df9c1c15c59d2cf43008180048


.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-5
        :end-before: step-6

    ::

       [<Object: name=an amazing goat, size=191874, hash=439884df9c1c15c59d2cf43008180048, provider=OpenStack Swift ...>]


    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-6
        :end-before: step-7

    ::

        <Object: name=an amazing goat, size=954465, hash=7513986d3aeb22659079d1bf3dc2468b, provider=OpenStack Swift ...>

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-7
        :end-before: step-8

    ::

        7513986d3aeb22659079d1bf3dc2468b

.. only:: shade

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-5
        :end-before: step-6

    ::

        [Munch({u'hash': u'd1408b5bf6510426db6e2bafc2f90854', u'last_modified':
        u'2016-05-23T03:34:59.353480', u'bytes': 63654, u'name': u'an amazing
        goat', u'content_type': u'application/octet-stream'})]

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-6
        :end-before: step-7

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-7
        :end-before: step-8

    ::

        d1408b5bf6510426db6e2bafc2f90854

Finally, clean up by deleting the test object:

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-8
        :end-before: step-9

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-8
        :end-before: step-10

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-8
        :end-before: step-9

    .. note:: You must pass in objects and not object names to the delete commands.

    Now, no more objects are available in the :code:`fractals` container.

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-9
        :end-before: step-10

    ::

        []

.. only:: shade

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-8
        :end-before: step-9

    ::

        Munch({u'content-length': u'0', u'x-container-object-count': u'0',
        u'accept-ranges': u'bytes', u'x-container-bytes-used': u'0',
        u'x-timestamp': u'1463950178.11674', u'x-trans-id':
        u'tx46c83fa41030422493110-0057427af3', u'date': u'Mon, 23 May 2016
        03:37:23 GMT', u'content-type': u'text/plain; charset=utf-8'})


Back up the Fractals from the database on the Object Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Back up the Fractals app images, which are currently stored inside the
database, on Object Storage.

Place the images in the :code:`fractals` container:

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-10
        :end-before: step-11

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-10
        :end-before: step-11

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-10
        :end-before: step-11

.. only:: shade

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-10
        :end-before: step-11

Next, back up all existing fractals from the database to the swift container.
A simple loop takes care of that:

.. note:: Replace :code:`IP_API_1` with the IP address of the API instance.

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-11
        :end-before: step-12

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-11
        :end-before: step-12

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-11
        :end-before: step-12

    ::

        <Object: name=025fd8a0-6abe-4ffa-9686-bcbf853b71dc, size=61597, hash=b7a8a26e3c0ce9f80a1bf4f64792cd0c, provider=OpenStack Swift ...>
        <Object: name=26ca9b38-25c8-4f1e-9e6a-a0132a7a2643, size=136298, hash=9f9b4cac16893854dd9e79dc682da0ff, provider=OpenStack Swift ...>
        <Object: name=3f68c538-783e-42bc-8384-8396c8b0545d, size=27202, hash=e6ee0cd541578981c294cebc56bc4c35, provider=OpenStack Swift ...>

    .. note:: Replace :code:`IP_API_1` with the IP address of the API instance.

    .. note:: The example code uses the awesome
              `Requests library <http://docs.python-requests.org/en/latest/>`_.
              Before you try to run the previous script, make sure that
              it is installed on your system.

.. only:: shade

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-11
        :end-before: step-12

    .. note:: Replace :code:`IP_API_1` with the IP address of the API instance.

    .. note:: The example code uses the awesome
              `Requests library <http://docs.python-requests.org/en/latest/>`_.
              Before you try to run the previous script, make sure that
              it is installed on your system.


Configure the Fractals app to use Object Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. warning:: Currently, you cannot directly store generated
             images in OpenStack Object Storage. Please revisit
             this section again in the future.

Extra features
--------------

Delete containers
~~~~~~~~~~~~~~~~~

To delete a container, you must first remove all objects from the container.
Otherwise, the delete operation fails:

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-12
        :end-before: step-13

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-12
        :end-before: step-13

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-12
        :end-before: step-13

.. only:: shade

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-12
        :end-before: step-13

.. warning:: It is not possible to restore deleted objects. Be careful.

Add metadata to objects
~~~~~~~~~~~~~~~~~~~~~~~

You can complete advanced tasks such as uploading an object with metadata, as
shown in following example. For more information, see the documentation for
your SDK.

.. only:: fog

    This option also uses a bit stream to upload the file, iterating bit
    by bit over the file and passing those bits to Object Storage as they come.
    Compared to loading the entire file in memory and then sending it, this method
    is more efficient, especially for larger files.

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-13
        :end-before: step-14

.. only:: jclouds

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-13
        :end-before: step-14

.. only:: libcloud

    This option also uses a bit stream to upload the file, iterating bit
    by bit over the file and passing those bits to Object Storage as they come.
    Compared to loading the entire file in memory and then sending it, this method
    is more efficient, especially for larger files.

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-13
        :end-before: step-14

.. todo:: It would be nice to have a pointer here to section 9.

.. only:: shade

    This adds a "foo" key to the metadata that has a value of "bar".

    .. Note::

        Swift metadata keys are prepended with "x-object-meta-" so when you get
        the object with get_object(), in order to get the value of the metadata
        your key will be "x-object-meta-foo".

    .. literalinclude:: ../samples/shade/durability.py
        :start-after: step-13
        :end-before: step-14

Large objects
~~~~~~~~~~~~~

For efficiency, most Object Storage installations treat large objects,
:code:`> 5GB`, differently than smaller objects.

.. only:: fog

    .. literalinclude:: ../samples/fog/durability.rb
        :start-after: step-14
        :end-before: step-15

.. only:: jclouds

    If you work with large objects, use the :code:`RegionScopedBlobStoreContext`
    class family instead of the ones used so far.

    .. note:: Large file uploads that use the :code:`openstack-swift` provider
              are supported in only jclouds V2, currently in beta. Also, the
              default chunk size is 64 Mb. Consider changing this as homework.

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java
        :start-after: step-14
        :end-before: step-15

.. only:: libcloud

    If you work with large objects, use the :code:`ex_multipart_upload_object`
    call instead of the simpler :code:`upload_object` call. The call splits
    the large object into chunks and creates a manifest so that the chunks can
    be recombined on download. Change the :code:`chunk_size` parameter, in
    bytes, to a value that your cloud can accept.

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-14
        :end-before: step-15

.. only:: jclouds

    Complete code sample
    ~~~~~~~~~~~~~~~~~~~~

    This file contains all the code from this tutorial section. This
    class lets you view and run the code.

    Before you run this class, confirm that you have configured it for
    your cloud and the instance running the Fractals application.

    .. literalinclude:: ../samples/jclouds/Durability.java
        :language: java

.. only:: shade

    Shade's create_object function has a "use_slo" parameter (that defaults to
    true) which will break your object into smaller objects for upload and
    rejoin them if needed.

Next steps
----------

You should now be fairly confident working with Object Storage. You
can find more information about the Object Storage SDK calls at:

.. only:: fog

    https://github.com/fog/fog/blob/master/lib/fog/openstack/docs/storage.md

.. only:: libcloud

    https://libcloud.readthedocs.org/en/latest/storage/api.html

Or, try one of these tutorial steps:

* :doc:`/block_storage`: Migrate the database to block storage, or use
  the database-as-a-service component.
* :doc:`/orchestration`: Automatically orchestrate your application.
* :doc:`/networking`: Learn about complex networking.
* :doc:`/advice`: Get advice about operations.
* :doc:`/craziness`: Learn some crazy things that you might not think to do ;)
