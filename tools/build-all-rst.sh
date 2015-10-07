#!/bin/bash -e

mkdir -p publish-docs

tools/build-firstapp-rst.sh
tools/build-api-start.sh
