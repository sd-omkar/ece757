#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

// Output levels, 1 = Print Avg. and Time, 2 = Print Grid, 3 = Print Partitions
int VERBOSE = 1;

/* Implement this function in serial_ocean and omp_ocean */
extern void ocean (int** grid, int xdim, int ydim, int timesteps, int rank, int size);

void printGrid(int** grid, int xdim, int ydim);

int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double start_s, end_s;
    MPI_Status status;

    int xdim,ydim,timesteps;
    int **grid, **partition;
    int i,j,t;

    //hwtimer_t timer;
    //initTimer(&timer);
    
    /********************Get the arguments correctly (start) **************************/
    /* 
    Three input Arguments to the program
    1. X Dimension of the grid
    2. Y dimension of the grid
    3. number of timesteps the algorithm is to be performed
    */
   
    if (rank == 0) {
      if (argc!=4) {
          printf("The Arguments you entered are wrong.\n");
          printf("./serial_ocean <x-dim> <y-dim> <timesteps>\n");
          return EXIT_FAILURE;
      } else {
          xdim = atoi(argv[1]);
          ydim = atoi(argv[2]);
          timesteps = atoi(argv[3]);
      }
    }

    // Broadcast xdim, ydim, timesteps
    MPI_Bcast(&xdim, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&ydim, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&timesteps, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int ydim_part = (ydim-2)/size;

    //printf("xdim = %d ydim = %d timesteps = %d ydim_part = %d\n", xdim, ydim, timesteps, ydim_part);

    ///////////////////////Get the arguments correctly (end) //////////////////////////


    /*********************create the grid as required (start) ************************/
    /*
    The grid needs to be allocated as per the input arguments and randomly initialized.
    Remember during allocation that we want to gaurentee a contiguous block, hence the
    nasty pointer math.

    To test your code for correctness please comment this section of random initialization.
    */

    // root creates and initializes the full grid.
    if (rank == 0) {
      grid = (int**) malloc(ydim*sizeof(int*));
      int *temp = (int*) malloc(xdim*ydim*sizeof(int));
      for (i=0; i<ydim; i++) {
        grid[i] = &temp[i*xdim];
      }
      for (i=0; i<ydim; i++) {
        for (j=0; j<xdim; j++) {
          grid[i][j] = rand() % 100;
          /*
          if (i==0 || j==0 || i==(ydim-1) || j==(xdim-1))
            grid[i][j] = 100;
          else
            grid[i][j] = 0;
          */
        }
      }
    }

    // others create partitions to hold the data
    else {
      partition = (int**) malloc((ydim_part + 2) * sizeof(int*));
      int *temp = (int*) malloc(xdim * (ydim_part +2) * sizeof(int));
      for (i=0; i<(ydim_part + 2); i++) {
        partition[i] = &temp[i*xdim];
      }
    }

    if (rank == 0) {
    printGrid(grid, xdim, ydim);
    }

    start_s = MPI_Wtime(); // Start the time measurment here before the algorithm starts
    
    // Root sends the partitions and others receive
    if (rank == 0) {
      for (i=1; i<size; i++) {
        MPI_Send (grid[i * ydim_part], (xdim * (ydim_part + 2)), MPI_INT, i, 0, MPI_COMM_WORLD);
      }
    }
    else {
      MPI_Recv (partition[0], (xdim * (ydim_part + 2)), MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    ///////////////////////create the grid as required (end) //////////////////////////

    if (rank == 0)
      ocean(grid, xdim, ydim_part+2, timesteps, rank, size);
    else
      ocean(partition, xdim, ydim_part+2, timesteps, rank, size);

    // Root receives partitions from others
    if (rank != 0) 
      MPI_Send (partition[1], (xdim * ydim_part), MPI_INT, 0, 0, MPI_COMM_WORLD);
    if (rank == 0) {
      for (i=1; i<size; i++) {
        MPI_Recv (grid[i * ydim_part+1], (xdim * (ydim_part)), MPI_INT, i, 0, MPI_COMM_WORLD, &status);
      }
    }

    end_s = MPI_Wtime(); // Start the time measurment here before the algorithm starts

    //Calculate average
    if (VERBOSE >= 1 && rank == 0) {
    printGrid(grid, xdim, ydim);
      float sum = 0;
      for (i=0; i<ydim; i++)
        for (j=0; j<xdim; j++)
          sum += grid[i][j];
      sum /= (xdim*ydim);
      printf("Avg = %d\n", (int)sum);
    }

    // Free the memory we allocated for grid
    if (rank == 0) {
      free(grid);
      //Do the time calcuclation
      printf("Time: %.3f ms\n", 1000 * (end_s - start_s));
    }
    else free(partition);

    MPI_Finalize();
    return EXIT_SUCCESS;
}

void printGrid(int** grid, int xdim, int ydim) {
  if (VERBOSE >= 2) {
  for (int i=0; i<ydim; i++) {
    for (int j=0; j<xdim; j++)
      printf("%3d ", grid[i][j]);
    printf("\n");
  }
  }
}
