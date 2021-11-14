#!/bin/bash

set -eu
cd `dirname $0`/..

TOTAL_SCORE=0

for FILE in `ls out/cases`; do
  FILE_STDIN="out/cases/$FILE"

  SCORE=`./bin/run.sh < $FILE_STDIN 2>&1 > /dev/null | tail -n1`
  echo "case '$FILE': score=$SCORE"
  TOTAL_SCORE=$(($TOTAL_SCORE+$SCORE))
done
echo "total score:"
echo $TOTAL_SCORE
