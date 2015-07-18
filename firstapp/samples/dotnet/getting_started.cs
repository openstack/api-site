using System;
using System.Collections.Generic;

using net.openstack.Core.Domain;
using net.openstack.Core.Providers;
using net.openstack.Providers.Rackspace;

namespace openstack
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			// step-1
			var username = "your_auth_username";
			var password = "your_auth_password";
			var project_name = "your_project_name";
			var project_id = "your_project_id";
			var auth_url = "http://controller:5000/v2.0";
			var region = "your_region_name";
			var networkid = "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx";

			var identity = new CloudIdentityWithProject () {
				Username = username,
				Password = password,
				ProjectId = new ProjectId(project_id),
				ProjectName = project_name
			};

			var identityProvider = new OpenStackIdentityProvider (
				new Uri (auth_url));

			var conn = new CloudServersProvider (identity, identityProvider);

			// step-2
			var images = conn.ListImages (region: region);
			foreach (var image in images) {
				Console.WriteLine (string.Format(
					"Image Id: {0} - Image Name: {1}",
					image.Id,
					image.Name));
			}

			// step-3
			var flavors = conn.ListFlavors (region: region);
			foreach (var flavor in flavors) {
				Console.WriteLine (string.Format(
					"Flavor Id: {0} - Flavor Name: {1}",
					flavor.Id,
					flavor.Name));
			}

			// step-4
			var image_id = "97f55846-6ea5-4e9d-b437-bda97586bd0c";
			var _image = conn.GetImage(image_id, region:region);
			Console.WriteLine (string.Format(
				"Image Id: {0} - Image Name: {1}",
				_image.Id,
				_image.Name));

			// step-5
			var flavor_id = "42";
			var _flavor = conn.GetFlavor (flavor_id, region: region);
			Console.WriteLine (string.Format(
				"Flavor Id: {0} - Flavor Name: {1}",
				_flavor.Id,
				_flavor.Name));

			// step-6
			var instance_name = "testing";
			var testing_instance = conn.CreateServer (instance_name,
				_image.Id,
				_flavor.Id,
				region: region,
				networks: new List<String> () { networkid });
			Console.WriteLine (string.Format(
				"Instance Id: {0} at {1}",
				testing_instance.Id,
				testing_instance.Links
			));

			// step-7
			var instances = conn.ListServers(region:region);
			foreach (var instance in instances) {
				Console.WriteLine (string.Format(
					"Instance Id: {0} at {1}",
					testing_instance.Id,
					testing_instance.Links));
			}

			// step-8
			conn.DeleteServer(testing_instance.Id, region:region);

			// step-9

			// step-10

			// step-11

			// step-12

			// step-13

			// step-14

			// step-15

			Console.Read ();
		}
	}
}

