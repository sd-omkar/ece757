#!/bin/bash 

export OMP_NUM_THREADS=8
for j in {100..11000..500}
do 
  echo $j
  ./serial_ocean $j $j 100
  ./omp_ocean_dyn $j $j 100
  ./omp_ocean_stat $j $j 100
  echo
done
