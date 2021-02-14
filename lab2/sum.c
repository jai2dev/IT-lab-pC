#include<stdio.h>
#include <omp.h>

int main()
{
int n,sum=0;
	printf("enter total nums of elements in array \n");
	scanf("%d",&n);

	int array[n];
		printf("enter the elements in array \n");
		for (int i = 0; i < n; ++i)
		{
			scanf("%d",&array[i]);
		}

	#pragma omp parallel num_threads(4)
		{
	#pragma omp for reduction(+:sum)
		for (int i = 0; i < n; ++i)
		{
			sum= sum +array[i];
		}
		// int ls=sum;
	}

	printf("sum is %d\n",sum );


	return 0;
}