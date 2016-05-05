.. -*- rst -*-

=======================================
Network IP availability and usage stats
=======================================

List and show the network IP usage stats of all networks and a
specified network. These operations are available in the Mitaka
release (April 2016).


Show Network IP Availability
============================

.. rest_method::  GET /v2.0/network-ip-availabilities/{network_id}

Shows network IP availability details for a network.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml

   - network_id: network_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - used_ips: used_ips
   - subnet_ip_availability: subnet_ip_availability
   - network_id: network_id
   - tenant_id: tenant_id
   - total_ips: total_ips
   - network_ip_availability: network_ip_availability
   - subnet_id: subnet_id
   - subnet_name: subnet_name
   - ip_version: ip_version
   - cidr: cidr
   - network_name: network_name



Response Example
----------------

.. literalinclude:: ../samples/network-ip-availability/network-ip-availability-show.json
   :language: javascript






List Network IP Availability
============================

.. rest_method::  GET /v2.0/network-ip-availabilities

Lists network IP availability of all networks.


Normal response codes: 200
Error response codes:403,401,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - used_ips: used_ips
   - subnet_ip_availability: subnet_ip_availability
   - network_id: network_id
   - tenant_id: tenant_id
   - total_ips: total_ips
   - subnet_id: subnet_id
   - subnet_name: subnet_name
   - ip_version: ip_version
   - cidr: cidr
   - network_name: network_name
   - network_ip_availabilities: network_ip_availabilities



Response Example
----------------

.. literalinclude:: ../samples/network-ip-availability/network-ip-availability-list.json
   :language: javascript





