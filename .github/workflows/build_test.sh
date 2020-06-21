#!/bin/bash

set -e

rm -rf ./build_release
mkdir build_release
cd build_release
cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
ninja ci
