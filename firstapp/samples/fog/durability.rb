# step-1
require 'fog'

auth_username = 'your_auth_username'
auth_password = 'your_auth_password'
auth_url = 'http://controller:5000'
project_name = 'your_project_name_or_id'
region_name = 'your_region_name'

swift = Fog::Storage.new({
    :provider            => 'openstack',
    :openstack_auth_url  => auth_url + '/v2.0/tokens',
    :openstack_username  => auth_username,
    :openstack_tenant    => project_name,
    :openstack_api_key   => auth_password,
    :openstack_region   => region_name
})

# step-2
container_name = 'fractals'
container = swift.directories.create :key => container_name

# step-3
swift.directories

# step-4
file_path = 'goat.jpg'
object_name = 'an amazing goat'
container = swift.directories.get container_name
object = container.upload_object(file_path=file_path, object_name=object_name)
object = container.files.create :key => object_name, :body => File.open file_path

# step-5
objects = container.files
puts objects

# step-6
object = container.files.get(object_name)
puts object

# step-7
require 'digest/md5'
file = File.open('goat.jpg', "rb")
contents = file.read
file.close
digest = Digest::MD5.hexdigest(contents)
puts digest


# step-8
object.destroy

# step-9
objects = container.files
puts objects

# step-10
container_name = 'fractals'
container = swift.directories.get container_name

# step-11
require "net/https"
require "uri"
require "json"

endpoint = 'http://IP_API_1'
uri = URI.parse('%s/v1/fractal?results_per_page=-1' % endpoint)
http = Net::HTTP.new(uri.host, uri.port)
request = Net::HTTP::Get.new(uri.request_uri)
response = http.request(request)
data = json.parse(response.body)

for fractal in data['objects']
    request = Net::HTTP::Get.new('%s/fractal/%s' % (endpoint, fractal['uuid']), stream=True)
    response = http.request(request)
    container.files.create :key => fractal['uuid'], :body => response.body
end

for object in container.files:
    puts object

# step-12
for object in container.files:
    object.destroy
container.destroy

# step-13
file_path = 'goat.jpg'
object_name = 'backup_goat.jpg'
metadata = {'description' => 'a funny goat', 'created' => '2015-06-02'}
container.files.creare :key => object_name, :body File.open file_path, :metadata => metadata

# step-14
# XXX TODOZ TBC
chunk_size = 33554432
File.open(file_path) do |chunk|

end

swift.put_object_manifest(container_name, object_name, 'X-Object-Manifest' => container_name + "/" + object_name "/")

# step-15
