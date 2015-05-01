========================================
Writing your First OpenStack Application
========================================

This directory contains the "Writing your First OpenStack Application"
tutorial.

The tutorials works with an application that can be found at:
https://github.com/stackforge/faafo

/source
~~~~~~~

The :code:`/source` directory contains a playground for the actual tutorial
documentation. It's reStructuredText (RST), built with Sphinx.

The RST source includes conditional output logic, so specifying::

  tox -e firstapp-libcloud

will invoke :code:`sphinx-build` with :code:`-t libcloud`, meaning sections
marked :code:`.. only:: libcloud` in the RST will be built, while others
won't.

Sphinx and the OpenStack docs.openstack.org Sphinx Theme (openstackdocstheme)
are needed to build the docs.

/samples
~~~~~~~~

The code samples provided in the guide are sourced from files
in this directory. There is a sub-directory for each SDK.
