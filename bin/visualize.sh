#!/bin/bash


set -eu
cd `dirname $0`/..

cd out
../third_party/tools/target/release/vis $@ > /dev/null

echo `readlink -f out.svg`
