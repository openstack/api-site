API-Site repository
+++++++++++++++++++

This repository contains API documentation for the OpenStack project.

For details, see `OpenStack Documentation Contributor Guide
<http://docs.openstack.org/contributor-guide/index.html>`_,
which includes these pages:

 * API Quick Start
 * API Guide (in progress)

In addition to these documents, this repository contains:

 * Landing page for developer.openstack.org: ``www``
 * Writing your first OpenStack application tutorial (in progress): ``firstapp``

The files in the ``api-ref`` directory cannot be changed
because they are moving to project repositories.

To complete code reviews in this repository, use the standard
OpenStack Gerrit `workflow <https://review.openstack.org>`_.
For details, see `Gerrit Workflow
<http://docs.openstack.org/infra/manual/developers.html#development-workflow>`_.

Prerequisites
=============

To build the documentation locally, you must install Python and
`Python Tox <https://tox.readthedocs.org/>`_.

To install Tox for Ubuntu 14.04 or later::

    apt-get install python-tox python-dev libxml2-dev libxslt1-dev

To build all the documentation after installing Python and Tox::

    tox -e docs

To build an individual document, such as the API Guide::

    tox -e api-quick-start

The locally-built output files are found in a ``publish-docs`` directory.

"Writing your First OpenStack Application" tutorial
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To build the "Writing your first OpenStack application" tutorial, you must
install `Graphviz <http://www.graphviz.org/>`_.

To install Graphviz for Ubuntu 12.04 or later or Debian 7 ("wheezy") or later::

    apt-get install graphviz

On Fedora 22 and later::

    dnf install graphviz

On openSUSE::

    zypper install graphviz

On Mac OSX with Homebrew installed::

    brew install graphviz

Build and update API docs
=========================

Refer to the `OpenStack Documentation Contributor Guide
<http://docs.openstack.org/contributor-guide/api-guides.html>`_
for more information.

Run tests
=========

To use the same tests that are used as part of our Jenkins gating jobs,
install the Python tox package and run ``tox`` from the top-level directory.

To run individual tests:

 * ``tox -e checkniceness`` - Niceness tests
 * ``tox -e checkbuild`` - Builds all of the documents in this repository

To run these tests, the Tox package uses the
`OpenStack doc tools package
<https://git.openstack.org/cgit/openstack/openstack-doc-tools>`_.

Contribute
==========

Our community welcomes everyone who is interested in open source cloud
computing and encourages you to join the
`OpenStack Foundation <http://www.openstack.org/join>`_.

The best way to get involved with the community is to talk with others online
or at a meetup and offer contributions through our processes, the
`OpenStack wiki <http://wiki.openstack.org>`_, blogs,
or on IRC at ``#openstack`` on ``irc.freenode.net``.

We welcome all types of contributions, from blueprint designs to documentation
to testing to deployment scripts.

To contribute to the documents, see
`OpenStack Documentation Contributor Guide
<http://docs.openstack.org/contributor-guide/>`_.

Bugs
====

File bugs on Launchpad and not through GitHub:

   https://bugs.launchpad.net/openstack-api-site/

Install
=======

To learn more about the OpenStack project,
see `OpenStack <http://www.openstack.org/>`_.
