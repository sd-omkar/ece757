#include <stdio.h>
#include <stdlib.h>

#include "hwtimer.h"

/* Implement this function in serial_ocean and omp_ocean */
extern void ocean (int** grid, int xdim, int ydim, int timesteps,int num_threads);

void printGrid(int** grid, int xdim, int ydim);

int main(int argc, char* argv[])
{
    int xdim,ydim,timesteps;
    int** grid;
    int i,j,t;
    int num_threads;
    hwtimer_t timer;
    initTimer(&timer);
    
    srand(26);
    long long avg_store=0,avg_input=0;    

    /********************Get the arguments correctly (start) **************************/
    /* 
    Three input Arguments to the program
    1. X Dimension of the grid
    2. Y dimension of the grid
    3. number of timesteps the algorithm is to be performed
    */
    
    if (argc!=5) {
        printf("The Arguments you entered are wrong.\n");
        printf("./serial_ocean <x-dim> <y-dim> <timesteps> <num_threads>\n");
        return EXIT_FAILURE;
    } else {
        xdim = atoi(argv[1]);
        ydim = atoi(argv[2]);
        timesteps = atoi(argv[3]);
	num_threads = atoi(argv[4]);
    }
    ///////////////////////Get the arguments correctly (end) //////////////////////////


    /*********************create the grid as required (start) ************************/
    /*
    The grid needs to be allocated as per the input arguments and randomly initialized.
    Remember during allocation that we want to gaurentee a contiguous block, hence the
    nasty pointer math.

    To test your code for correctness please comment this section of random initialization.
    */
    grid = (int**) malloc(ydim*sizeof(int*));
    int *temp = (int*) malloc(xdim*ydim*sizeof(int));
    for (i=0; i<ydim; i++) {
        grid[i] = &temp[i*xdim];
    }
    for (i=0; i<ydim; i++) {
        for (j=0; j<xdim; j++) {
//		if(i==0||i==xdim-1||j==0||j==ydim-1)
//			grid[i][j]=100;
//		else
		        grid[i][j] = rand()%100;
//			printf("%d ",grid[i][j]);
        }
//	printf("\n");
    }
    ///////////////////////create the grid as required (end) //////////////////////////

	//Print input 
	for(i=0;i<xdim;i++){
		for(j=0;j<ydim;j++){
															

			avg_input+=grid[i][j];
		}
//		printf("\n");
	}
    printf("average input = %ld\n",avg_input/(xdim*ydim));
    startTimer(&timer); // Start the time measurment here before the algorithm starts

    ocean(grid, xdim, ydim, timesteps, num_threads);

    stopTimer(&timer); // End the time measuremnt here since the algorithm ended

    //Do the time calcuclation
    printf("Total Execution time: %lld ns\n", getTimerNs(&timer));

	//Print results
	for(i=0;i<xdim;i++){
		for(j=0;j<ydim;j++){

	//		printf("%d ",grid[i][j]);
			avg_store+=grid[i][j];
		}
	//	printf("\n");
	}
	avg_store/=xdim*ydim;
	printf("The average is = %ld\n",avg_store);
    // Free the memory we allocated for grid
    free(temp);
    free(grid);

    return EXIT_SUCCESS;
}
