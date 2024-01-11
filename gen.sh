#!/bin/bash

export CC=~/.bin/gcc-13.2.0/usr/local/bin/gcc
export CXX=~/.bin/gcc-13.2.0/usr/local/bin/g++

BUILD_DIR="build"
OPTIONS="
-DCMAKE_EXPORT_COMPILE_COMMANDS=1
-DCMAKE_CXX_COMPILER_LAUNCHER=ccache
-DCMAKE_BUILD_TYPE=Debug
"

mkdir $BUILD_DIR;

cmake -S . -B $BUILD_DIR $OPTIONS;

ln -sf $BUILD_DIR/compile_commands.json .;
cp -n rc build/;
