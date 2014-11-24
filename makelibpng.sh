#!/bin/bash
mkdir -p libpng-build
cd libpng-1.6.15
TARGET=$(pwd)"/../libpng-build/"
echo "Building libpng with target $TARGET"
./configure --prefix=$TARGET
make check
make install