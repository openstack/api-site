========================
Team and repository tags
========================

.. image:: https://governance.openstack.org/tc/badges/api-site.svg
    :target: https://governance.openstack.org/tc/reference/tags/index.html

.. Change things from this point on

API-Site repository
+++++++++++++++++++

This repository contains API documentation for the OpenStack project.

For details, see `OpenStack Documentation Contributor Guide
<https://docs.openstack.org/doc-contrib-guide/index.html>`_,
which includes these pages:

 * API Quick Start
 * API Guide (in progress)

In addition to these documents, this repository contains:

 * Landing page for developer.openstack.org: ``www``

To complete code reviews in this repository, use the standard
OpenStack Gerrit `workflow <https://review.opendev.org>`_.
For details, see `Gerrit Workflow
<https://docs.openstack.org/infra/manual/developers.html#development-workflow>`_.

Prerequisites
=============

To build the documentation locally, you must install Python and
`Python Tox <https://tox.readthedocs.io/en/latest/>`_.

To install Tox for Ubuntu 14.04 or later::

    apt-get install python-tox python-dev libxml2-dev libxslt1-dev

To build all the documentation after installing Python and Tox::

    tox -e docs

To build an individual document, such as the API Guide::

    tox -e api-quick-start

The locally-built output files are found in a ``publish-docs`` directory.

Build and update API docs
=========================

Refer to the `OpenStack Documentation Contributor Guide
<https://docs.openstack.org/doc-contrib-guide/api-guides.html>`_
for more information.

Run tests
=========

To use the same tests that are used as part of our Jenkins gating jobs,
install the Python tox package and run ``tox`` from the top-level directory.

To run individual tests:

 * ``tox -e linters`` - Niceness tests
 * ``tox -e checkbuild`` - Builds all of the documents in this repository

To run these tests, the Tox package uses the
`OpenStack doc tools package
<https://opendev.org/openstack/openstack-doc-tools>`_.

Contribute
==========

Our community welcomes everyone who is interested in open source cloud
computing and encourages you to join the
`OpenStack Foundation <https://www.openstack.org/join>`_.

The best way to get involved with the community is to talk with others online
or at a meetup and offer contributions through our processes, the
`OpenStack wiki <https://wiki.openstack.org>`_, blogs,
or on IRC at ``#openstack`` on ``irc.freenode.net``.

We welcome all types of contributions, from blueprint designs to documentation
to testing to deployment scripts.

To contribute to the documents, see
`OpenStack Documentation Contributor Guide
<https://docs.openstack.org/doc-contrib-guide/>`_.

Bugs
====

File bugs on Launchpad and not through GitHub:

   `Bugs:openstack-api-site <https://bugs.launchpad.net/openstack-api-site/>`_

Install
=======

To learn more about the OpenStack project,
see `OpenStack <https://www.openstack.org/>`_.

Release Notes
=============

Release notes for the project can be found at:
    https://docs.openstack.org/releasenotes/openstack-manuals/
