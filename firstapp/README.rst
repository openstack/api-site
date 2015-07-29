========================================
Writing your first OpenStack application
========================================

This tutorial works with the `First App Application for OpenStack <https://github.com/stackforge/faafo/>`_.

Prerequisites
=============

To build the documentation, install `Python Tox <https://tox.readthedocs.org/>`_.

To install Tox for Ubuntu 14.04 and later::

    apt-get install python-tox python-dev libxml2-dev libxslt1-dev

Structure
=========

/source
~~~~~~~

The :code:`/source` directory contains the tutorial documentation as
`reStructuredText <http://docutils.sourceforge.net/rst.html>`_ (RST). The
documentation is built with `Sphinx <http://sphinx-doc.org/>`_.

The RST source includes conditional output logic, so specifying::

  tox -e firstapp-libcloud

will invoke :code:`sphinx-build` with :code:`-t libcloud`, meaning sections
marked :code:`.. only:: libcloud` in the RST are built, while others
are not built.

To build the documentation, you need Sphinx and the OpenStack
docs.openstack.org Sphinx Theme (openstackdocstheme). When you invoke tox,
these dependencies are automatically pulled in from the top-level :code:`test-requirements.txt`.

/samples
~~~~~~~~

The code samples provided in the guide are sourced from files in this
directory. Each SDK has its own subdirectory.

/build-libcloud
~~~~~~~~~~~~~~~

The HTML documentation is built in this directory. This directory is included
in the project :code:`.gitignore`.
