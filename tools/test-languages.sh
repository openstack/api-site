#!/bin/bash

function setup_directory {
    SET_LANG=$1
    shift
    for BOOK_DIR in "$@" ; do
        openstack-generate-docbook -l $SET_LANG -b $BOOK_DIR -r ./
    done
}

function setup_lang {
    SET_LANG=$1
    shift
    echo ""
    echo "Setting up files for $SET_LANG"
    echo "======================="
    mkdir -p generated/$SET_LANG
    cp pom.xml generated/$SET_LANG/pom.xml
}

function test_manuals {
    SET_LANG=$1
    shift
    setup_lang $SET_LANG
    for BOOK in "$@" ; do
        echo "Building $BOOK for language $SET_LANG..."
        setup_directory $SET_LANG $BOOK
        openstack-doc-test --check-build -l $SET_LANG --only-book $BOOK
        RET=$?
        if [ "$RET" -eq "0" ] ; then
            echo "... succeeded"
        else
            echo "... failed"
            BUILD_FAIL=1
        fi
    done
}

function test_all {
    test_manuals 'de' 'api-quick-start'
    test_manuals 'es' 'api-quick-start'
    test_manuals 'fr' 'api-quick-start'
    test_manuals 'ja' 'api-quick-start'
    test_manuals 'ko_KR' 'api-quick-start'
}


BUILD_FAIL=0
test_all

exit $BUILD_FAIL
