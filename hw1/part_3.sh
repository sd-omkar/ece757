#!/bin/bash 

if [ $# -ne 1 ]; then
  echo "Usage run.sh DIMENSION"
  exit 0
fi

echo Serial
./serial_ocean $1 $1 100
./serial_ocean $1 $1 100
./serial_ocean $1 $1 100
echo

echo Dynamic 2
export OMP_NUM_THREADS=2
./omp_ocean_dyn $1 $1 100
./omp_ocean_dyn $1 $1 100
./omp_ocean_dyn $1 $1 100
echo

echo Dynamic 4
export OMP_NUM_THREADS=4
./omp_ocean_dyn $1 $1 100
./omp_ocean_dyn $1 $1 100
./omp_ocean_dyn $1 $1 100
echo

echo Dynamic 8
export OMP_NUM_THREADS=8
./omp_ocean_dyn $1 $1 100
./omp_ocean_dyn $1 $1 100
./omp_ocean_dyn $1 $1 100
echo

echo Dynamic 16
export OMP_NUM_THREADS=16
./omp_ocean_dyn $1 $1 100
./omp_ocean_dyn $1 $1 100
./omp_ocean_dyn $1 $1 100
