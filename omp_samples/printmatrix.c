#include <stdio.h>

// globals
extern int xdim;
extern int ydim;

void printmatrix(int ** matrix) {
  int i, j;

  for(j=0;j<ydim;j++) {
    for(i=0;i<xdim;i++) {
      printf("%-4i ",matrix[j][i]);  
    }
    
    printf("\n");
  }
}

