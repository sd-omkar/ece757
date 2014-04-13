#!/bin/bash 

LOGS="./run_log"
PCM="/scratch/omkar/pcm-tsx.x"

make -f ./Makefile.rtm clean
make -f ./Makefile.rtm

SMALL="./ssca2.rtm -s13 -i1.0 -u1.0 -l3 -p3 -t"
MEDIUM="./ssca2.rtm -s17 -i1.0 -u1.0 -l6 -p6 -t"
LARGE="./ssca2.rtm -s20 -i1.0 -u1.0 -l9 -p9 -t"

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
