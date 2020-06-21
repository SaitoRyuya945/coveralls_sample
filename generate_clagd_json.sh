#!/bin/bash

mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
mv compile_commands.json ../ 
cd ../
rm -rf build
