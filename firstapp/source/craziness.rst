===========
Going crazy
===========

This section explores options for expanding the sample application.

Regions and geographic diversity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note:: For more information about multi-site clouds, see the
          `Multi-Site chapter <http://docs.openstack.org/arch-design/multi-site.html>`_
          in the Architecture Design Guide.

OpenStack supports 'regions', which are geographically-separated
installations that are connected to a single service catalog. This
section explains how to expand the Fractal application to use multiple
regions for high availability.

.. note:: This section is incomplete. Please help us finish it!

Multiple clouds
~~~~~~~~~~~~~~~

.. note:: For more information about hybrid clouds, see the `Hybrid
          Cloud chapter
          <http://docs.openstack.org/arch-design/hybrid.html>`_
          in the Architecture Design Guide.

You might want to use multiple clouds, such as a private cloud inside
your organization and a public cloud. This section attempts to do
exactly that.

.. note:: This section is incomplete. Please help us finish it!

High availability
~~~~~~~~~~~~~~~~~

Using Pacemaker to look at the API.

.. note:: This section is incomplete. Please help us finish it!

conf.d, etc.d
~~~~~~~~~~~~~

Use conf.d and etc.d.

In earlier sections, the Fractal application used an installation
script into which the metadata API passed parameters to bootstrap the
cluster. `Etcd <https://github.com/coreos/etcd>`_ is "a distributed,
consistent key-value store for shared configuration and service
discovery" that you can use to store configurations. You can write
updated versions of the Fractal worker component to connect to Etcd or
use `Confd <https://github.com/kelseyhightower/confd>`_ to poll for
changes from Etcd and write changes to a configuration file on the
local file system, which the Fractal worker can use for configuration.

Use Object Storage instead of a database
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We have not quite figured out how to stop using a database, but the
general steps are:

* Change the Fractal upload code to store metadata with the object in
  Object Storage.

* Change the API code, such as "list fractals," to query Object Storage
  to get the metadata.

.. note:: This section is incomplete. Please help us finish it!

Next steps
~~~~~~~~~~

Wow! If you have made it through this section, you know more than the
authors of this guide know about working with OpenStack clouds.

Perhaps you can `contribute <http://docs.openstack.org/contributor-guide/>`_?
