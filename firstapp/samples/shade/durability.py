# step-1
from __future__ import print_function
import hashlib
from shade import *

conn = openstack_cloud(cloud='myfavoriteopenstack')

# step-2
container_name = 'fractals'
container = conn.create_container(container_name)
print(container)

# step-3
print(conn.list_containers())

# step-4
file_path = 'goat.jpg'
object_name = 'an amazing goat'
container = conn.get_container(container_name)
object = conn.create_object(container=container_name, name=object_name, filename=file_path)

# step-5
print(conn.list_objects(container_name))

# step-6
object = conn.get_object(container_name, object_name)
print(object)

# step-7
print(hashlib.md5(open('goat.jpg', 'rb').read()).hexdigest())

# step-8
conn.delete_object(container_name, object_name)

# step-9
print(conn.list_objects(container_name))

# step-10
container_name = 'fractals'
print(conn.get_container(container_name))

# step-11
import base64
import cStringIO
import json
import requests

endpoint = 'http://IP_API_1'
params = { 'results_per_page': '-1' }
response = requests.get('%s/v1/fractal' % endpoint, params=params)
data = json.loads(response.text)
for fractal in data['objects']:
    r = requests.get('%s/fractal/%s' % (endpoint, fractal['uuid']), stream=True)
    with open(fractal['uuid'], 'wb') as f:
        for chunk in r.iter_content(chunk_size=1024):
            if chunk:
                f.write(chunk)
    conn.create_object(container=container_name, name=fractal['uuid'])

for object in conn.list_objects(container_name):
    print(object)

# step-12
for object in conn.list_objects(container_name):
    conn.delete_object(container_name, object['name'])
conn.delete_container(container_name)

# step-13
metadata = {'foo': 'bar'}
conn.create_object(container=container_name, name=fractal['uuid'],
    metadata=metadata
)

# step-14
