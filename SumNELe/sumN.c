/*
 *  Aman Madaan
    Ideas used from samples by :  
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
*/
#include "mpi.h"
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
int main(int argc,char *argv[])
{
    int done = 0, n=0, myid, numprocs, i;
    double share,total;
    double startwtime = 0.0, endwtime;
int namelen;
    int N;
  //  n=atoi(argv[1]);
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);
    while (n<=20000000) {
	    startwtime = MPI_Wtime();
        share=0;
		n+=8000;
 
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
            for (i = myid ; i <= n; i += numprocs)
	     {
		share+=i; //everyone calculates their bit, then they sum it up
             }
            MPI_Reduce(&share, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (myid == 0) {
                printf("sum till %d is approximately %.16f",n,total);
		endwtime = MPI_Wtime();
		printf("wall clock time = %f\n", endwtime-startwtime);	       
		fflush( stdout );
	    }
	n++;	
       }
    MPI_Finalize();
    return 0;
}
