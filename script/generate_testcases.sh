#!/bin/bash

set -eu
cd `dirname $0`/..

mkdir -p out/cases/

i=0
for f in `./bin/generator_multi.sh 30`; do
  cp $f out/cases/in_${i}.txt
  i=$(($i+1))
done
