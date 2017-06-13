#!/bin/bash

mkdir data

git clone https://github.com/ISibboI/fann

cd fann
cmake .
sudo make install
