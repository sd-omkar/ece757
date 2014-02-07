
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char * argv[]) {
  
  int x;        // the variable to increment
  int count;    // the number of times each variable will increment x
  int nThreads; // the number of threads to use
  int i;        // a loop counter
  omp_lock_t lock; // a traditional lock
        
  // the argument stream should look like this:
  // increment <count> <nThreads>
  if(argc!=3) {
    fprintf(stderr,"Usage:\n%s <count> <nThreads>\n",argv[0]);
    exit(1);
  }

  count = atoi(argv[1]);
  nThreads = atoi(argv[2]);

  if(count<=0 || nThreads <=0) {
    fprintf(stderr,"Count and nThreads must be >0\n");
    exit(1);
  }

  // arguments parsed successfully
  // now start incrementing
  omp_set_num_threads(nThreads);
  x = 0;

  // must call this if you use locks...
  omp_init_lock(&lock);

  // fork a team of threads
  #pragma omp parallel \
     private(i) \
     shared(x,count) 
  {

    for(i=0;i<count;i++) {
      // use critical section construct to increment
      #pragma omp critical
      {
        // each thread will execute here, but one-at-a-time
        x++;
      
      } // end of critical section
    }

    // wait for all threads to finish incrementing
    #pragma omp barrier
    
    #pragma omp master 
    {
      // only the master thread will execute here (thread id = 0)
      fprintf(stdout,"Master thread (id=%i) reports x=%i\n",
                      omp_get_thread_num(),
                      x);
      x = 0;
    }

    // wait for the master to print and then reset x
    #pragma omp barrier
          
    // now update x using ATOMIC directive
    for(i=0;i<count;i++) {
      #pragma omp atomic
      x++;
    }

    // ensure all threads have done the update
    #pragma omp barrier

    #pragma omp single
    {
       // use of Single means ANY thread may enter, but only one
       fprintf(stdout,"            Thread %i reports x=%i\n",
                       omp_get_thread_num(),
                       x);
       x = 0;

    }
    
    // ensure all threads wait for printing and reset before continue
    #pragma omp barrier
    
    // each thread will now loop, acquiring and releasing the
    // omp lock
    for(i=0;i<count;i++) {
      omp_set_lock(&lock); 
      // this thread now has the lock
      x++;
      
      // memory must remain consistent -- why?
      // Answer: ATOMIC and CRITICAL have built-in flush!
      #pragma omp flush
      
      omp_unset_lock(&lock);       // don't forget to unlock
    }

    #pragma omp barrier
    
    #pragma omp single
    {
       
            
       // done with the lock
       omp_destroy_lock(&lock);
       fprintf(stdout,"            Thread %i reports x=%i\n",
                       omp_get_thread_num(),
                       x);
       
    }
  } // JOIN occurs here, with an implicit barrier
    // end of Parallel

  exit(0);  
}

