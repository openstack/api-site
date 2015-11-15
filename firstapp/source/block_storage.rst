=============
Block Storage
=============

.. todo:: (For nick: Restructure the introduction to this chapter to
          provide context of what we're actually going to do.)

By default, data in OpenStack instances is stored on 'ephemeral' disks. These
disks stay with the instance throughout its lifetime, but when the instance is
terminated, that storage and all the data stored on it disappears. Ephemeral
storage is allocated to a single instance and cannot be moved to another
instance.

This section introduces block storage, also known as volume storage, which
provides access to persistent storage devices. You interact with block storage
by attaching volumes to running instances just as you might attach a USB drive
to a physical server. You can detach volumes from one instance and reattach
them to another instance and the data remains intact. The OpenStack Block
Storage (cinder) project implements block storage.

Though you might have configured Object Storage to store images, the Fractal
application needs a database to track the location of and parameters that were
used to create images in Object Storage. This database server cannot fail.

If you are an advanced user, consider how you might remove the database from
the architecture and replace it with Object Storage metadata (then contribute
these steps to :doc:`craziness`). Other users can continue reading to learn
how to work with block storage and move the Fractal application database
server to use it.

Basics
~~~~~~

Later on, we'll use a Block Storage volume to provide persistent storage for
the database server for the Fractal application. But first, learn how to
create and attach a Block Storage device.

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


As always, connect to the API endpoint:

.. only:: libcloud

    .. code-block:: python

      from libcloud.compute.types import Provider
      from libcloud.compute.providers import get_driver

        auth_username = 'your_auth_username'
        auth_password = 'your_auth_password'
        auth_url = 'http://controller:5000'
        project_name = 'your_project_name_or_id'
        region_name = 'your_region_name'

        provider = get_driver(Provider.OPENSTACK)
        connection = provider(auth_username,
                              auth_password,
                              ex_force_auth_url=auth_url,
                              ex_force_auth_version='2.0_password',
                              ex_tenant_name=project_name,
                              ex_force_service_region=region_name)

.. only:: shade

    .. literalinclude:: ../samples/shade/block_storage.py
        :language: python
        :start-after: step-1
        :end-before: step-2

To try it out, make a 1GB volume called :test'.

.. only:: libcloud

    .. code-block:: python

        volume = connection.create_volume(1, 'test')
        print(volume)

    ::

        <StorageVolume id=755ab026-b5f2-4f53-b34a-6d082fb36689 size=1 driver=OpenStack>

.. only:: shade

    .. literalinclude:: ../samples/shade/block_storage.py
        :language: python
        :start-after: step-2
        :end-before: step-3

.. note:: The parameter :code:`size` is in gigabytes.

List all volumes to see if it was successful:

.. only:: libcloud

    .. code-block:: python

        volumes = connection.list_volumes()
        print(volumes)

    ::

        [<StorageVolume id=755ab026-b5f2-4f53-b34a-6d082fb36689 size=1 driver=OpenStack>]

.. only:: shade

    .. literalinclude:: ../samples/shade/block_storage.py
        :language: python
        :start-after: step-3
        :end-before: step-4

Attach the storage volume to a running instance.

Use Block Storage for the Fractal database server
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You need a server for the dedicated database. Use the image, flavor, and
keypair that you used in :doc:`/getting_started` to launch an
:code:`app-database` instance.

You also need a security group to permit access to the database server (for
MySQL, port 3306) from the network:

.. only:: libcloud

    .. code-block:: python

       db_group = connection.ex_create_security_group('database', 'for database service')
       connection.ex_create_security_group_rule(db_group, 'TCP', 3306, 3306)
       instance = connection.create_node(name='app-database',
                                         image=image,
                                         size=flavor,
                                         ex_keyname=keypair_name,
                                         ex_security_groups=[db_group])

.. only:: shade

    .. literalinclude:: ../samples/shade/block_storage.py
        :language: python
        :start-after: step-4
        :end-before: step-5

Create a volume object by using the unique identifier (UUID) for the volume.
Then, use the server object from the previous code snippet to attach the
volume to it at :code:`/dev/vdb`:

.. only:: libcloud

    .. code-block:: python

        volume = connection.ex_get_volume('755ab026-b5f2-4f53-b34a-6d082fb36689')
        connection.attach_volume(instance, volume, '/dev/vdb')

.. only:: shade

    .. literalinclude:: ../samples/shade/block_storage.py
        :language: python
        :start-after: step-5
        :end-before: step-6

Log in to the server to run the following steps.

.. note:: Replace :code:`IP_SERVICES` with the IP address of the
          services instance and USERNAME to the appropriate user name.

Now prepare the empty block device.

::

    $ ssh -i ~/.ssh/id_rsa USERNAME@IP_SERVICES
    # fdisk -l
    # mke2fs /dev/vdb
    # mkdir /mnt/database
    # mount /dev/vdb /mnt/database

.. todo:: Outputs missing, add attaching log from dmesg.

Stop the running MySQL database service and move the database files from
:file:`/var/lib/mysql` to the new volume, which is temporarily mounted at
:file:`/mnt/database`.

::

    # systemctl stop mariadb
    # mv /var/lib/mysql/* /mnt/database

Sync the file systems and mount the block device that contains the database
files to :file:`/var/lib/mysql`.

::

    # sync
    # umount /mnt/database
    # rm -rf /mnt/database
    # echo "/dev/vdb /var/lib/mysql ext4 defaults  1 2" >> /etc/fstab
    # mount /var/lib/mysql

Finally, start the stopped MySQL database service and validate that everything
works as expected.

::

    # systemctl start mariadb
    # mysql -ufaafo -ppassword -h localhost faafo -e 'show tables;'

Extras
~~~~~~

You can detach the volume and reattach it elsewhere, or use the following
steps to delete the volume.

.. warning::
    The following operations are destructive and result in data loss.

To detach and delete a volume:

.. only:: libcloud

    .. code-block:: python

        connection.detach_volume(volume)

    ::

        True

    .. code-block:: python

        connection.destroy_volume(volume)

    .. note:: :code:`detach_volume` and :code:`destroy_volume` take a
              volume object, not a name.

.. only:: shade

    .. literalinclude:: ../samples/shade/block_storage.py
        :language: python
        :start-after: step-6
        :end-before: step-7

.. only:: libcloud

    Other features, such as creating volume snapshots, are useful for backups:

    .. code-block:: python

        snapshot_name = 'test_backup_1'
        connection.create_volume_snapshot('test', name=snapshot_name)

    .. todo:: Do we need a note here to mention that 'test' is the
              volume name and not the volume object?

    For information about these and other calls, see
    `libcloud documentation
    <http://ci.apache.org/projects/libcloud/docs/compute/drivers/openstack.html>`_.

Work with the OpenStack Database service
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Previously, you manually created the database, which is useful for a a single
database that you rarely update. However, the OpenStack :code:`trove`
component provides Database as a Service (DBaaS).

.. note:: This OpenStack Database service is not installed in many
          clouds right now, but if your cloud supports it, it can
          make your life a lot easier when working with databases.

SDKs do not generally support the service yet, but you can use the
'trove' command-line client to work with it instead.

Install the trove command-line client by following this guide:
http://docs.openstack.org/cli-reference/content/install_clients.html

Then, set up necessary variables for your cloud in an :file:`openrc.sh` file
by using this guide:
http://docs.openstack.org/cli-reference/content/cli_openrc.html

Ensure you have an :file:`openrc.sh` file, source it, and validate that
your trove client works: ::

    $ cat openrc.sh
    export OS_USERNAME=your_auth_username
    export OS_PASSWORD=your_auth_password
    export OS_TENANT_NAME=your_project_name
    export OS_AUTH_URL=http://controller:5000/v2.0
    export OS_REGION_NAME=your_region_name

    $ source openrc.sh

    $ trove --version
    1.0.9

For information about supported features and how to work with an existing
database service installation, see these
`slides <http://www.slideshare.net/hastexo/hands-on-trove-database-as-a-service-in-openstack-33588994>`_.

Next steps
~~~~~~~~~~

You should now be fairly confident working with Block Storage volumes. For
information about other calls, see the volume documentation for your SDK or
try one of these tutorial steps:

* :doc:`/orchestration`: to automatically orchestrate the application
* :doc:`/networking`: to learn about more complex networking
* :doc:`/advice`: for advice for developers new to operations
