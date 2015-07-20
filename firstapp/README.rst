========================================
Writing Your First OpenStack Application
========================================

This directory contains the "Writing Your First OpenStack Application"
tutorial.

The tutorials work with an application that can be found at
`https://github.com/stackforge/faafo <https://github.com/stackforge/faafo/>`_.

Prerequisites
-------------

To build the documentation, you must install the Graphviz package.

/source
~~~~~~~

The :code:`/source` directory contains the tutorial documentation as
`reStructuredText <http://docutils.sourceforge.net/rst.html>`_ (RST).

To build the documentation, you must install `Sphinx <http://sphinx-doc.org/>`_ and the
`OpenStack docs.openstack.org Sphinx theme (openstackdocstheme) <https://pypi.python.org/pypi/openstackdocstheme/>`_. When
you invoke tox, these dependencies are automatically pulled in from the
top-level :code:`test-requirements.txt`.

You must also install `Graphviz <http://www.graphviz.org/>`_ on your build system.

The RST source includes conditional output logic. The following command
invokes :code:`sphinx-build` with :code:`-t libcloud`::

  tox -e firstapp-libcloud

Only the sections marked :code:`.. only:: libcloud` in the RST are built.

/samples
~~~~~~~~

The code samples in this guide are located in this directory. The code samples
for each SDK are located in separate subdirectories.

/build-libcloud
~~~~~~~~~~~~~~~

The HTML documentation is built in this directory. The :code:`.gitignore` file
for the project specifies this directory.
