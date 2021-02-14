#include<stdio.h>
#include <omp.h>

int main()
{
int n,max=0;
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
	#pragma omp for reduction(max:max)
		for (int i = 0; i < n; ++i)
		{
			if (array[i]>=max)
			{
				/* code */max=array[i];
			}
		}
		// int ls=sum;
	}

	printf("max is %d\n",max);


	return 0;
}