#!/bin/bash

#set -x
set -e
set -u

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <gnu|clang> <wanted_version> <compiler_name>"
    exit 2
fi

wanted_compiler="$1"
wanted_version="$2"
compiler_name="$3"

if [[ ${wanted_compiler} != "gnu" ]] && [[ ${wanted_compiler} != "clang" ]]; then
    echo "Please select gnu or clang."
    exit 3
fi

if [ ${#wanted_version} -ne 5 ]; then
    echo "Please give a 5-digit version number."
    exit 4
fi

if [[ ${compiler_name} != "g"* ]] && [[ ${compiler_name} != "clang"* ]]; then
    echo "Only GNU and Clang compilers are supported."
    exit 5
fi

if [[ ${wanted_compiler} == "gnu" ]] && [[ ${compiler_name} != "g"* ]]; then
    exit 1
fi

if [[ ${wanted_compiler} == "clang" ]] && [[ ${compiler_name} != "clang"* ]]; then
    exit 1
fi

# GNU
if [[ ${compiler_name} == "g"* ]]; then
    version=$(${compiler_name} -dumpversion)

    if [ ${#version} -eq 1 ]; then
        version=$(${compiler_name} -dumpfullversion)
    fi
fi

# Clang
if [[ ${compiler_name} == "clang"* ]]; then
    version=$(${compiler_name} -dumpversion)
fi

# See: http://qiita.com/misho/items/f1c0748e9a31bea62e5c

# #ifndef GCC_VERSION
# #define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
# #endif

long_version=$(echo "${version}" | sed -e 's/\.\([0-9]\)\b/0\1/g' -e 's/\.//g')

if [ "${long_version}" -ge "${wanted_version}" ];
then
    echo 0
    exit 0
else
    echo 1
    exit 1
fi
