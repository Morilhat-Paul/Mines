#!/bin/bash

mkdir -p build
cd ./build/
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug --target Mines -j8
