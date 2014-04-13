#!/bin/bash 

LOGS="./run_log"
PCM="/scratch/omkar/pcm-tsx.x"

make -f ./Makefile.rtm clean
make -f ./Makefile.rtm

SMALL="./bayes.rtm -v32 -r1024 -n2 -p20 -i2 -e2 -t"
MEDIUM="./bayes.rtm -v32 -r4096 -n2 -p20 -i2 -e2 -t"
LARGE="./bayes.rtm -v32 -r4096 -n10 -p40 -i2 -e2 -s1 -t"

for j in 1 2 3
do
for i in 1 2 4 8
do 
  echo "=============================" >> $LOGS/small.$j
  $PCM "$SMALL $i" >> $LOGS/small.$j
  echo "=============================" >> $LOGS/small.$j

  echo "=============================" >> $LOGS/medium.$j
  $PCM "$MEDIUM $i" >> $LOGS/medium.$j
  echo "=============================" >> $LOGS/medium.$j

  echo "=============================" >> $LOGS/large.$j
  $PCM "$LARGE $i" >> $LOGS/large.$j
  echo "=============================" >> $LOGS/large.$j
done
done
