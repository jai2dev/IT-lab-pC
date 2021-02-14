#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>
int seq_linear(int arr[], int n, int ele) //sequential linear search
{for (int a = 0; a < n; a++)
	{    if (arr[a] == ele) 
		{ return a;
 }
 } 
    return -1;}

 int par_linear(int arr[], int n, int ele) //parallel linear search
 { int ret = -1; 
 #pragma omp parallel num_threads(4) 
 {      int tid = omp_get_thread_num();
       #pragma omp for           
       for (int a = 0; a < n; a++)         
         { if (arr[a] == ele){      
         #pragma omp critical      
         {           ret = a;     
          }
           }
                      } 
                           } return ret;   
                            }


  void merge(int arr[], int l, int m, int r) //Merge function to sort the array using Merge Sort.
{ int i, j, k;
 int n1 = m - l + 1; 
 int n2 = r - m; 
 int L[n1], R[n2]; 
 for (i = 0; i < n1; i++) 
 	L[i] = arr[l + i]; 
 	for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
 	 i = 0; j = 0; k = l;
 	  while (i < n1 && j < n2) 
 	  	{      if (L[i] <= R[j])      
 	  		{  arr[k] = L[i]; i++;      } 
 	  		     else      { arr[k] = R[j]; j++;      }    
 	  		       k++; } 
 	  		       while (i < n1) 
 	  		       	{      arr[k] = L[i];  
 	  		       	    i++;  
 	  		       	        k++; }
 while (j < n2) 
 { arr[k] = R[j]; 
 j++; 
 k++; }
}
 void mergeSort(int arr[], int l, int r) // Recursive Merge Sort function to sort the array
 {    if (l < r)   
  {         int m = l + (r - l) / 2;    
       mergeSort(arr, l, m);   
             mergeSort(arr, m + 1, r); 
             merge(arr, l, m, r);    }
         }
             int seq_binary(int arr[], int n, int ele) // sequential binary search
             { int l = 0, r = n-1, mid; 
             	while (r-l>1) 
             		{ mid = l + (r-l)/2; 
             			if (arr[mid] == ele) 
             			{
 return mid; }
  if (arr[mid] > ele)
   {  r = mid; } 
   else {      l = mid; }  
   } 
   if(arr[l] == ele) {  
       return l; } 
       if(arr[r] == ele)
        {      return r; } 
        return -1;}
        int main()
        {    srand(time(0));
            long long int n; // number of elements    
            printf("Enter the number of elements: ");
    scanf("%lld", &n);   
     int arr[n];    
     for (long long int i = 0; i < n; i++) arr[i] = rand()%n;
     //populating the array randomly   
      int key, index;    
      printf("\nEnter the element to be searched: ");   
       scanf("%d", &key);    double t1,t2;
       // timestamps to calculate time taken   
        t1=omp_get_wtime();    
        index = seq_linear(arr, n, key);
         // sequential linear search   
          t2=omp_get_wtime();   
           printf("\nTIME TAKEN FOR SEQUENTIAL LINEAR SEARCH: %lf",t2-t1); 
              if (index == -1){ printf("\nElement not present!");    } 
                 else{ printf("\nElement found at: %d", index);    }   
                  t1=omp_get_wtime(); 
                     index = par_linear(arr, n, key); 
                     //parallel linear search    
                     t2=omp_get_wtime();
    printf("\n\nTIME TAKEN FOR PARALLEL LINEAR SEARCH: %lf",t2-t1); 
       if (index == -1)   
        {         printf("\nElement not present!");    }  
          else{         printf("\nElement found at: %d", index);    } 
             mergeSort(arr, 0, n-1); //sorting to apply binary search
                 t1=omp_get_wtime();    
                 index = seq_binary(arr, n, key); 
                 //sequential binary search    
                 t2=omp_get_wtime();   
                  printf("\n\nTIME TAKEN FOR SEQUENTIAL BINARY SEARCH: %lf",t2-t1);  
                   if (index == -1)    
                   	{         printf("\nElement not present!\n");    }  
                   	  else{ printf("\nElement found at: %d\n", index);    }}
                   	  