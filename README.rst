========================
Team and repository tags
========================


API-Site repository
+++++++++++++++++++

This repository contains the index page for
https://developer.openstack.org in the ``www`` directory.

To complete code reviews in this repository, use the standard
OpenStack Gerrit `workflow <https://review.opendev.org>`_.
For details, see `Gerrit Workflow
<https://docs.opendev.org/opendev/infra-manual/latest/developers.html#development-workflow>`_.

This repository is in a frozen state, it will be fully retired once a
new home is found for the index page.

Prerequisites
=============

To build the documentation locally, you must install Python and
`Python Tox <https://tox.readthedocs.io/en/latest/>`_.

To install Tox and dependencies for Ubuntu 22.04 or later::

    apt-get install python3-tox python3-dev libxml2-dev libxslt1-dev

To build all the documentation after installing Python and Tox::

    tox -e docs

To build an individual document, such as the API Guide::

    tox -e api-quick-start

The locally-built output files are found in a ``publish-docs`` directory.

Run tests
=========

To use the same tests that are used as part of our Jenkins gating jobs,
install the Python tox package and run ``tox`` from the top-level directory.

To run individual tests:

 * ``tox -e publishdocs`` - Builds all of the documents in this repository,
   this is called from CI jobs.

Contribute
==========

Our community welcomes everyone who is interested in open source cloud
computing and encourages you to join the
`OpenStack Foundation <https://www.openstack.org/join>`_.

The best way to get involved with the community is to talk with others online
or at a meetup and offer contributions through our processes, the
`OpenStack wiki <https://wiki.openstack.org>`_, blogs,
or on IRC at ``#openstack`` on ``irc.oftc.net``.

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
