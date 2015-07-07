#!/bin/bash

export CXX="`which clang++` -std=c++14 -stdlib=libc++"
export LINK="`which clang++` -std=c++14 -stdlib=libc++"
export GYP_DEFINES="clang=1 mac_deployment_target=10.8"

# Required for build here:
# https://code.google.com/p/v8-wiki/wiki/UsingGit#Prerequisites
# http://dev.chromium.org/developers/how-tos/install-depot-tools
export PATH=`pwd`/depot_tools:"$PATH"

fetch v8 && cd v8 && gclient sync && make native -j8 OUTDIR=../v8-build
