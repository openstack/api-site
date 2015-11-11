#!/bin/bash -e

mkdir -p publish-docs

# Publish documents to api-ref for developer.openstack.org
for tag in libcloud; do
    tools/build-rst.sh firstapp  \
        --tag ${tag} --target "api-ref/firstapp-${tag}"
done

# Draft documents
for tag in dotnet fog openstacksdk pkgcloud shade; do
    tools/build-rst.sh firstapp  \
        --tag ${tag} --target "api-ref/draft/firstapp-${tag}"
done
