#!/bin/bash

set -eu
cd `dirname $0`/..

for FILE in `ls stdin`; do
  ID="${FILE%%.*}"
  FILE_STDIN="stdin/$FILE"
  FILE_STDOUT="out/$ID.prof.out.txt"
  FILE_STDERR="out/$ID.prof.err.txt"

  ./bin/run_prof.sh < $FILE_STDIN > $FILE_STDOUT 2> $FILE_STDERR

  FILE_IMAGE=$(./bin/visualize.sh `readlink -f $FILE_STDIN` `readlink -f $FILE_STDOUT`)
  tail -n1 $FILE_STDERR
  mv $FILE_IMAGE "out/$ID.out."${FILE_IMAGE##*.}""

  break
done
