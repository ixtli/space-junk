#!/bin/bash

export CXX="`which clang++` -std=c++11 -stdlib=libc++"
export LINK="`which clang++` -std=c++11 -stdlib=libc++"
export GYP_DEFINES="clang=1 mac_deployment_target=10.8"

cd v8 && make dependencies && make native -j8 OUTDIR=../v8-build
