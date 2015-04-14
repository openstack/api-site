========
Appendix
========

Bootstrapping Your Network
--------------------------

Most cloud providers will provision all of the required network objects necessary to
boot an instance.  An easy way to see if these have been created for you is to access
the Network Topology section of the OpenStack dashboard.

.. figure:: images/network-topology.png
    :width: 920px
    :align: center
    :height: 622px
    :alt: network topology view
    :figclass: align-center

Specify a network during instance build
---------------------------------------

.. todo:: code for creating a networking using code

Requirements of the First App Application For OpenStack
-------------------------------------------------------

To be able to install the First App Application For OpenStack from PyPi you have to install
the following packages:

On openSUSE/SLES:

.. code-block:: shell

    sudo zypper install -y python-devel and python-pip

On Fedora/CentOS/RHEL:

.. code-block:: shell

    sudo yum install -y python-devel and python-pip

On Debian/Ubuntu:

.. code-block:: shell

    sudo apt-get update
    sudo apt-get install -y python-dev and python-pip

To easify this process you can simply run the following command, which will run the commands above, depending on the used distribution.

.. code-block: shell

    curl -s http://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh | bash

