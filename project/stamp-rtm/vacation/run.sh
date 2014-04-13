#!/bin/bash 

LOGS="./run_log"
PCM="/scratch/omkar/pcm-tsx.x"

make -f ./Makefile.rtm clean
make -f ./Makefile.rtm

# Low contention
SMALL="./vacation.rtm -n2 -q90 -u98 -r16384 -t4096 -c"
MEDIUM="./vacation.rtm -n2 -q90 -u98 -r1048576 -t4096 -c"
LARGE="./vacation.rtm -n2 -q90 -u98 -r1048576 -t4194304 -c"

for j in 1 2 3
do
for i in 1 2 4 8
do 
  echo "=============================" >> $LOGS/low_small.$j
  $PCM "$SMALL $i" >> $LOGS/low_small.$j
  echo "=============================" >> $LOGS/low_small.$j

  echo "=============================" >> $LOGS/low_medium.$j
  $PCM "$MEDIUM $i" >> $LOGS/low_medium.$j
  echo "=============================" >> $LOGS/low_medium.$j

  echo "=============================" >> $LOGS/low_large.$j
  $PCM "$LARGE $i" >> $LOGS/low_large.$j
  echo "=============================" >> $LOGS/low_large.$j
done
done

# High contention
SMALL="./vacation.rtm -n4 -q60 -u90 -r16384 -t4096 -c"
MEDIUM="./vacation.rtm -n4 -q60 -u90 -r1048576 -t4096 -c"
LARGE="./vacation.rtm -n4 -q60 -u90 -r1048576 -t4194304 -c"

for j in 1 2 3
do
for i in 1 2 4 8
do 
  echo "=============================" >> $LOGS/high_small.$j
  $PCM "$SMALL $i" >> $LOGS/high_small.$j
  echo "=============================" >> $LOGS/high_small.$j

  echo "=============================" >> $LOGS/high_medium.$j
  $PCM "$MEDIUM $i" >> $LOGS/high_medium.$j
  echo "=============================" >> $LOGS/high_medium.$j

  echo "=============================" >> $LOGS/high_large.$j
  $PCM "$LARGE $i" >> $LOGS/high_large.$j
  echo "=============================" >> $LOGS/high_large.$j
done
done
