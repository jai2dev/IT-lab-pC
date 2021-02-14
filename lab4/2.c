#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
	int n,i,j;
	double t1_s,t2_s,t1_p,t2_p;
	printf("Enter the value n : ");
	scanf("%u",&n);
	int m[n][n];
	int rsum[n];
	int csum[n];
	srand(time(0));
	printf("matrix:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			int k=(rand())%10000;
			m[i][j]=k;
			printf("%d ",k);
		}
		printf("\n");
	}

	//sequential
	t1_s=omp_get_wtime();
	
	for(i=0;i<n;i++)
	{
		int temp=0;
		for(j=0;j<n;j++)
			temp+=m[i][j];
		
		rsum[i]=temp;
	}

	for(i=0;i<n;i++)
	{
		int temp=0;
		for(j=0;j<n;j++)
			temp+=m[j][i];
		
		csum[i]=temp;
	}

	t2_s=omp_get_wtime();
	int temp;
	//parallel
	t1_p=omp_get_wtime();
	#pragma omp parallel shared(n)
	{
		#pragma omp for schedule(static,10) private(i,j,temp)
			for(i=0;i<n;i++)
			{
				temp=0;
				for(j=0;j<n;j++)
				temp+=m[i][j];
				
				rsum[i]=temp;
			}

		#pragma omp for schedule(static,10) private(i,j,temp)
			for(i=0;i<n;i++)
			{
				temp=0;
				for(j=0;j<n;j++)
					temp+=m[j][i];
			
				csum[i]=temp;
			}
	}
	
	t2_p=omp_get_wtime();
	
	//results
	printf("Row Sum : \n");
	for(i=0;i<n;i++)
	{
		printf("Row %d: %d \n", i,rsum[i]);
	}
	printf("\nColumn Sum : \n");
	for(i=0;i<n;i++)
	{
	printf("Column %d : %d \n", i,csum[i]);
	}
	printf("\nTime taken for sequential execution is %f s \n",t2_s-t1_s);
	printf("\nTime taken for parallel execution is %f s \n",t2_p-t1_p);
	return 0;
}