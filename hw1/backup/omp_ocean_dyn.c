#include <omp.h>
#include <stdio.h>

extern int VERBOSE;

void ocean (int **grid, int xdim, int ydim, int timesteps)
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

  #pragma omp parallel for shared(flag, grid, xdim, ydim) private(i, j) schedule(dynamic)
  for (j=1; j < ydim-1; j++) {
    for (i=flag; i < xdim-1; i+=2) {
      grid[j][i] = (grid[j-1][i] + grid[j][i-1] 
          + grid[j][i] 
          + grid[j][i+1] + grid[j+1][i]) / 5;
    }
    flag = (flag == 1 ? 2 : 1);
  }

  flag = 2;
  #pragma omp parallel for shared(flag, grid, xdim, ydim) private(i, j) schedule(dynamic)
  for (j=1; j < ydim-1; j++) {
    for (i=flag; i < xdim-1; i+=2) {
      grid[j][i] = (grid[j-1][i] + grid[j][i-1] 
          + grid[j][i] 
          + grid[j][i+1] + grid[j+1][i]) / 5;
    }
    flag = (flag == 1 ? 2 : 1);
  }
  }

    /////////////////////// the red-black algortihm (end) ///////////////////////////
}
