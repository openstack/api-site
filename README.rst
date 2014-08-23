API-Site repository
+++++++++++++++++++

This repository contains documentation for the OpenStack project.

For more details, see the `OpenStack Documentation wiki page
<http://wiki.openstack.org/Documentation>`_.

It includes these pages and PDFs:

 * API Quick Start
 * API Complete Reference (web pages)
 * API Reference PDFs
 * API Guide (in progress)

In addition to these, this repository contains:

 * developer.openstack.org: ``www``

Prerequisites
=============

`Apache Maven <http://maven.apache.org/>`_ must be installed to build the
documentation.

To install Maven 3 for Ubuntu 12.04 and later,and Debian wheezy and later::

    apt-get install maven

On Fedora 20 and later::

    yum install maven

Build and update API docs
=========================

For more details about the Gerrit workflow, see `Gerrit Workflow <https://wiki.openstack.org/wiki/GerritWorkflow>`_.

To build and updates any of the API documents:

#. Open a Terminal window.

#. Change into a directory where you want to clone api-site.

#. Run this command to clone openstack/api-site::

        git clone https://github.com/openstack/api-site

#. CD into the api-site directory.

#. Run these commands to ensure you have the latest changes::

        git remote update
        git checkout master
        git pull origin master

#. To checkout a new branch::

        git checkout -b "*my_branch*"

   Otherwise, to checkout an existing review::

        git review –d change-number /* where change-number is the change number of the review

#. Make your changes.

#. Run this command to build the docs locally::

        mvn clean generate-sources

#. To check in your changes, see `Gerrit Workflow <https://wiki.openstack.org/wiki/GerritWorkflow>`_.

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

Install the python tox package and run ``tox`` from the top-level
directory to use the same tests that are done as part of our Jenkins
gating jobs.

If you like to run individual tests, run:

 * ``tox -e checkniceness`` - to run the niceness tests
 * ``tox -e checksyntax`` - to run syntax checks
 * ``tox -e checkdeletions`` - to check that no deleted files are referenced
 * ``tox -e checkbuild`` - to actually build the manual

tox will use the `openstack-doc-tools package
<https://github.com/openstack/openstack-doc-tools>`_ for execution of
these tests. openstack-doc-tools has a requirement on maven for the
build check.


Contribute
==========

Our community welcomes all people interested in open source cloud
computing, and encourages you to join the `OpenStack Foundation
<http://www.openstack.org/join>`_.

The best way to get involved with the community is to talk with others online
or at a meetup and offer contributions through our processes, the `OpenStack
wiki <http://wiki.openstack.org>`_, blogs, or on IRC at ``#openstack``
on ``irc.freenode.net``.

We welcome all types of contributions, from blueprint designs to documentation
to testing to deployment scripts.

If you would like to contribute to the documents, please see the
`Documentation HowTo <https://wiki.openstack.org/wiki/Documentation/HowTo>`_.

Bugs
====

Bugs should be filed on Launchpad, and not GitHub:

   https://bugs.launchpad.net/openstack-api-site/


Install
=======

See `OpenStack <http://www.openstack.org/>`_ to learn more about the OpenStack project.
