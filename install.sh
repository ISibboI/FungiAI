#!/bin/bash

git clone https://github.com/libfann/fann

cd fann
cmake .
sudo make install
