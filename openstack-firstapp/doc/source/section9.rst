=========================
Section Nine: Going Crazy
=========================

In this section, we will look at further options for expanding the sample application.

Regions and geographic diversity
--------------------------------

.. note:: For more information on multi-site clouds, check out the `Multi-Site chapter <http://docs.openstack.org/arch-design/content/multi_site.html>`_ of the Architecture Design Guide.

OpenStack supports the concepts of 'Regions' - ususally geographicaly separated installations that are
all connected to the one service catalogue. This section explains how to expand the Fractal app to
to use multiple regions for high availability.

.. note:: This section is incomplete. Please help us finish it!

Multiple clouds
---------------

.. note:: For more information on hybrid-clouds, check out the `Hybrid Cloud chapter <http://docs.openstack.org/arch-design/content/hybrid.html>`_ of the Architecture Design Guide

Sometimes, you want to use multiple clouds, such as a private cloud inside your organisation
and a public cloud. This section attempts to do exactly that.

.. note:: This section is incomplete. Please help us finish it!

High Availability
-----------------
Using Pacemaker to look at the API.

.. note:: This section is incomplete. Please help us finish it!

conf.d, etc.d
-------------
Use conf.d and etc.d.

In earlier sections, the Fractal Application uses an install script, with parameters passed in from the metadata API,
in order to bootstrap the cluster. `Etcd <https://github.com/coreos/etcd>`_ is a "a distributed, consistent key value store for shared configuration and service discovery"
that can be used for storing configuration. Updated versions of the Fractal worker 
component could be writted to connect to Etcd, or use `Confd <https://github.com/kelseyhightower/confd>`_ which will
poll for changes from Etcd and write changes to a configuration file on the local filesystem, which the Fractal worker
could use for configuration.

Using Swift instead of a database
---------------------------------

We haven't quite figured out how to do this yet, but the general steps involve changing the fractal upload
code to store metadata with the object in swift, then changing the API code such as "list fractals" to
query swift to retrieve the metadata. If you do this, you should be able to stop using a database.

.. note:: This section is incomplete. Please help us finish it!

Next Steps
----------
Wow, if you've made it through this section, you know more about
working with OpenStack clouds than the authors of this guide.

Perhaps you can `contribute <https://wiki.openstack.org/wiki/Documentation/HowTo>`_?

