#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
//#include "hwtimer.h"
//#include <sys/errno.h>

int NumProcs;

pthread_mutex_t   SyncLock; /* mutex */
pthread_cond_t    SyncCV; /* condition variable */
int               SyncCount; /* number of processors at the barrier so far */

pthread_mutex_t   ThreadLock; /* mutex */
int               Count; /* the shared counter */
int 		  num_threads=0;
int **grid;
int xdim;
int ydim;
int timesteps;

void Barrier()
{
  int ret;

  pthread_mutex_lock(&SyncLock); /* Get the thread lock */
  SyncCount++;
  if(SyncCount == num_threads) {
    ret = pthread_cond_broadcast(&SyncCV);
    SyncCount = 0;
    assert(ret == 0);
  } else {
    ret = pthread_cond_wait(&SyncCV, &SyncLock);
    assert(ret == 0);
  }
  pthread_mutex_unlock(&SyncLock);
}

/* The function which is called once the thread is allocated */
void* ThreadLoop(void* tmp)
{
  /* each thread has a private version of local variables */
  int threadId = *((int*) tmp);
//  int num_threads = *(((int*)tmp)+1);
  int ret;
  int startTime, endTime;

  /* ********************** Execute Job ********************************* */
//  for (i = 0; i < (10000 / NumProcs); i++) {
//    pthread_mutex_lock(&ThreadLock); /* Get the thread lock */
//    Count++;
//    pthread_mutex_unlock(&ThreadLock); /* Release the lock */
//  }
//   printf("I am thread %d of %d threads\n",threadId,num_threads);

       int i,j,k;
        for(k=0;k<timesteps;k++){

                for(j=1+threadId;j<ydim-1;j+=num_threads)
                        for(i=1;i<xdim-1;i++){

                                if(k%2==1){
                                        if((i+j)%2==0){
					//	printf("%d %d\n",j,i);
                grid[j][i] = (grid[j-1][i] + grid[j][i-1] + grid[j][i] + grid[j][i+1] + grid[j+1][i]) / 5;
                                        }

                                }
                                else{
                                        if((i+j)%2!=0){
					//printf("%d %d\n",j,i);
                grid[j][i] = (grid[j-1][i] + grid[j][i-1] + grid[j][i] + grid[j][i+1] + grid[j+1][i]) / 5;
                                        }
                                }
                        }

	  Barrier();
        }



}



void ocean (int **grid_rec, int xdim_rec, int ydim_rec, int timesteps_rec, int num_threads_rec)
{
	grid = grid_rec;
	xdim = xdim_rec;
	ydim = ydim_rec;
	timesteps = timesteps_rec;

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
  pthread_t*     threads;
  pthread_attr_t attr;
  int            ret;
  int            dx;
  num_threads = num_threads_rec;

  /* Initialize array of thread structures */
  threads = (pthread_t *) malloc(sizeof(pthread_t) * num_threads);
  assert(threads != NULL);

  /* Initialize thread attribute */
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM); // sys manages contention
	
  /* Initialize mutexs */
  ret = pthread_mutex_init(&SyncLock, NULL);
  assert(ret == 0);
  ret = pthread_mutex_init(&ThreadLock, NULL);
  assert(ret == 0);

  /* Init condition variable */
  ret = pthread_cond_init(&SyncCV, NULL);
  assert(ret == 0);
  SyncCount = 0;

  Count = 0;
//  hwtimer_t timer;
//  initTimer(&timer);
//  startTimer(&timer); // Start the time measurment here before the algorithm starts

  int thread_arg[num_threads];
  for(dx=0; dx < num_threads; dx++) {
    /* ************************************************************
 *      * pthread_create takes 4 parameters
 *           *  p1: threads(output)
 *                *  p2: thread attribute
 *                     *  p3: start routine, where new thread begins
 *                          *  p4: arguments to the thread
 *                               * ************************************************************ */
	thread_arg[dx]=dx;
//	printf("Creating %d\n",thread_arg[dx]);
    ret = pthread_create(&threads[dx], &attr, ThreadLoop, (void*)(thread_arg+dx));
    assert(ret == 0);
  }

 // printf("Reached join\n");
  /* Wait for each of the threads to terminate */
  for(dx=0; dx < num_threads; dx++) {
    ret = pthread_join(threads[dx], NULL);
    assert(ret == 0);
  }

//  stopTimer(&timer); // End the time measuremnt here since the algorithm ended

//  printf("Count = %d\n", Count);
//  printf("Total Execution time: %lld ns\n", getTimerNs(&timer));

  pthread_mutex_destroy(&ThreadLock);

  pthread_mutex_destroy(&SyncLock);
  pthread_cond_destroy(&SyncCV);
  pthread_attr_destroy(&attr);


    /////////////////////// the red-black algortihm (end) ///////////////////////////
}
