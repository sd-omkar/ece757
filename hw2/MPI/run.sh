#!/bin/bash 

rm -f log_mpi

for i in 2 4 8 16
do
  echo $i

  echo $i 4098 >> log_mpi
  mpiexec -n $i ./mpi_ocean 4098 4098 100 >> log_mpi
  mpiexec -n $i ./mpi_ocean 4098 4098 100 >> log_mpi
  mpiexec -n $i ./mpi_ocean 4098 4098 100 >> log_mpi
  echo $i 8194 >> log_mpi
  mpiexec -n $i ./mpi_ocean 8194 8194 100 >> log_mpi
  mpiexec -n $i ./mpi_ocean 8194 8194 100 >> log_mpi
  mpiexec -n $i ./mpi_ocean 8194 8194 100 >> log_mpi
  echo >> log_mpi
done
