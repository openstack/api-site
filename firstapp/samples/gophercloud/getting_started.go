package main

import (
  "fmt"
  "io/ioutil"

  "github.com/rackspace/gophercloud"
  "github.com/rackspace/gophercloud/openstack"
  "github.com/rackspace/gophercloud/openstack/compute/v2/flavors"
  "github.com/rackspace/gophercloud/openstack/compute/v2/images"
  "github.com/rackspace/gophercloud/openstack/compute/v2/servers"
  "github.com/rackspace/gophercloud/openstack/compute/v2/extensions/floatingip"
  "github.com/rackspace/gophercloud/openstack/compute/v2/extensions/keypairs"
  "github.com/rackspace/gophercloud/openstack/compute/v2/extensions/secgroups"
  "github.com/rackspace/gophercloud/openstack/networking/v2/networks"
  "github.com/rackspace/gophercloud/openstack/networking/v2/extensions/external"
)

func main() {
  // step-1
  var authUsername string = "your_auth_username"
  var authPassword string = "your_auth_password"
  var authUrl string = "http://controller:5000"
  var projectName string = "your_project_id"
  var regionName string = "your_region_name"

  authOpts := gophercloud.AuthOptions{
    IdentityEndpoint: authUrl,
    Username: authUsername,
    Password: authPassword,
    TenantID: projectName,
  }
  provider, _ := openstack.AuthenticatedClient(authOpts)
  client, _ := openstack.NewComputeV2(provider, gophercloud.EndpointOpts{
    Region: regionName,
  })

  // step-2
  pager := images.ListDetail(client, images.ListOpts{})
  page, _ := pager.AllPages()
  imageList, _ := images.ExtractImages(page)
  fmt.Println(imageList)

  // step-3
  pager = flavors.ListDetail(client, flavors.ListOpts{})
  page, _ = pager.AllPages()
  flavorList, _ := flavors.ExtractFlavors(page)
  fmt.Println(flavorList)

  // step-4
  imageID := "74e6d1ec-9a08-444c-8518-4f232446386d"
  image, _ := images.Get(client, imageID).Extract()
  fmt.Println(image)

  // step-5
  flavorID := "1"
  flavor, _ := flavors.Get(client, flavorID).Extract()
  fmt.Println(flavor)

  // step-6
  instanceName := "testing"
  testingInstance, _ := servers.Create(client, servers.CreateOpts{
    Name: instanceName,
    ImageRef: imageID,
    FlavorRef: flavorID,
  }).Extract()
  fmt.Println(testingInstance)

  // step-7
  pager = servers.List(client, servers.ListOpts{})
  page, _ = pager.AllPages()
  serverList, _ := servers.ExtractServers(page)
  fmt.Println(serverList)

  // step-8
  servers.Delete(client, testingInstance.ID)

  // step-9
  fmt.Println("Checking for existing SSH key pair...")
  keyPairName := "demokey"
  pubKeyFile := "~/.ssh/id_rsa.pub"
  keyPairExists := false

  pager = keypairs.List(client)
  page, _ = pager.AllPages()
  keypairList, _ := keypairs.ExtractKeyPairs(page)
  for _, k := range keypairList {
    if k.Name == keyPairName {
      keyPairExists = true
      break
    }
  }

  if keyPairExists {
    fmt.Println("Keypair " + keyPairName + " already exists. Skipping import.")
  } else {
    fmt.Println("adding keypair...")
    bs, _ := ioutil.ReadFile(pubKeyFile)
    keypairs.Create(client, keypairs.CreateOpts{
      Name: keyPairName,
      PublicKey: string(bs),
    }).Extract()
  }

  pager = keypairs.List(client)
  page, _ = pager.AllPages()
  keypairList, _ = keypairs.ExtractKeyPairs(page)
  fmt.Println(keypairList)

  // step-10
  fmt.Println("Checking for existing security group...")
  var allInOneSecurityGroup secgroups.SecurityGroup
  securityGroupName := "all-in-one"
  securityGroupExists := false

  pager = secgroups.List(client)
  page, _ = pager.AllPages()
  secgroupList, _ := secgroups.ExtractSecurityGroups(page)
  for _, secGroup := range secgroupList {
    if secGroup.Name == securityGroupName {
      allInOneSecurityGroup = secGroup
      securityGroupExists = true
      break
    }
  }

  if securityGroupExists {
    fmt.Println("Security Group " + allInOneSecurityGroup.Name + " already exists. Skipping creation.")
  } else {
    allInOneSecurityGroup, _ := secgroups.Create(client, secgroups.CreateOpts{
      Name: securityGroupName,
      Description: "network access for all-in-one application.",
    }).Extract()
    secgroups.CreateRule(client, secgroups.CreateRuleOpts{
      ParentGroupID: allInOneSecurityGroup.ID,
      FromPort: 80,
      ToPort: 80,
      IPProtocol: "TCP",
      CIDR: "0.0.0.0/0",
    }).Extract()
    secgroups.CreateRule(client, secgroups.CreateRuleOpts{
      ParentGroupID: allInOneSecurityGroup.ID,
      FromPort: 22,
      ToPort: 22,
      IPProtocol: "TCP",
      CIDR: "0.0.0.0/0",
    }).Extract()
  }

  pager = secgroups.List(client)
  page, _ = pager.AllPages()
  secgroupList, _ = secgroups.ExtractSecurityGroups(page)
  fmt.Println(secgroupList)

  // step-11
  userData := `#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
    -i faafo -i messaging -r api -r worker -r demo
`

  // step-12
  fmt.Println("Checking for existing instance...")
  instanceName = "all-in-one"
  instanceExists := false

  pager = servers.List(client, servers.ListOpts{})
  page, _ = pager.AllPages()
  serverList, _ = servers.ExtractServers(page)
  for _, s := range serverList {
    if s.Name == instanceName {
      testingInstance = &s
      instanceExists = true
      break
    }
  }

  if instanceExists {
    fmt.Println("Instance " + testingInstance.Name + " already exists. Skipping creation.")
  } else {
    opts := servers.CreateOpts{
      Name: instanceName,
      ImageRef: image.ID,
      FlavorRef: flavor.ID,
      SecurityGroups: []string{securityGroupName},
      UserData: []byte(userData),
    }
    testingInstance, _ = servers.Create(client, keypairs.CreateOptsExt{
      CreateOptsBuilder: opts,
      KeyName: keyPairName,
    }).Extract()
  }
  servers.WaitForStatus(client, testingInstance.ID, "ACTIVE", 300)

  pager = servers.List(client, servers.ListOpts{})
  page, _ = pager.AllPages()
  serverList, _ = servers.ExtractServers(page)
  fmt.Println(serverList)

  // step-13
  var privateIP string
  for t, addrs := range testingInstance.Addresses {
    if t != "private"  || len(privateIP) != 0 {
      continue
    }
    addrs, ok := addrs.([]interface{})
    if !ok {
      continue
    }
    for _, addr := range addrs {
      a, ok := addr.(map[string]interface{})
      if !ok || a["version"].(float64) != 4 {
        continue
      }
      ip, ok := a["addr"].(string)
      if ok && len(ip) != 0 {
        privateIP = ip
        fmt.Println("Private IP found: " + privateIP)
        break
      }
    }
  }

  // step-14
  var publicIP string
  for t, addrs := range testingInstance.Addresses {
    if t != "public"  || len(publicIP) != 0 {
      continue
    }
    addrs, ok := addrs.([]interface{})
    if !ok {
      continue
    }
    for _, addr := range addrs {
      a, ok := addr.(map[string]interface{})
      if !ok || a["version"].(float64) != 4 {
        continue
      }
      ip, ok := a["addr"].(string)
      if ok && len(ip) != 0 {
        publicIP = ip
        fmt.Println("Public IP found: " + publicIP)
        break
      }
    }
  }

  // step-15
  fmt.Println("Checking for unused Floating IP...")
  var unusedFloatingIP string
  pager = floatingip.List(client)
  page, _ = pager.AllPages()
  floatingIPList, _ := floatingip.ExtractFloatingIPs(page)
  for _, ip := range floatingIPList {
    if ip.InstanceID == "" {
      unusedFloatingIP = ip.IP
      break
    }
  }

  networkClient, _ := openstack.NewNetworkV2(provider, gophercloud.EndpointOpts{
    Region: regionName,
  })

  pager = networks.List(networkClient, networks.ListOpts{})
  page, _ = pager.AllPages()
  poolList, _ := external.ExtractList(page)
  for _, pool := range poolList {
    if len(unusedFloatingIP) != 0 || !pool.External {
      continue
    }
    fmt.Println("Allocating new Floating IP from pool: " + pool.Name)
    f, _ := floatingip.Create(client, floatingip.CreateOpts{Pool: pool.Name}).Extract()
    unusedFloatingIP = f.IP
  }

  // step-16
  if len(publicIP) != 0 {
    fmt.Println("Instance " + testingInstance.Name + " already has a public ip. Skipping attachment.")
  } else {
    floatingip.Associate(client, testingInstance.ID, unusedFloatingIP)
  }

  // step-17
  var actualIPAddress string
  if len(publicIP) != 0 {
    actualIPAddress = publicIP
  } else if len(unusedFloatingIP) != 0 {
    actualIPAddress = unusedFloatingIP
  } else {
    actualIPAddress = privateIP
  }

  fmt.Println("The Fractals app will be deployed to http://" + actualIPAddress)
}
