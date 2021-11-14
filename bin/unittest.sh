#!/bin/bash

set -eu
cd `dirname $0`/..

mkdir -p out
g++ --std=c++17 -lgtest_main -lgtest -lpthread -o out/unittest src/app/unittest.cpp -Wall
out/unittest
