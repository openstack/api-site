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

The RST source includes conditional output logic. To invoke
:code:`sphinx-build` with :code:`-t libcloud`::

  tox -e firstapp-libcloud

Only the sections marked :code:`.. only:: libcloud` in the RST are built.

To build the documentation, you must install `Sphinx <http://sphinx-doc.org/>`_
and the
`OpenStack docs.openstack.org Sphinx theme (openstackdocstheme) <https://pypi.python.org/pypi/openstackdocstheme>`_.

When you invoke tox, these dependencies are automatically pulled in from the
top-level :code:`test-requirements.txt`.

You must also install `Graphviz <http://www.graphviz.org/>`_ on your build system.

/samples
~~~~~~~~

The code samples in the guide are located in this directory. The code samples
for each SDK are located in separate subdirectories.

/build-libcloud
~~~~~~~~~~~~~~~

The HTML documentation is built in this directory. This directory is included
in the project :code:`.gitignore`.
