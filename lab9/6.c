#include<mpi.h> 
#include<stdio.h>
#include<time.h>
#include<limits.h>

int main(int argc,char *argv[ ]) 
{ 
	int size,rank,actualmin;
	double start,end;
	int A[1000000],B[1000000];
	long int chunk=atol(argv[1]); 
	MPI_Init(&argc,&argv); 
	MPI_Comm_size(MPI_COMM_WORLD,&size); 
	MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
	if(rank==0) 
	{ 
		srand(time(0));
		for(int i=0;i<chunk*size;i++)
			A[i]=rand()%100+10;
		printf("Number of element:%ld\n",chunk*size);
	} 
	MPI_Scatter(A,chunk,MPI_INT,B,chunk,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	start=MPI_Wtime();
	int minimum=INT_MAX;
	for(long int i=0;i<chunk;i++)
	{ 
		if(B[i]<minimum)
			minimum=B[i];
				
	}
	MPI_Reduce(&minimum,&actualmin,1,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("Minimum element is :%d\n",actualmin);
		end=MPI_Wtime();
	}
	if(rank==0)
		printf("Time Taken:%lf\n",end-start);
	MPI_Finalize(); 
return 0; 
}