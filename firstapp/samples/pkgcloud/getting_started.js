// step-1

auth_username = 'your_auth_username';
auth_password = 'your_auth_password';
auth_url = 'http://controller:5000';
project_name = 'your_project_name_or_id';
region_name = 'your_region_name';


var conn = require('pkgcloud').compute.createClient({
    provider: 'openstack',
    username: auth_username,
    password: auth_password,
    authUrl:auth_url,
    region: region_name
});


// step-2
conn.getImages(function(err, images) {
    for (i =0; i<images.length; i++) {
        console.log("id: " + images[i].id);
        console.log("name: " + images[i].name);
        console.log("created: " + images[i].created);
        console.log("updated: " + images[i].updated);
        console.log("status: " + images[i].status + "\n");
}});


// step-3
conn.getFlavors(function(err, flavors) {
    for (i=0; i<flavors.length; i++) {
        console.log("id: " + flavors[i].id);
        console.log("name: " + flavors[i].name);
        console.log("ram: " + flavors[i].ram);
        console.log("disk: " + flavors[i].disk);
        console.log("vcpus: " + flavors[i].vcpus + "\n");
}});


// step-4
image_id = '2cccbea0-cea9-4f86-a3ed-065c652adda5';
conn.getImage(image_id, function(err, image) {
    console.log("id: " + image.id);
    console.log("name: " + image.name);
    console.log("created: " + image.created);
    console.log("updated: " + image.updated);
    console.log("status: " + image.status + "\n");
});


// step-5
flavor_id = '3';
conn.getFlavor(flavor_id, function(err, flavor) {
        console.log("id: " + flavor.id);
        console.log("name: " + flavor.name);
        console.log("ram: " + flavor.ram);
        console.log("disk: " + flavor.disk);
        console.log("vcpus: " + flavor.vcpus + "\n");
});


// step-6
instance_name = 'testing';
conn.createServer({
  name: instance_name,
  flavor: flavor_id,
  image: image_id
}, function(err, server) {
    console.log(server.id)
});


// step-7
conn.getServers(console.log);
// TODO - make a decision about printing this nicely or not

// step-8
test_instance_id = '0d7968dc-4bf4-4e01-b822-43c9c1080d77';
conn.destroyServer(test_instance_id, console.log);
// TODO - make a decision about printing this nicely or not

// step-9
console.log('Checking for existing SSH key pair...');
keypair_name = 'demokey';
pub_key_file = '/home/user/.ssh/id_rsa.pub';
pub_key_string = '';
keypair_exists = false;
conn.listKeys(function (err, keys) {
    for (i=0; i<keys.length; i++){
        if (keys[i].keypair.name == keypair_name) {
            keypair_exists = true;
}}});


if (keypair_exists) {
    console.log('Keypair already exists.  Skipping import.');
} else {
    console.log('adding keypair...');
    fs = require('fs');
    fs.readFile(pub_key_file, 'utf8', function (err, data) {
      pub_key_string = data;
    });
    conn.addKey({name: keypair_name, public_key:pub_key_string}, console.log);
}

conn.listKeys(function (err, keys) {
    for (i=0; i<keys.length; i++){
        console.log(keys[i].keypair.name)
        console.log(keys[i].keypair.fingerprint)
}});

// step-10
security_group_name = 'all-in-one';
security_group_exists = false;
all_in_one_security_group = false;
conn.listGroups(function (err, groups) {
    for (i=0; i<groups.length; i++){
        if (groups[i].name == security_group_name) {
            security_group_exists = true;
}}});

if (security_group_exists) {
    console.log('Security Group already exists.  Skipping creation.');
} else {
    conn.addGroup({ name: 'all-in-one',
                    description: 'network access for all-in-one application.'
                  }, function (err, group) {
    all_in_one_security_group = group.id;
    conn.addRule({ groupId: group.id,
                   ipProtocol: 'TCP',
                   fromPort: 80,
                   toPort: 80}, console.log);
    conn.addRule({ groupId: group.id,
                   ipProtocol: 'TCP',
                   fromPort: 22,
                   toPort: 22}, console.log);
   });
};

// step-11
userdata = "#!/usr/bin/env bash\n" +
    "curl -L -s https://git.openstack.org/cgit/stackforge/faafo/plain/contrib/install.sh" +
    " | bash -s -- -i faafo -i messaging -r api -r worker -r demo";
userdata = new Buffer(userdata).toString('base64')

// step-12
instance_name = 'all-in-one'
conn.createServer({ name: instance_name,
                    image: image_id,
                    flavor: flavor_id,
                    keyname: keypair_name,
                    cloudConfig: userdata,
                    securityGroups: all_in_one_security_group},
                    function(err, server) {
                        server.setWait({ status: server.STATUS.running }, 5000, console.log)
                    });

// step-13
console.log('Checking for unused Floating IP...')
unused_floating_ips = []
conn.getFloatingIps(function (err, ips) {
    console.log(ips)
    for (i=0; i<ips.length; i++){
        if (ips[i].node_id) {
            unused_floating_ips = ips[i];
            break;
}}});


if (!unused_floating_ip) {
    conn.allocateNewFloatingIp(function (err, ip) {
    unused_floating_ip = ip.ip;
})};

console.log(unused_floating_ip);

// step-14
conn.addFloatingIp(testing_instance, unused_floating_ip, console.log)

// step-15
console.log('The Fractals app will be deployed to http://%s' % unused_floating_ip.ip_address)
