===================
OpenStack API Guide
===================

Although you install each OpenStack service separately, the OpenStack
services work together to meet your cloud needs: Identity, Compute,
Images, Block Storage, Networking (neutron), Object Storage, Databases, and
Metering. With the `TryStack <http://www.trystack.org/>`__ OpenStack
installation, these services work together in the background of the
installation.

After you authenticate through Identity, you can use the other OpenStack
APIs to create and manage resources in your OpenStack cloud. You can
launch instances from images and assign metadata to instances through
the Compute API or the **openstack** command-line client.

To begin sending API requests, use one of the following methods:

-  **cURL**

   A command-line tool that lets you send HTTP requests and receive
   responses. See the section called :ref:`openstack_API_quick_guide`.

-  **OpenStack command-line client**

   The OpenStack project provides a command-line client that enables
   you to access APIs through easy-to-use commands. See the section
   called :ref:`client-intro`.

-  **REST clients**

   Both Mozilla and Google provide browser-based graphical interfaces
   for REST. For Firefox, see
   `RESTClient <https://addons.mozilla.org/en-US/firefox/addon/restclient/>`__.
   For Chrome, see
   `rest-client <http://code.google.com/p/rest-client/>`__.

-  **OpenStack Python Software Development Kit (SDK)**

   Use this SDK to write Python automation scripts that create and
   manage resources in your OpenStack cloud. The SDK implements Python
   bindings to the OpenStack API, which enables you to perform
   automation tasks in Python by making calls on Python objects rather
   than making REST calls directly. All OpenStack command-line tools are
   implemented by using the Python SDK. See `OpenStack Python
   SDK <http://docs.openstack.org/user-guide/sdk.html>`__ in the
   *OpenStack End User Guide*.

Learn more
----------

.. toctree::

   api-quick-start


