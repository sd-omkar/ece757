#include <mpi.h>

extern int VERBOSE;

void ocean (float **grid, int xdim, int ydim, int timesteps, int rank, int size)
{
    /********************* the red-black algortihm (start)************************/
    /*
    In odd timesteps, calculate indeces with - and in even timesteps, calculate indeces with * 
    See the example of 6x6 matrix, A represents the corner elements. 
        A A A A A A
        A - * - * A
        A * - * - A
        A - * - * A
        A * - * - A
        A A A A A A 
    */

    // PUT YOUR CODE HERE

  for (int t=0; t < timesteps/2; t++) {
    int flag = 1;
    int i, j;
    MPI_Status status;

    for (j=1; j < ydim-1; j++) {
      for (i=flag; i < xdim-1; i+=2) {
        grid[j][i] = (grid[j-1][i] + grid[j][i-1] + grid[j][i] + grid[j][i+1] + grid[j+1][i]) / 5;
      }
      flag = (flag == 1 ? 2 : 1);
    }

    flag = 2;
    for (j=1; j < ydim-1; j++) {
      for (i=flag; i < xdim-1; i+=2) {
        grid[j][i] = (grid[j-1][i] + grid[j][i-1] + grid[j][i] + grid[j][i+1] + grid[j+1][i]) / 5;
      }
      flag = (flag == 1 ? 2 : 1);
    }

    // After every timestep, elements on the boundary need to be updated
    // Send and receive orders need to alternate between partitions to avoid deadlock
    if (rank == 0) {
      MPI_Send (grid[ydim-2], (xdim * 1), MPI_INT, (rank+1), 0, MPI_COMM_WORLD);
      MPI_Recv (grid[ydim-1], (xdim * 1), MPI_INT, (rank+1), 0, MPI_COMM_WORLD, &status);
    }
    else if (rank == (size-1)) {
      MPI_Recv (grid[0], (xdim * 1), MPI_INT, (rank-1), 0, MPI_COMM_WORLD, &status);
      MPI_Send (grid[1], (xdim * 1), MPI_INT, (rank-1), 0, MPI_COMM_WORLD);
    }
    else if (rank % 2 == 1){
      // Upper boundary
      MPI_Recv (grid[0], (xdim * 1), MPI_INT, (rank-1), 0, MPI_COMM_WORLD, &status);
      MPI_Send (grid[1], (xdim * 1), MPI_INT, (rank-1), 0, MPI_COMM_WORLD);
      // Lower boundary
      MPI_Recv (grid[ydim-1], (xdim * 1), MPI_INT, (rank+1), 0, MPI_COMM_WORLD, &status);
      MPI_Send (grid[ydim-2], (xdim * 1), MPI_INT, (rank+1), 0, MPI_COMM_WORLD);
    }
    else if (rank % 2 == 0){
      // Upper boundary
      MPI_Send (grid[1], (xdim * 1), MPI_INT, (rank-1), 0, MPI_COMM_WORLD);
      MPI_Recv (grid[0], (xdim * 1), MPI_INT, (rank-1), 0, MPI_COMM_WORLD, &status);
      // Lower boundary
      MPI_Send (grid[ydim-2], (xdim * 1), MPI_INT, (rank+1), 0, MPI_COMM_WORLD);
      MPI_Recv (grid[ydim-1], (xdim * 1), MPI_INT, (rank+1), 0, MPI_COMM_WORLD, &status);
    }
  }
  
    /////////////////////// the red-black algortihm (end) ///////////////////////////
}
