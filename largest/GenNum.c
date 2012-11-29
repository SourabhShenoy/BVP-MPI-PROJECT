//sg
#include<stdio.h>
#include<stdlib.h>

int writeToFile(char * fn,int n)
{
	FILE * fp=fopen(fn,"w");
	int i;
	if(!fp)
	{
		return -1;
	}
	
	for(i=0;i<n;i++)
	{
		
		fprintf(fp,"\n%d",rand()%4000000);
	}
		fprintf(fp,"\n-1");
	
	return 0;
}

int main(int argc,char *argv[])
{
return writeToFile(argv[1],atoi(argv[2]));
	
}
