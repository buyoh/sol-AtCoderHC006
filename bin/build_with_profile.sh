#!/bin/bash

set -eu
cd `dirname $0`/..

mkdir -p out
cd out
g++ --std=c++17 -O3  -fprofile-arcs -ftest-coverage -pg -g -lgcov -o ../out/main_prof ../src/app/main.cpp -Wall
