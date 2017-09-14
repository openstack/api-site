#!/bin/bash -xe

LANGDIR=$1

if [[ -z "$LANGDIR" ]] ; then
    echo "usage $0 language"
    exit 1
fi

# Move all firstapp files for one language into the api-ref directory
# since that directory is used for publishing.

mkdir -p publish-docs/api-ref/$LANGDIR/
mv publish-docs/$LANGDIR/firstapp* publish-docs/api-ref/$LANGDIR/
