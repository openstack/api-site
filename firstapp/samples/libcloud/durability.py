# step-1
from __future__ import print_function
from libcloud.storage.types import Provider
from libcloud.storage.providers import get_driver

auth_username = 'your_auth_username'
auth_password = 'your_auth_password'
auth_url = 'http://controller:5000'
project_name = 'your_project_name_or_id'
region_name = 'your_region_name'

provider = get_driver(Provider.OPENSTACK_SWIFT)
swift = provider(auth_username,
                 auth_password,
                 ex_force_auth_url=auth_url,
                 ex_force_auth_version='2.0_password',
                 ex_tenant_name=project_name,
                 ex_force_service_region=region_name)

# step-2
container_name = 'fractals'
container = swift.create_container(container_name=container_name)
print(container)

# step-3
print(swift.list_containers())

# step-4
file_path = 'goat.jpg'
object_name = 'an amazing goat'
container = swift.get_container(container_name=container_name)
object = container.upload_object(file_path=file_path, object_name=object_name)

# step-5
objects = container.list_objects()
print(objects)

# step-6
object = swift.get_object(container_name, object_name)
print(object)

# step-7
import hashlib
print(hashlib.md5(open('goat.jpg', 'rb').read()).hexdigest())

# step-8
swift.delete_object(object)

# step-9
objects = container.list_objects()
print(objects)

# step-10
container_name = 'fractals'
container = swift.get_container(container_name)

# step-11
import json

import requests

endpoint = 'http://IP_API_1'
params = { 'results_per_page': '-1' }
response = requests.get('%s/v1/fractal' % endpoint, params=params)
data = json.loads(response.text)
for fractal in data['objects']:
    response = requests.get('%s/fractal/%s' % (endpoint, fractal['uuid']), stream=True)
    container.upload_object_via_stream(response.iter_content(), object_name=fractal['uuid'])

for object in container.list_objects():
    print(object)

# step-12
for object in container.list_objects():
    container.delete_object(object)
swift.delete_container(container)

# step-13
file_path = 'goat.jpg'
object_name = 'backup_goat.jpg'
extra = {'meta_data': {'description': 'a funny goat', 'created': '2015-06-02'}}
with open('goat.jpg', 'rb') as iterator:
    object = swift.upload_object_via_stream(iterator=iterator,
                                            container=container,
                                            object_name=object_name,
                                            extra=extra)

# step-14
swift.ex_multipart_upload_object(file_path, container, object_name,
                                 chunk_size=33554432)

# step-15
