=======================================
Advice for developers new to operations
=======================================

This section introduces some operational concepts and tasks to
developers who have not written cloud applications before.

Monitoring
~~~~~~~~~~

Monitoring is essential for 'scalable' cloud applications. You must
know how many requests are coming in and the impact that these
requests have on various services. You must have enough information to
determine whether to start another worker or API service as you
did in :doc:`/scaling_out`.

.. todo:: explain how to achieve this kind of monitoring. Ceilometer?
          (STOP LAUGHING.)

In addition to this kind of monitoring, you should consider
availability monitoring. Although your application might not care
about a failed worker, it should care about a failed database server.

Use the
`Health Endpoint Monitoring Pattern <https://msdn.microsoft.com/en-us/library/dn589789.aspx>`
to implement functional checks within your application that external
tools can access through exposed endpoints at regular intervals.

Backups
~~~~~~~

Just as you back up information on a non-cloud server, you must back
up non-reproducible information, such as information on a database
server, file server, or in application log files. Just because
something is 'in the cloud' does not mean that the underlying hardware
or systems cannot fail.

OpenStack provides a couple of tools that make it easy to back up
data. If your provider runs OpenStack Object Storage, you can use its
API calls and CLI tools to work with archive files.

You can also use the OpenStack API to create snapshots of running
instances and persistent volumes. For more information, see your SDK
documentation.

.. todo:: Link to appropriate documentation, or better yet, link and
          also include the commands here.

In addition to configuring backups, review your policies about what
you back up and how long to retain each backed up item.

Phoenix servers
~~~~~~~~~~~~~~~

`Phoenix Servers <http://martinfowler.com/bliki/PhoenixServer.html>`_,
named for the mythical bird that is consumed by fire and rises from
the ashes to live again, make it easy to start over with new
instances.

Application developers and operators who use phoenix servers have
access to systems that are built from a known baseline, such as a
specific operating system version, and to tooling that automatically
builds, installs, and configures a system.

If you deploy your application on a regular basis, you can resolve
outages and make security updates without manual intervention. If an
outage occurs, you can provision more resources in another region. If
you must patch security holes, you can provision additional compute
nodes that are built with the updated software. Then, you can
terminate vulnerable nodes and automatically fail-over traffic to the
new instances.

Security
~~~~~~~~

If one application instance is compromised, all instances with the
same image and configuration will likely suffer the same
vulnerability. The safest path is to use configuration management to
rebuild all instances.

Configuration management
~~~~~~~~~~~~~~~~~~~~~~~~

Configuration management tools, such as Ansible, Chef, and Puppet,
enable you to describe exactly what to install and configure on an
instance. Using these descriptions, these tools implement the changes
that are required to get to the desired state.

These tools vastly reduce the effort it takes to work with large
numbers of servers, and also improve the ability to recreate, update,
move, and distribute applications.

Application deployment
~~~~~~~~~~~~~~~~~~~~~~

How do you deploy your application? For example, do you pull the
latest code from a source control repository? Do you make packaged
releases that update infrequently? Do you perform haphazard tests in a
development environment and deploy only after major changes?

One of the latest trends in scalable cloud application deployment is
`continuous integration <http://en.wikipedia.org/wiki/Continuous_integration>`_
and `continuous deployment <http://en.wikipedia.org/wiki/Continuous_delivery>`_
(CI/CD).

CI/CD means that you always test your application and make frequent
deployments to production.

In this tutorial, we have downloaded the latest version of our
application from source and installed it on a standard image. Our
magic installation script also updates the standard image to have the
latest dependencies that you need to run the application.

Another approach is to create a 'gold' image, which pre-installs your
application and its dependencies. A 'gold' image enables faster boot
times and more control over what is on the instance. However, if you
use 'gold' images, you must have a process in place to ensure that
these images do not fall behind on security updates.

Fail fast
~~~~~~~~~

.. todo:: Section needs to be written.
