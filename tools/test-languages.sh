#!/bin/bash

function setup_directory {
    SET_LANG=$1
    shift
    for BOOK_DIR in "$@" ; do
        echo "   $BOOK_DIR"
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

function test_api_quick_start {
    SET_LANG=$1
    shift

    case "$PURPOSE" in
        test)
            setup_directory $SET_LANG 'api-quick-start'
            openstack-doc-test -v --check-build -l $SET_LANG \
                --only-book api-quick-start
            RET=$?
            ;;
        publish)
            setup_directory $SET_LANG 'api-quick-start'
            openstack-doc-test -v --publish --check-build -l $SET_LANG \
                --only-book api-quick-start
            RET=$?
            ;;
    esac
    if [ "$RET" -eq "0" ] ; then
        echo "... succeeded"
    else
        echo "... failed"
        BUILD_FAIL=1
    fi
}

function test_ca {
    setup_lang 'ca'
    test_api_quick_start 'ca'
}

function test_de {
    setup_lang 'de'
    test_api_quick_start 'de'
}

function test_es {
    setup_lang 'es'
    test_api_quick_start 'es'
}

function test_fr {
    setup_lang 'fr'
    test_api_quick_start 'fr'
}

function test_ja {
    setup_lang 'ja'
    test_api_quick_start 'ja'
}

function test_ko_KR {
    setup_lang 'ko_KR'
    test_api_quick_start 'ko_KR'
}

function test_zh_CN {
    setup_lang 'zh_CN'
    test_api_quick_start 'zh_CN'
}

function test_language () {

    case "$language" in
        all)
            test_ca
            test_de
            test_es
            test_fr
            test_ja
            test_ko_KR
            test_zh_CN
            ;;
        ca)
            test_ca
            ;;
        de)
            test_de
            ;;
        es)
            test_es
            ;;
        fr)
            test_fr
            ;;
        ja)
            test_ja
            ;;
        ko_KR)
            test_ko_KR
            ;;
        zh_CN)
            test_zh_CN
            ;;
        *)
            BUILD_FAIL=1
            echo "Language $language not handled"
            ;;
    esac
}

function usage () {
    echo "Call the script as: "
    echo "$0 PURPOSE LANGUAGE1 LANGUAGE2..."
    echo "PURPOSE is either 'test', 'publish'."
    echo "LANGUAGE can also be 'all'."
}

if [ "$#" -lt 2 ] ; then
    usage
    exit 1
fi
if [ "$1" = "test" ] ; then
   PURPOSE="test"
elif [ "$1" = "publish" ] ; then
   PURPOSE="publish"
else
    usage
    exit 1
fi
shift
BUILD_FAIL=0
for language in "$@" ; do
  echo
  echo "Building for language $language"
  echo
  test_language "$language"
done

exit $BUILD_FAIL
