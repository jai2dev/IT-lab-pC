
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>


int main(){
if(myrank%2==0)
{

MPI_Comm_split(MPI_COMM_WORLD,0,0,&comm1);

}

else {
MPI_Comm_split(MPI_COMM_WORLD,1,0,&comm2);

}}