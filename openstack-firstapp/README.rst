========================================
Writing your First OpenStack Application
========================================

This repo contains the "Writing your First OpenStack Application"
tutorial.

The tutorials works with an application that can be found at:
https://github.com/stackforge/faafo

/bin
~~~~

This document was initially written in 'sprint' style.
/bin contains some useful scripts for the sprint, such as
pads2files which faciliates the creation of files from
an etherpad server using its API.

/doc
~~~~

/doc contains a playground for the actual tutorial documentation

It's RST, built with sphinx.

The RST source includes conditional output logic, so specifying::

  tox -e libcloud

will invoke sphinx-build with -t libcloud, meaning sections
marked .. only:: libcloud in the RST will be built, while others
won't.


sphinx and openstackdoctheme are needed to build the docs


/samples
~~~~~~~~

The code samples provided in the guide are sourced from files
in this directory. There is a sub-directory for each SDK.
