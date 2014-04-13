#!/bin/bash 

LOGS="./run_log"
PCM="/scratch/omkar/pcm-tsx.x"

make -f ./Makefile.rtm clean
make -f ./Makefile.rtm

# Low contention
SMALL="./kmeans.rtm -m40 -n40 -t0.05 -i inputs/random-n2048-d16-c16.txt -p"
MEDIUM="./kmeans.rtm -m40 -n40 -t0.05 -i inputs/random-n16384-d24-c16.txt -p"
LARGE="./kmeans.rtm -m40 -n40 -t0.00001 -i inputs/random-n65536-d32-c16.txt -p"

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
SMALL="./kmeans.rtm -m15 -n15 -t0.05 -i inputs/random-n2048-d16-c16.txt -p"
MEDIUM="./kmeans.rtm -m15 -n15 -t0.05 -i inputs/random-n16384-d24-c16.txt -p"
LARGE="./kmeans.rtm -m15 -n15 -t0.00001 -i inputs/random-n65536-d32-c16.txt -p"

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
