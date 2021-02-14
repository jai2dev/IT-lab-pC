#include<stdio.h>
#include <omp.h>

int main()
{
int n,sum=0;
	printf("enter total nums of elements in array c and b \n");
	scanf("%d",&n);

	int c[n];
		printf("enter the elements in array c \n");
		for (int i = 0; i < n; ++i)
		{
			scanf("%d",&c[i]);
		}

    int b[n],a[n];
		printf("enter the elements in array b \n");
		for (int i = 0; i < n; ++i)
		{
			scanf("%d",&b[i]);
		}

	#pragma omp parallel num_threads(4)
		{
	#pragma omp for reduction(+:sum)
		for (int i = 0; i < n; ++i)
		{
			a[i]= b[i] +c[i];
		}
		// int ls=sum;
	}
printf("elements in array a are\n " );
for (int i = 0; i < n; ++i)
{
	/* code */printf("%d\n",a[i] );
}
	


	return 0;
}