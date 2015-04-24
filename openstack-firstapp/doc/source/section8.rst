=======================================
Advice for developers new to operations
=======================================

In this section, we will introduce some operational concepts and tasks
which may be new to developers who have not written cloud applications
before.

Monitoring
~~~~~~~~~~

Monitoring is essential for cloud applications, especially if the
application is to be 'scalable'. You must know how many requests are
coming in, and what impact that has on the various services -- in
other words, enough information to determine whether you should start
another worker or API service as we did in :doc:`/section3`.

.. todo:: explain how to achieve this kind of monitoring.  Ceilometer?
          (STOP LAUGHING.)

Aside from this kind of monitoring, you should consider availability
monitoring.  Does your application care about a worker going down?
Maybe not. Does it care about a failed database server? Probably yes.

One great pattern to add this to your application is the `Health
Endpoint Monitoring Pattern
<https://msdn.microsoft.com/en-us/library/dn589789.aspx>`, where a
special API endpoint is introduced to your application for a basic
health check.

Backups
~~~~~~~

Where instances store information that is not reproducable (such as a
database server, a file server, or even log files for an application),
it is important to back up this information as you would a normal
non-cloud server. It sounds simple, but just because it is 'in the
cloud' does not mean it has any additional robustness or resilience
when it comes to failure of the underlying hardware or systems.

OpenStack provides a couple of tools that make it easier to perform
backups. If your provider runs OpenStack Object Storage, this is
normally extremely robust and has several handy API calls and CLI
tools for working with archive files.

It is also possible to create snapshots of running instances and persistent
volumes using the OpenStack API. Refer to the documentation of your SDK for
more.

.. todo:: Link to appropriate documentation, or better yet, link and
          also include the commands here.

While the technical action to perform backups can be straightforward,
you should also think about your policies regarding what is backed up
and how long each item should be retained.

Phoenix Servers
~~~~~~~~~~~~~~~

Application developers and operators who employ
`Phoenix Servers <http://martinfowler.com/bliki/PhoenixServer.html>`_
have built systems that start from a known baseline (sometimes just a specific
version of an operating system) and have built tooling that will automatically
build, install, and configure a system with no manual intervention.

Phoenix Servers, named for the mythological bird that would live its life,
be consumed by fire, then rise from the ashes to live again, make it possible
to easily "start over" with new instances.

If your application is automatically deployed on a regular basis,
resolving outages and security updates are not special operations that
require manual intervention.  If you suffer an outage, provision more
resources in another region. If you have to patch security holes,
provision more compute nodes that will be built with the
updated/patched software, then terminate vulnerable nodes, with
traffic automatically failing over to the new instances.

Security
~~~~~~~~

Security-wise, one thing to keep in mind is that if one instance of an
application is compromised, all instances with the same image and
configuration are likely to suffer the same vulnerability. In this
case, it is safer to rebuild all of your instances (a task made easier
by configuration management - see below).

Configuration management
~~~~~~~~~~~~~~~~~~~~~~~~

Tools such as Ansible, Chef, and Puppet allow you to describe exactly
what should be installed on an instance and how it should be
configured. Using these descriptions, the tool implements any changes
required to get to the desired state.

These tools vastly reduce the amount of effort it takes to work with
large numbers of servers, and also improves the ability to recreate,
update, move, or distribute applications.

Application deployment
~~~~~~~~~~~~~~~~~~~~~~

Related to configuration management is the question of how you deploy
your application.

For example, do you:

* pull the latest code from a source control repository?
* make packaged releases that update infrequently?
* big-bang test in a development environment and deploy only after
  major changes?

One of the latest trends in deploying scalable cloud applications is
`continuous integration
<http://en.wikipedia.org/wiki/Continuous_integration>`_ / `continuous
deployment <http://en.wikipedia.org/wiki/Continuous_delivery>`_
(CI/CD).  Working in a CI/CD fashion means you are always testing your
application and making frequent deployments to production.

In this tutorial, we have downloaded the latest version of our
application from source and installed it on a standard image. Our
magic install script also updates the standard image to have the
latest dependencies we need to run the application.

Another approach to this is to create a 'gold' image - one that has your
application and dependencies pre-installed. This means faster boot times and
a higher degree of control over what is on the instance, however a process is
needed to ensure that 'gold' images do not fall behind on security updates.

Fail fast
~~~~~~~~~

.. todo:: Section needs to be written.
