#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

// in addmatrix.c
void addmatrix(int ** a, int ** b, int ** c);

// in printmatrix.c
void printmatrix(int ** matrix);

// globals
int xdim;
int ydim;  // matrix dimensions

int main(int argc, char * argv[]) {

  int i,j,n; // loop counters
  
  int ** a;  // the matrices themselves
  int ** b; 
  
  int count; // number to add
        
  // argument stream should be matrix dimensions & count
  if(argc!=4) {
    fprintf(stderr,"Usage:\n%s <xdim> <ydim> <count>\n",
                    argv[0]);
    exit(1);
  }

  xdim = atoi(argv[1]);
  ydim = atoi(argv[2]);
  count = atoi(argv[3]);

  if(xdim <= 0 || ydim <= 0 || count < 2) {
    fprintf(stderr,"xdim,ydim must be >0, count must be >1\n");
    exit(1);
  }

  // seed the random number generator
  srand(time(NULL));
        
  // allow the omp library to select the number of threads to use
  omp_set_dynamic(1);
  
  // allocate the matrices
  a = (int **) malloc( ydim * sizeof(int *));
  b = (int **) malloc( ydim * sizeof(int *));
  
  for(j=0;j<ydim;j++) {
    a[j] = (int*) malloc( xdim * sizeof(int));
    b[j] = (int*) malloc( xdim * sizeof(int));
    
    for(i=0;i<xdim;i++) {
      a[j][i] = 0;
      b[j][i] = rand() % 5;
    }
  }
  
  
  // do the specified number of additions
  for(n=0;n<count;n++) {

    printmatrix(a);
    fprintf(stdout,"    +\n");
    printmatrix(b);
    fprintf(stdout,"    =\n");
    
    // calls into an OMP-enabled file    
    addmatrix(a,a,b); // does a = a+b

    printmatrix(a);
    fprintf(stdout,"\n***********************\n\n");
    
    // re-initialize b to a new random matrix
    // Note: this is not done in parallel!
    for(j=0;j<ydim;j++) {
      for(i=0;i<xdim;i++) {
        b[j][i] = rand() % 5;
      }
    }
  }
  
  exit(0);
}

