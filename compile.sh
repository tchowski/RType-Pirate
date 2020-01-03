#!/bin/bash

mkdir -p build
cd build
conan install .. --build=missing
cmake .. -G "Unix Makefiles"
make
