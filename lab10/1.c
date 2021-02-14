#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
int random_val(int a,int b)
{
    return rand()%(b-a+1);
}
int main(int argc,char** argv)
{
    int A[1000000];
    int B[1000000];
    int rank,size;
    long chunk=atol(argv[1]);
    long int total;
    double start,end,average;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0)
    {
        srand(time(0));
        for(long int i=0;i<size*chunk;i++)
            A[i]=random_val(0,100)-40;
    }
    MPI_Scatter(A,chunk,MPI_INT,B,chunk,MPI_INT,0,MPI_COMM_WORLD);
    start=MPI_Wtime();
    long int localsum=0;
    for(int i=0;i<chunk;i++)
        localsum+=B[i];
    MPI_Reduce(&localsum,&total,1,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        average=total/(chunk*size);
        end=MPI_Wtime();
        printf("Number of data elements:%ld\n",size*chunk);
        printf("Average is :%lf\n",average);
        printf("Time taken:%lf\n",end-start);

    }
    MPI_Finalize();
    return 0;


}
