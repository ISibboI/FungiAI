#!/bin/bash

git clone https://github.com/Artelnics/OpenNN

cd OpenNN
mkdir build
cd build
cmake -D__OPENNN_OMP__=1 ..
make
