//sg
/*
 *  Author : Aman Madaan <madaan.amanmadaan@gmail.com>
*/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ROOT 0
/*Reads a file into the array and 
returns the number of integers*/
int maxN(int * arr,int n)
{
	int i=0,max;
	for(i=0;i<n;i++)
	{
		if(arr[i]>max)
		{
			max=arr[i];
		}
	}
	return max;
	
}
void dump(int * arr,int N,int id)
{
	int i=0;
	printf("%d's Share=",id,N);
	while(i<N)
	{
		printf("\n%d",arr[i]);
		i++;
	}
}
int readFile(char * fn,int * arr)
{
	int i=0;
	FILE * fp=fopen(fn,"r");
	if(!fp)
	{
		return -1;
	}
	while(fscanf(fp,"%d",&arr[i]))
	{
		if(arr[i]==-1)
		{
			break;
		}
		i++;
	}
	return i;
}
int main(int argc,char *argv[])
{
    int  myid, /*id of the process*/
		 numprocs, /* total number of processes*/
		 i /* iterator*/;
    double startwtime = 0.0, endwtime; //time trackers
    int share; //each processes share
    int * arr ;//the receive buffer
    int N; //total number of processes
    int * initbuff; //send buffer
    int namelen;//for processor name length
    int max,maxlocal;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);
    if(myid==ROOT) 
    {
		//first read all the values in an initial array
		initbuff=(int *)malloc(sizeof(int)*atoi(argv[2]));
		int total=readFile(argv[1],initbuff);
		if(total==-1)
		{
			printf("Error! opening %s",argv[1]);
			return 0;
		}
		//calculate the share of each node
		share=total/numprocs;
		//now scatter the array to all the processes 
			startwtime = MPI_Wtime();	
		
	}
		MPI_Bcast(&share, 1, MPI_INT, 0, MPI_COMM_WORLD);		
		arr=(int*)malloc(sizeof(int)*share);
        MPI_Scatter(initbuff,share, MPI_INT,arr,share, MPI_INT,ROOT,MPI_COMM_WORLD);
       	
       	//printf("%d's Share=%d\n",myid,share);
       	//dump(arr,share,myid);	
		maxlocal=maxN(arr,share);
		MPI_Reduce( &maxlocal, &max, 1, MPI_INT, MPI_MAX, ROOT, MPI_COMM_WORLD );
		if(myid==0)
		{
        endwtime = MPI_Wtime();    //now everyone sorts their share
		printf("Maximum = %d\n",max);
		printf("wall clock time = %f\n", endwtime-startwtime);
		}	       
		fflush( stdout );
		MPI_Finalize();
    return 0;
}
