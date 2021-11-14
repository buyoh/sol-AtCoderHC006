#!/bin/bash

set -eu
cd `dirname $0`/..

for FILE in `ls stdin`; do
  ID="${FILE%%.*}"
  FILE_STDIN="stdin/$FILE"
  FILE_STDOUT="out/$ID.out.txt"
  FILE_STDERR="out/$ID.err.txt"

  ./bin/run.sh < $FILE_STDIN > $FILE_STDOUT 2> $FILE_STDERR
done
