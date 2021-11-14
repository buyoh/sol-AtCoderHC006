#!/bin/bash

CNT=$1

set -eu
cd `dirname $0`

if [[ x$CNT == x ]]; then
  echo "usage: $0 cnt"
  exit 1
fi

mkdir -p out

LI=()
for i in `seq $CNT`; do
  OUT_FILE="./out/$i.txt"
  OUT_FILE=`readlink -f $OUT_FILE`
  ruby generator.rb > $OUT_FILE
  LI=("${LI[@]}" $OUT_FILE)
done

cat /dev/null > ./out/list.txt
for x in ${LI[@]}; do echo $x >> ./out/list.txt; done

