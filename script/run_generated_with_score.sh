#!/bin/bash

set -eu
cd `dirname $0`/..

mkdir -p out/cases_out

TOTAL_P=0

for FILE in `ls out/cases`; do
  FILE_STDIN="out/cases/$FILE"
  echo $FILE

  ./bin/run.sh < $FILE_STDIN 1> /dev/null 2> out/cases_out/$FILE &
  
  TOTAL_P=$(($TOTAL_P+1))
  if [[ 10 -le $TOTAL_P ]]; then
    wait
    TOTAL_P=0
  fi
done
wait

TOTAL_SCORE=0

for FILE in `ls out/cases`; do
  FILE_STDOUT="out/cases_out/$FILE" # but STDERR!
  SCORE=`tail $FILE_STDOUT -n1`
  echo "case '$FILE': score=$SCORE"
  TOTAL_SCORE=$(($TOTAL_SCORE+$SCORE))
done
# echo "total score:"
echo $TOTAL_SCORE
