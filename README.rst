API-Site repository
+++++++++++++++++++

This repository contains documentation for the OpenStack project.

For details, see the
`OpenStack Documentation wiki page <http://wiki.openstack.org/Documentation>`_,
which includes these pages and PDFs:

 * API Quick Start
 * API Complete Reference (web pages)
 * API Reference PDFs
 * API Guide (in progress)

In addition to these documents, this repository contains:

 * developer.openstack.org: ``www``
 * Writing your first OpenStack application tutorial (in progress): ``firstapp``

Prerequisites
=============

To build the documentation, you must install `Apache Maven <http://maven.apache.org/>`_.

To install Maven 3 for Ubuntu 12.04 or later or Debian 7 ("wheezy") or later::

    apt-get install maven

On Fedora 20 or later::

    yum install maven

To run tests, you must install `Python Tox <https://tox.readthedocs.org/>`_.

To install Tox for Ubuntu 14.04 or later::

    apt-get install python-tox python-dev libxml2-dev libxslt1-dev

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

To complete code reviews in this repository, use the standard OpenStack Gerrit
`workflow <https://review.openstack.org>`_ . For details, see
`Gerrit Workflow <http://docs.openstack.org/infra/manual/developers.html#development-workflow>`_.

To build and update the API documents:

#. Open a Terminal window.

#. Change into a directory where you want to clone api-site.

#. Run this command to clone openstack/api-site::

        git clone https://git.openstack.org/openstack/api-site

#. CD into the api-site directory.

#. Run these commands to ensure that you have the latest changes::

        git remote update
        git checkout master
        git pull origin master

#. To check out a new branch::

        git checkout -b "*my_branch*"

   Otherwise, to check out an existing review::

        git review -d change-number /* where change-number is the change number of the review

#. Make your changes.

#. Run this command to build the docs locally::

        mvn clean generate-sources

#. To check in your changes, see
`Gerrit Workflow <http://docs.openstack.org/infra/manual/developers.html#development-workflow>`_.

- The root of the generated HTML (API site) documentation is::

        api-site/api-ref/target/docbkx/html/api-ref.html

- The root of the generated API guide (in progress) is::

        api-site/api-guide/target/docbkx/webhelp/api-guide/index.html

- The generated PDFs for the API pages are at::

        api-site/api-ref-guides/target/docbkx/pdf/*.pdf

- The root of the API quick start is at::

        api-site/api-quick-start/target/docbkx/webhelp/api-quick-start-onepager-external/api-quick-start-onepager.pdf


Run tests
=========

To use the same tests that are used as part of our Jenkins gating jobs,
install the Python tox package and run ``tox`` from the top-level directory.

To run individual tests:

 * ``tox -e checkniceness`` - Niceness tests
 * ``tox -e checksyntax`` - Syntax checks
 * ``tox -e checkdeletions`` - Verifies that no deleted files are referenced
 * ``tox -e checkbuild`` - Builds the manual

To run these tests, the Tox package uses the
`OpenStack doc tools package <https://git.openstack.org/cgit/openstack/openstack-doc-tools>`_.

The OpenStack doc tools require Maven for the build check.


Contribute
==========

Our community welcomes everyone who is interested in open source cloud
computing and encourages you to join the `OpenStack Foundation <http://www.openstack.org/join>`_.

The best way to get involved with the community is to talk with others online
or at a meetup and offer contributions through our processes, the
`OpenStack wiki <http://wiki.openstack.org>`_, blogs, or on IRC at ``#openstack`` on
``irc.freenode.net``.

We welcome all types of contributions, from blueprint designs to documentation
to testing to deployment scripts.

To contribute to the documents, see
`OpenStack Documentation Contributor Guide <http://docs.openstack.org/contributor-guide/>`_.

Bugs
====

File bugs on Launchpad and not through GitHub:

   https://bugs.launchpad.net/openstack-api-site/


Install
=======

To learn more about the OpenStack project, see `OpenStack <http://www.openstack.org/>`_.
