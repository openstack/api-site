package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"os"

	"github.com/gophercloud/gophercloud"
	"github.com/gophercloud/gophercloud/openstack"
	"github.com/gophercloud/gophercloud/openstack/objectstorage/v1/containers"
	"github.com/gophercloud/gophercloud/openstack/objectstorage/v1/objects"
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
	objectClient, err := openstack.NewObjectStorageV1(provider, gophercloud.EndpointOpts{
		Region: regionName,
	})
	if err != nil {
		fmt.Println(err)
		return
	}

	// step-2
	containerName := "fractals"
	containers.Create(objectClient, containerName, nil)

	// step-3
	containers.List(objectClient, &containers.ListOpts{}).EachPage(func(page pagination.Page) (bool, error) {
		containerList, _ := containers.ExtractNames(page)
		for _, name := range containerList {
			fmt.Printf("Container name [%s] \n", name)
		}
		return true, nil
	})

	// step-4
	filePath := "goat.jpg"
	objectName := "an amazing goat"

	f, _ := os.Open(filePath)
	defer f.Close()
	reader := bufio.NewReader(f)

	options := objects.CreateOpts{
		Content: reader,
	}

	objects.Create(objectClient, containerName, objectName, options)

	// step-5
	objects.List(objectClient, containerName, &objects.ListOpts{}).EachPage(func(page pagination.Page) (bool, error) {
		objectList, _ := objects.ExtractNames(page)
		for _, name := range objectList {
			fmt.Printf("Object name [%s] \n", name)
		}
		return true, nil
	})

	// step-6

	// step-7

	// step-8
	objects.Delete(objectClient, containerName, objectName, nil)

	// step-9

	// step-10
	containerName = "fractals"
	containers.Create(objectClient, containerName, nil)

	// step-11
	endpoint := "http://IP_API_1"

	resp, _ := http.Get(endpoint + "/v1/fractal")
	defer resp.Body.Close()
	body, _ := ioutil.ReadAll(resp.Body)

	type Fractal struct {
		UUID string `json:"uuid"`
	}

	type Data struct {
		Results    int       `json:"num_results"`
		Objects    []Fractal `json:"objects"`
		Page       int       `json:"page"`
		TotalPages int       `json:"total_pages"`
	}

	var data Data
	json.Unmarshal([]byte(body), &data)

	for _, fractal := range data.Objects {
		r, _ := http.Get(endpoint + "/fractal/" + fractal.UUID)
		defer r.Body.Close()
		image := fractal.UUID + ".png"
		out, _ := os.Create(image)
		defer out.Close()
		io.Copy(out, r.Body)

		f, _ := os.Open(image)
		defer f.Close()
		reader := bufio.NewReader(f)

		options := objects.CreateOpts{
			Content: reader,
		}

		objectName = fractal.UUID
		fmt.Printf("Uploading object [%s] in container [%s]... \n", objectName, containerName)
		objects.Create(objectClient, containerName, objectName, options)
	}

	objects.List(objectClient, containerName, &objects.ListOpts{}).EachPage(func(page pagination.Page) (bool, error) {
		objectList, _ := objects.ExtractNames(page)
		for _, name := range objectList {
			fmt.Printf("Object [%s] in container [%s] \n", name, containerName)
		}
		return true, nil
	})

	// step-12
	objects.List(objectClient, containerName, &objects.ListOpts{}).EachPage(func(page pagination.Page) (bool, error) {
		objectList, _ := objects.ExtractNames(page)
		for _, name := range objectList {
			fmt.Printf("Deleting object [%s] in container [%s]... \n", name, containerName)
			objects.Delete(objectClient, containerName, name, nil)
		}
		return true, nil
	})
	fmt.Printf("Deleting container [%s] \n", containerName)
	containers.Delete(objectClient, containerName)

	// step-13
	objects.Update(objectClient, containerName, objectName, &objects.UpdateOpts{Metadata: map[string]string{"foo": "bar"}})

	// step-14
}
