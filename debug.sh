#!/bin/bash
# This script is used to build the project in debug mode on onyx.boisestate.edu
# You can use cmake presets detailed in the README on systems that have cmake 3.27 or higher.
if [ ! -d ./build ]
then
    mkdir -p build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    echo "Build directory is already present. Run clean.sh first!"
fi