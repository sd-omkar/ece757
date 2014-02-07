#include <omp.h>

// globals
extern int xdim;
extern int ydim;

// does a = b + c
void addmatrix(int ** a, int ** b, int ** c) {
  
  int i,j;

  // handle the outer loop in parallel
  #pragma omp parallel for \
    shared(a,b,c,xdim,ydim) \
    private(i,j) \
    schedule(dynamic)
  for(j=0;j<ydim;j++) {

    // nothing special will be done to parallelize the inner loop--
    // this section is already done in parallel
    for(i=0;i<xdim;i++) {
      a[j][i] = b[j][i] + c[j][i];
    }
    
  } // end of parallel for (implicit barrier)
        
}

