#!/usr/bin/env sh
mkdir -p debug
cd debug
cmake -DCPT_WITH_OMP=0 -DDAE_WITH_MPI=0 -DCMAKE_BUILD_TYPE=Debug ..
make
cd ..