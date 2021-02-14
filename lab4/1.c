#include<stdio.h>
#include<omp.h>

#include <time.h>


int fibo(int n);
int fibbo(int n);


int main(void)
{
int n,fib;
double t1,t2;
printf("Enter the value of n:\n");
scanf("%d",&n);
t1=omp_get_wtime();
#pragma omp parallel shared(n)
{
#pragma omp single
{
fib=fibo(n);
}
}
t2=omp_get_wtime();
printf("Fib is %d\n",fib);
printf("Time taken by parallel execution %f s \n",t2-t1);

clock_t t; 
t = clock();
fibbo(n);
t = clock() - t; 
double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Time taken by sequential execution %f s \n",time_taken);
return 0;
}



int fibbo(int n)
{  if (n<=2)
	return n;

	return fibbo(n-1)+fibbo(n-2);

}

int fibo(int n)
{
int a,b;
if(n<2)
return n;
else
{
#pragma omp task shared(a) 
{
// printf("Task Created by Thread %d\n",omp_get_thread_num());
a=fibo(n-1);
// printf("Task Executed by Thread %d \ta=%d\n",omp_get_thread_num(),a);
}
#pragma omp task shared(b)
{
// printf("Task Created by Thread %d\n",omp_get_thread_num());
b=fibo(n-2);
// printf("Task Executed by Thread %d \tb=%d\n",omp_get_thread_num(),b);
}
#pragma omp taskwait
return a+b;
}
}