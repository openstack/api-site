#!/bin/bash -xe
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.

PUBLISH=$1

if [[ -z "$PUBLISH" ]] ; then
    echo "usage $0 (build|publish)"
    exit 1
fi

mkdir -p publish-docs/html

# Build the www pages so that openstack-doc-test creates a link to
# www/www-index.html.
if [ "$PUBLISH" = "build" ] ; then
    python tools/www-generator.py --source-directory www/ \
        --output-directory publish-docs/html/www/
    rsync -a www/static/ publish-docs/html/www/
    # publish-docs/html/www-index.html is the trigger for openstack-doc-test
    # to include the file.
    mv publish-docs/html/www/www-index.html publish-docs/html/www-index.html
    # Create index page for viewing
    openstack-indexpage publish-docs/html
fi
if [ "$PUBLISH" = "publish" ] ; then
    python tools/www-generator.py --source-directory www/ \
        --output-directory publish-docs/html/
    rsync -a www/static/ publish-docs/html/
    # Don't publish this file
    rm publish-docs/html/www-index.html

    # This marker is needed for infra publishing
    MARKER_TEXT="Project: $ZUUL_PROJECT Ref: $ZUUL_REFNAME Build: $ZUUL_UUID"
    echo $MARKER_TEXT > publish-docs/html/.root-marker

fi
