#!/bin/bash -e

mkdir -p publish-docs

# Publish documents to api-ref for developer.openstack.org
for tag in libcloud shade; do
    tools/build-rst.sh firstapp  \
        --tag ${tag} --target "firstapp-${tag}"
done

# Draft documents
for tag in dotnet fog openstacksdk pkgcloud jclouds gophercloud; do
    tools/build-rst.sh firstapp  \
        --tag ${tag} --target "draft/firstapp-${tag}"
done
