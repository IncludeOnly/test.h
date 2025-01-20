#!/usr/bin/env bash

VERSION="1.0.0"

help(){
    cat << EOF
USAGE
  test.sh [OPTIONS...]

OPTIONS
  -h --help     Prints this message
  -v --version  Prints the script version
  -e --exe      Set the test executable 
                (Can also be set as an environment variable)

Written by KDesp73 <Konstantinos Despoinidis>
EOF
}

while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        -e|--exe)
            shift
            TESTEXE=$1
            shift
            ;;
        -h|--help)
            help
            exit 0
            ;;
        -v|--version)
            echo "test.sh v$VERSION"
            exit 0
            ;;
        *)
            echo "ERRO: Invalid argument '$key'. Try 'test.sh --help'"
            exit 1
            ;;
    esac
done

if [ -z "${TESTEXE+x}" ]; then
    echo "ERRO: Set the TESTEXE variable" 2<&1;
    exit 1;
fi

echo "INFO: Running tests..."
$TESTEXE load
$TESTEXE
