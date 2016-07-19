#!/usr/bin/env ruby
require 'fog/openstack'
require 'digest/md5'
require 'net/http'
require 'json'

# step-1
auth_username = "your_auth_username"
auth_password = "your_auth_password"
auth_url      = "http://controller:5000"
project_name  = "your_project_name_or_id"

swift = Fog::Storage::OpenStack.new openstack_auth_url:     auth_url + "/v3/auth/tokens",
                                    openstack_domain_id:    "default",
                                    openstack_username:     auth_username,
                                    openstack_api_key:      auth_password,
                                    openstack_project_name: project_name

# step-2
container_name = "fractals"
container      = swift.directories.create key: container_name

p container

# step-3
p swift.directories.all

# step-4
file_path   = "goat.jpg"
object_name = "an amazing goat"
container   = swift.directories.get container_name
object      = container.files.create body: File.read(File.expand_path(file_path)),
                                     key:  object_name

# step-5
p container.files.all

# step-6
p container.files.get object_name

# step-7
puts Digest::MD5.hexdigest(File.read(File.expand_path(file_path)))

# step-8
object.destroy

# step-9
p container.files.all

# step-10
container_name = 'fractals'
container      = swift.directories.get container_name

# step-11
endpoint  = "http://IP_API_1"
uri       = URI("#{endpoint}/v1/fractal")
uri.query = URI.encode_www_form results_per_page: -1
data      = JSON.parse(Net::HTTP.get_response(uri).body)

data["objects"].each do |fractal|
  body   = open("#{endpoint}/fractal/#{fractal["uuid"]}") {|f| f.read}
  object = container.files.create body: body, key: fractal["uuid"]
end

p container.files.all

# step-12
container.files.each do |file|
  file.destroy
end
container.destroy

# step-13
object_name = "backup_goat.jpg"
file_path   = "backup_goat.jpg"
extra = {
  description: "a funny goat",
  created:     "2015-06-02"
}
object  = container.files.create body: File.read(File.expand_path(file_path)),
                                 key:  object_name,
                                 metadata: extra

# step-14
#TBC

# step-15
