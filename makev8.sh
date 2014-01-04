#!/bin/bash

export CC=`which clang`
export CXX=`which clang++`
export GYP_DEFINES="clang=1"

cd v8 && make dependencies && make native -j8 OUTDIR=../v8-build
