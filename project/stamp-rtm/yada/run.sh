#!/bin/bash 

LOGS="./run_log"
PCM="/scratch/omkar/pcm-tsx.x"

make -f ./Makefile.rtm clean
make -f ./Makefile.rtm

SMALL="./yada.rtm -a20 -i ./inputs/633.2 -t"
MEDIUM="./yada.rtm -a20 -i ./inputs/ttimeu10000.2 -t"
LARGE="./yada.rtm -a20 -i ./inputs/ttimeu1000000.2 -t"

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
