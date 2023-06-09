#!/bin/bash

BUILD_DIR="build"
OPTIONS="
-DCMAKE_EXPORT_COMPILE_COMMANDS=1
-DCMAKE_CXX_COMPILER_LAUNCHER=ccache
"

mkdir $BUILD_DIR;

cmake -S . -B $BUILD_DIR $OPTIONS;

ln -s $BUILD_DIR/compile_commands.json .;
