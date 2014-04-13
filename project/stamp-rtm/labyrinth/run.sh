#!/bin/bash 

LOGS="./run_log"
PCM="/scratch/omkar/pcm-tsx.x"

make -f ./Makefile.rtm clean
make -f ./Makefile.rtm

SMALL="./labyrinth.rtm -i ./inputs/random-x32-y32-z3-n96.txt -t"
MEDIUM="./labyrinth.rtm -i ./inputs/random-x64-y64-z3-n64.txt -t"
LARGE="./labyrinth.rtm -i ./inputs/random-x512-y512-z7-n512.txt -t"

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
