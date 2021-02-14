

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <time.h>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iterator>
#include <vector>

#define THREAD 256

#include <bits/stdc++.h>
#include <chrono>


using namespace std::chrono;

using namespace std;

__global__
void markPrimes(int step,int k, char *d_primes,  int n) {
	 int index = blockIdx.x*blockDim.x + threadIdx.x;
	
	 int begin = step * step;
	if (begin == 0){
		begin = step*step;
	}
	 int end = (index + 1) * k;
	for ( int i = begin; i <= end; i += step) //begin + step
	{
		if (i<n) 
			d_primes[i] = 0;
			
	}


}



int main(int argc, char *argv[]) {
	 int n, N, k, blocks;
	 char *primes, *d_primes;

	n = atoi(argv[1]); 
	N = ceill((long double)sqrt(n)); 
	k = ceill((long double)n / (long double)N); 
	blocks = ceill((long double)N / (long double)THREAD);

	primes = ( char*)malloc(n*sizeof(char));
	for (int i = 0; i < n; i++)
	{
			
			if (i%2!=0 || i==2 )
		    primes[i] = 1;
	}

	cudaMalloc(&d_primes, n * sizeof(char));
	cudaMemcpy(d_primes, primes, n * sizeof(char), cudaMemcpyHostToDevice);
	clock_t begin = clock();
	for (int i = 2; i <= N; i++)
	{
		if (primes[i])
			{
			    markPrimes << <blocks, THREAD >> > (i, k, d_primes, n);
			    }
		
		
	}

	
		cudaMemcpy(primes, d_primes, n * sizeof(char), cudaMemcpyDeviceToHost);

		clock_t end = clock();

	
	primes[0] = 0;
	primes[1] = 0;
	 int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (primes[i])
		{
			//cout << i << "\t";
			count++;
		}
	}
	cout << "\nNumber of primes less than " << n << ": " << count << endl;
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	cout << "The running time is " << time_spent << " milliseconds." << endl;


	cudaFree(d_primes);
}