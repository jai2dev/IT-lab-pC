#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>



void merge(int arr[], int l, int m, int r)
{int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];
	for (i = 0; i < n1; i++)L[i] = arr[l + i];
		for (j = 0; j < n2; j++)R[j] = arr[m + 1 + j];
			i = 0;j = 0;k = l;
		while (i < n1 && j < n2)
		 {if (L[i] <= R[j]) 
		 	{arr[k] = L[i];
		 		i++;}
else {arr[k] = R[j];
	j++;}
	k++;}
	while (i < n1) 
		{arr[k] = L[i];
			i++;
			k++;
		}
		while (j < n2) {
			arr[k] = R[j];
			j++;
			k++;
		}
	}
	void mergeSort(int arr[], int l, int r)
	{if (l < r) 
		{int m = l + (r - l) / 2;
			mergeSort(arr, l, m);
			mergeSort(arr, m + 1, r);

			merge(arr, l, m, r);
		}
	}
int seq_binary(int arr[], int n, int ele)
{
	int l = 0, r = n-1, mid;
	while (l < r)
		{mid = l + (r-l)/2;
		if (arr[mid] == ele)

			{return mid;}
		if (arr[mid] > ele)
			{r = mid-1;}
		else{l = mid+1;}
	}
	if (arr[l] == ele)
		{return l;}
	return -1;
}
int par_binary(int arr[], int l, int r, int ele)
{if (l > r)
	{return -1;}
	if (l == r){if (arr[l] == ele){
return l;}
return -1;}
int mid = l + (r-l)/2;
if (arr[mid] == ele)
	{return mid;}
int index= -1;
#pragma omp parallel num_threads(4)
{
#pragma omp single
	{if (arr[mid] > ele){
	#pragma omp task
		{
			index = par_binary(arr, l, mid-1, ele);
		}
	}
	else{
	#pragma omp task
		{
			index = par_binary(arr, mid+1, r, ele);
		}
	}
	#pragma omp taskwait
}
}
return index;}
int main()
{srand(time(0));
long long int n;//number of elements
printf("Enter the number of elements: ");
scanf("%lld", &n);
int arr[n];
for (long long int i = 0; i < n; i++)
{arr[i] = rand()%n;
//randomly populating array
}
int key, index;
printf("\nEnter the element to be searched: ");
scanf("%d", &key);

double t1,t2;
mergeSort(arr,0,n-1); //sorting array to apply binary search
t1=omp_get_wtime();
index= seq_binary(arr, n, key);
//sequential binary search
t2=omp_get_wtime();
printf("\n\nTIME TAKEN FOR SEQUENTIAL BINARY SEARCH: %lf",t2-t1);
if (index == -1){printf("\nElement not present!\n");}
else{printf("\nElement found at: %d", index);}
t1=omp_get_wtime();
index = par_binary(arr, 0, n-1, key);
 // parallel binary search
t2=omp_get_wtime();
printf("\n\nTIME TAKEN FOR PARALLEL BINARY SEARCH: %lf",t2-t1);
if (index == -1){printf("\nElement not present!\n");
}
else{printf("\nElement found at: %d\n", index);}}