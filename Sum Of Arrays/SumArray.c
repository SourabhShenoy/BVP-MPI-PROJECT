
//sg
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include "mpi.h"
int main(int argc,char * argv[])
{
int * a;
int i, tag = 99;
long long int sum=0;
double startTime,endTime;
int SIZE=atoi(argv[1]);
a=(int*)malloc(SIZE*sizeof(int));
for(i=0;i<SIZE;i++)
{
	a[i]=i;
}
MPI_Init(&argc, &argv);
startTime=MPI_Wtime();
printf("Adding %d Elements\n",SIZE);
for(i=0;i<SIZE;i++)
{
	
	sum+=(a[i]);
}
printf("\nTotal : %lld\n " ,sum);
endTime = MPI_Wtime();
printf("\nwall clock time = %f\n", endTime-startTime);	       

return 0;
}
