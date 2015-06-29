=================
Making it durable
=================

.. todo:: https://github.com/apache/libcloud/pull/492

.. todo:: For later versions of the guide:  Extend the Fractals app to use Swift directly, and show the actual code from there.

.. todo:: Explain how to get objects back out again.

.. todo:: Large object support in Swift
          http://docs.openstack.org/developer/swift/overview_large_objects.html

This section introduces object storage.  `OpenStack Object Storage
<http://www.openstack.org/software/openstack-storage/>`_ (code-named
swift) is open source software for creating redundant, scalable data
storage using clusters of standardized servers to store petabytes of
accessible data.  It is a long-term storage system for large amounts
of static data that can be retrieved, leveraged, and updated. Access
is via an API, not through a file-system like more traditional
storage.

There are a two key concepts to understand in the Object Storage
API. The Object Storage API is organized around two types of entities:

* Objects
* Containers

Similar to the Unix programming model, an object is a "bag of bytes"
that contains data, such as documents and images. Containers are used
to group objects.  You can make many objects inside a container, and
have many containers inside your account.

If you think about how you traditionally make what you store durable,
very quickly you should come to the conclusion that keeping multiple
copies of your objects on separate systems is a good way to do
that. However, keeping track of multiple copies of objects is a pain,
and building that into an app requires a lot of logic. OpenStack
Object Storage does this automatically for you behind-the-scenes -
replicating each object at least twice before returning 'write
success' to your API call. It will always work to ensure that there
are three copies of your objects (by default) at all times -
replicating them around the system in case of hardware failure,
maintenance, network outage or any other kind of breakage. This is
very convenient for app creation - you can just dump objects into
object storage and not have to care about any of this additional work
to keep them safe.


Using Object Storage to store fractals
--------------------------------------

The Fractals app currently uses the local filesystem on the instance
to store the images it generates. This is not scalable or durable, for
a number of reasons.

Because the local filesystem is ephemeral storage, if the instance is
terminated, the fractal images will be lost along with the
instance. Block based storage, which we'll discuss in
:doc:`/block_storage`, avoids that problem, but like local filesystems, it
requires administration to ensure that it does not fill up, and
immediate attention if disks fail.

The Object Storage service manages many of these tasks that normally
would require the application owner to manage them, and presents a
scalable and durable API that you can use for the fractals app,
without having to be concerned with the low level details of how the
objects are stored and replicated, and growing the storage pool. In
fact, Object Storage handles replication intrinsically, storing multiple
copies of each object and returning one of them on demand using the
API.

First, let's learn how to connect to the Object Storage endpoint:

.. only:: dotnet

    .. warning:: This section has not yet been completed for the .NET SDK.

.. only:: fog

    .. warning:: This section has not yet been completed for the fog SDK.

.. only:: jclouds

    .. warning:: This section has not yet been completed for the jclouds SDK.

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-1
        :end-before: step-2


    .. warning::

        Libcloud 0.16 and 0.17 are afflicted with a bug that means
        authentication to a swift endpoint can fail with `a Python
        exception
        <https://issues.apache.org/jira/browse/LIBCLOUD-635>`_.  If
        you encounter this, you can upgrade your libcloud version, or
        apply a simple `2-line patch
        <https://github.com/fifieldt/libcloud/commit/ec58868c3344a9bfe7a0166fc31c0548ed22ea87>`_.

    .. note:: Libcloud uses a different connector for Object Storage
              to all other OpenStack services, so a conn object from
              previous sections won't work here and we have to create
              a new one named :code:`swift`.

.. only:: pkgcloud

    .. warning:: This section has not yet been completed for the pkgcloud SDK.

.. only:: openstacksdk

    .. warning:: This section has not yet been completed for the OpenStack SDK.

.. only:: phpopencloud

    .. warning:: This section has not yet been completed for the
                 PHP-OpenCloud SDK.


To begin to store objects, we must first make a container.
Call yours :code:`fractals`:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-2
        :end-before: step-3

    You should see output such as:

    .. code-block:: python

        <Container: name=fractals, provider=OpenStack Swift>

You should now be able to see this container appear in a listing of
all containers in your account:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-3
        :end-before: step-4

    You should see output such as:

    .. code-block:: python

        [<Container: name=fractals, provider=OpenStack Swift>]

The next logical step is to upload an object. Find a photo of a goat
online, name it :code:`goat.jpg` and upload it to your container
:code:`fractals`:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-4
        :end-before: step-5

List objects in your container :code:`fractals` to see if the upload
was successful, then download the file to verify the md5sum is the
same:

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



Finally, let's clean up by deleting our test object:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-8
        :end-before: step-9

    .. note:: You need to pass in objects to the delete commands, not object names.

    Now there should be no more objects be available in the container :code:`fractals`.

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-9
        :end-before: step-10

    ::

        []

Backup the Fractals from the database on the Object Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

So let's now use the knowledge from above to backup the images of the
Fractals app, stored inside the database right now, on the Object
Storage.

Use the :code:`fractals`' container from above to put the images in:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-10
        :end-before: step-11

Next, we backup all of our existing fractals from the database to our
swift container. A simple for loop takes care of that:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-11
        :end-before: step-12

    ::

        <Object: name=025fd8a0-6abe-4ffa-9686-bcbf853b71dc, size=61597, hash=b7a8a26e3c0ce9f80a1bf4f64792cd0c, provider=OpenStack Swift ...>
        <Object: name=26ca9b38-25c8-4f1e-9e6a-a0132a7a2643, size=136298, hash=9f9b4cac16893854dd9e79dc682da0ff, provider=OpenStack Swift ...>
        <Object: name=3f68c538-783e-42bc-8384-8396c8b0545d, size=27202, hash=e6ee0cd541578981c294cebc56bc4c35, provider=OpenStack Swift ...>

    .. note:: Replace :code:`IP_API_1` with the IP address of the API instance.

    .. note:: The example code uses the awesome `Requests library <http://docs.python-requests.org/en/latest/>`_. Ensure that it is installed on your system before trying to run the script above.


Configure the Fractals app to use Object Storage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. warning:: Currently it is not possible to directly store generated
             images on the OpenStack Object Storage. Please revisit
             this section again in the future.

Extra features
--------------

Delete containers
~~~~~~~~~~~~~~~~~

One call we didn't cover above that you probably need to know is how
to delete a container.  Ensure that you have removed all objects from
the container before running this, otherwise it will fail:

.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-12
        :end-before: step-13

.. warning:: It is not possible to restore deleted objects. Be careful.

Add metadata to objects
~~~~~~~~~~~~~~~~~~~~~~~

You can also do advanced things like uploading an object with metadata, such
as in this below example, but for further information we'll refer you to the
documentation for your SDK. This option also uses a bit stream to upload the
file - iterating bit by bit over the file and passing those bits to swift as
they come, compared to loading the entire file in memory and then sending it.
This is more efficient, especially for larger files.


.. only:: libcloud

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-13
        :end-before: step-14

.. todo:: It would be nice to have a pointer here to section 9.

Large objects
~~~~~~~~~~~~~

For efficiency, most Object Storage installations treat large objects
(say, :code:`> 5GB`) differently than smaller objects.

.. only:: libcloud

    If you are working with large objects, use the
    :code:`ex_multipart_upload_object` call instead of the simpler
    :code:`upload_object` call. How the upload works behind-the-scenes
    is by splitting the large object into chunks, and creating a
    special manifest so they can be recombined on download. Alter the
    :code:`chunk_size` parameter (in bytes) according to what your
    cloud can accept.

    .. literalinclude:: ../samples/libcloud/durability.py
        :start-after: step-14
        :end-before: step-15


Next steps
----------

You should now be fairly confident working with Object Storage.
You can find more about the Object Storage SDK calls at:

.. only:: libcloud

    https://libcloud.readthedocs.org/en/latest/storage/api.html

Or try a different step in the tutorial, including:

* :doc:`/block_storage`: to migrate the database to block storage, or use
  the database-as-as-service component
* :doc:`/orchestration`: to automatically orchestrate the application
* :doc:`/networking`: to learn about more complex networking
* :doc:`/advice`: for advice for developers new to operations
