#!/bin/bash

CNT=$1

set -eu
cd `dirname $0`/..

src/generator/generator_multi.sh $CNT
cat src/generator/out/list.txt
