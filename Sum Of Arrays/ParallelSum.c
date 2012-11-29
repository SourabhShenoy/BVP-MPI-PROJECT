//sg
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include "mpi.h"
int main(int argc,char * argv[])
{
int * a;
int myrank,i, tag = 99,numProcess;
long long sum,halfSum1=0,halfSum2=0;
double startTime,endTime;
MPI_Status status;
int SIZE=atoi(argv[1]);
a=(int *)malloc(SIZE*sizeof(int));
for(i=0;i<SIZE;i++)
{
	a[i]=i;
}
MPI_Init(&argc, &argv);
MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
startTime=MPI_Wtime();
if (myrank == 0) 
{
printf("Adding %d Elements\n",SIZE);
MPI_Send( a+SIZE/2, SIZE/2, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
for(i=0;i<SIZE/2;i++)
{
	halfSum1+=a[i];
}
MPI_Recv(&halfSum2, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD, &status);
printf("\nFrom Node 1 : %lld " , halfSum1);
printf("\nFrom Node 3 : %lld " , halfSum2);
printf("\nTotal : %lld\n " ,halfSum1+halfSum2); 
endTime = MPI_Wtime();
printf("\nwall clock time = %f\n", endTime-startTime);	       
}
else if (myrank == 1)
{
int i,j;
MPI_Recv( a+SIZE/2, SIZE/2, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, &status);
for(i=SIZE/2;i<SIZE;i++)
{
	halfSum2+=a[i];
}
MPI_Send( &halfSum2, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD);
}
return 0;
}
