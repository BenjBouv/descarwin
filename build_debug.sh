#!/usr/bin/env sh
mkdir -p debug
cd debug
cmake -DCPT_WITH_OMP=1  -DCMAKE_BUILD_TYPE=Debug ..
make
cd ..
