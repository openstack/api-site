#!/bin/bash -e

mkdir -p publish-docs

tools/build-rst.sh api-quick-start --target api-ref/api-guide/quick-start
