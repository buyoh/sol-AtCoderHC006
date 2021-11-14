#!/bin/bash

set -eu
cd `dirname $0`/..

mkdir -p out
g++ --std=c++17 -O3 -o out/main src/app/main.cpp
