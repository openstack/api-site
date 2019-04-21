package main

import (
	"fmt"
	"os"

	"github.com/gophercloud/gophercloud"
	"github.com/gophercloud/gophercloud/openstack"
	"github.com/gophercloud/gophercloud/openstack/blockstorage/v1/volumes"
	"github.com/gophercloud/gophercloud/openstack/compute/v2/extensions/keypairs"
	"github.com/gophercloud/gophercloud/openstack/compute/v2/extensions/secgroups"
	"github.com/gophercloud/gophercloud/openstack/compute/v2/extensions/volumeattach"
	"github.com/gophercloud/gophercloud/openstack/compute/v2/servers"
	"github.com/gophercloud/gophercloud/pagination"
)

func main() {

	// step-1
	authOpts, err := openstack.AuthOptionsFromEnv()
	if err != nil {
		fmt.Println(err)
		return
	}

	provider, err := openstack.AuthenticatedClient(authOpts)
	if err != nil {
		fmt.Println(err)
		return
	}

	var regionName = os.Getenv("OS_REGION_NAME")
	volumeClient, err := openstack.NewBlockStorageV1(provider, gophercloud.EndpointOpts{
		Region: regionName,
	})
	if err != nil {
		fmt.Println(err)
		return
	}

	// step-2
	volumeOpts := volumes.CreateOpts{Size: 1, Name: "test"}
	volume, err := volumes.Create(volumeClient, volumeOpts).Extract()
	if err != nil {
		fmt.Println(err)
		return
	}

	// step-3
	_ = volumes.List(volumeClient, nil).EachPage(func(page pagination.Page) (bool, error) {
		volumeList, _ := volumes.ExtractVolumes(page)
		for _, vol := range volumeList {
			fmt.Println(vol)
		}
		return true, nil
	})

	// step-4
	computeClient, err := openstack.NewComputeV2(provider, gophercloud.EndpointOpts{
		Region: regionName,
		Type:   "computev21",
	})
	if err != nil {
		fmt.Println(err)
		return
	}

	securityGroupName := "database"
	databaseSecurityGroup, _ := secgroups.Create(computeClient, secgroups.CreateOpts{
		Name:        securityGroupName,
		Description: "for database service",
	}).Extract()
	secgroups.CreateRule(computeClient, secgroups.CreateRuleOpts{
		ParentGroupID: databaseSecurityGroup.ID,
		FromPort:      22,
		ToPort:        22,
		IPProtocol:    "TCP",
		CIDR:          "0.0.0.0/0",
	}).Extract()
	secgroups.CreateRule(computeClient, secgroups.CreateRuleOpts{
		ParentGroupID: databaseSecurityGroup.ID,
		FromPort:      3306,
		ToPort:        3306,
		IPProtocol:    "TCP",
		CIDR:          "0.0.0.0/0",
	}).Extract()

	userData := `#!/usr/bin/env bash
		curl -L -s https://opendev.org/openstack/faafo/raw/contrib/install.sh | bash -s -- \
		-i faafo -i messaging -r api -r worker -r demo`

	imageID := "41ba40fd-e801-4639-a842-e3a2e5a2ebdd"
	flavorID := "3"
	networkID := "aba7a6f8-6ec9-4666-8c42-ac2d00707010"

	serverOpts := servers.CreateOpts{
		Name:           "app-database",
		ImageRef:       imageID,
		FlavorRef:      flavorID,
		Networks:       []servers.Network{servers.Network{UUID: networkID}},
		SecurityGroups: []string{securityGroupName},
		UserData:       []byte(userData),
	}

	server, err := servers.Create(computeClient, keypairs.CreateOptsExt{
		CreateOptsBuilder: serverOpts,
		KeyName:           "demokey",
	}).Extract()
	if err != nil {
		fmt.Println(err)
		return
	}
	servers.WaitForStatus(computeClient, server.ID, "ACTIVE", 300)

	// step-5
	volumeAttachOptions := volumeattach.CreateOpts{
		VolumeID: volume.ID,
	}

	volumeAttach, err := volumeattach.Create(computeClient, server.ID, volumeAttachOptions).Extract()
	if err != nil {
		fmt.Println(err)
		return
	}
	volumes.WaitForStatus(volumeClient, volumeAttach.ID, "available", 60)

	// step-6
	err = volumeattach.Delete(computeClient, server.ID, volume.ID).ExtractErr()
	if err != nil {
		fmt.Println(err)
		return
	}
	volumes.WaitForStatus(volumeClient, volume.ID, "available", 60)
	volumes.Delete(volumeClient, volume.ID)
}
