#!/bin/bash 

LOGS="./run_log"
PCM="/scratch/omkar/pcm-tsx.x"

make -f ./Makefile.rtm clean
make -f ./Makefile.rtm

SMALL="./intruder.rtm -a10 -l4 -n2048 -s1 -t"
MEDIUM="./intruder.rtm -a10 -l16 -n4096 -s1 -t"
LARGE="./intruder.rtm -a10 -l128 -n26244 -s1 -t"

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
