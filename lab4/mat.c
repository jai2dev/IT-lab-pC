

#include <stdio.h>
#include <omp.h>
#include <time.h>

int main()
{
	int tmp,i,j,k,M,N,P;
	
printf("Enter the value of M:\n");
scanf("%d",&M);
printf("Enter the value of P:\n");
scanf("%d",&P);
printf("Enter the value of N:\n");
scanf("%d",&N);

int C[M][N],S[M][N],B[P][N],A[M][P];

printf("enter the first matrix' elements=\n");    
for(i=0;i<M;i++)    
{    
for(j=0;j<P;j++)    
{    
scanf("%d",&A[i][j]);    
}    
}    
printf("enter the second matrix element=\n");    
for(i=0;i<P;i++)    
{    
for(j=0;j<N;j++)    
{    
scanf("%d",&B[i][j]);    
}    
}  

double start_time = omp_get_wtime();


#pragma omp parallel for private(tmp, j, k)
for (i=0; i<M; i++)
{
for (j=0; j<N; j++)
{
tmp = 0.0;
for( k=0; k<P; k++)
{
/* C(i,j) = sum(over k) A(i,k) * B(k,j)*/
tmp += A[i][k] * B[k][j];
}
C[i][j] = tmp;
}
}
double run_time = omp_get_wtime() - start_time;


// t2=omp_get_wtime();
printf("multiplied mat is \n");
// printf("multiplied mat is %d%d\n",M,N);


for (int i = 0; i < M; ++i)
{
	for (int j = 0; j < N; ++j)
	{
		printf("%d\t", C[i][j]);
	}
	printf("\n"); 
}

printf("Time taken by parallel execution %f s \n",run_time);
// return 0;









// clock_t t; 
// t = clock(); 

double t2= omp_get_wtime();
for (i=0; i<M; i++)
{
for (j=0; j<N; j++)
{
tmp = 0.0;
for( k=0; k<P; k++)
{
/* C(i,j) = sum(over k) A(i,k) * B(k,j)*/
tmp += A[i][k] * B[k][j];
}
S[i][j] = tmp;
}
} 
// t = clock() - t; 
double time_taken = omp_get_wtime()-t2 ;
    printf("Time taken by sequential execution %f s \n",time_taken);

}