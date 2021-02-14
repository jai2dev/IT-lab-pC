#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
#define N 300
//int mat[300][300][3],mat_g[300][300],mat_y[300][300][3];
int mat[N*N*3],mat_g[N*N],mat_y[3*N*N];



int main()
{
	freopen("KittenRGB.txt","r",stdin);
// int mat[300][300][3],mat_g[300][300],mat_y[300][300][3];
//read data into a matrix of size 300*300
for(int i=0;i<3*N*N;i++)
{cin>>mat[i];}
//sequential
double start,end;
//rgb to gray scale
start=omp_get_wtime();
for(int i=0;i<300*300*3;i+=3)
{
	int R=mat[i];
int G=mat[i+1];
int B=mat[i+2];
mat_g[i]=(R*0.21)+(G*0.72)+(B*0.07);
mat_y[i]=(0.299*R)+(0.587*G)+(0.114*B);
mat_y[i+1]=(0.596*R)-(0.275*G)-(0.321*B);
mat_y[i+2]=(0.212*R)-(0.523*G)+(0.311*B);
}
end=omp_get_wtime();
cout<<"Total time taken by sequential= "<<(end-start)<<'\n';
//parallel//num_threads=2
start=omp_get_wtime();
#pragma omp parallel num_threads(2)
{
#pragma omp for
for(int i=0;i<N*N*3;i+=3)
{
int R=mat[i];
int G=mat[i+1];
int B=mat[i+2];
mat_g[i]=(R*0.21)+(G*0.72)+(B*0.07);
mat_y[i]=(0.299*R)+(0.587*G)+(0.114*B);
mat_y[i+1]=(0.596*R)-(0.275*G)-(0.321*B);
mat_y[i+2]=(0.212*R)-(0.523*G)+(0.311*B);
}
}
end=omp_get_wtime();
cout<<"Total time taken by 2 threads in parallel= "<<(end-start)<<'\n';
//num_threads=4
start=omp_get_wtime();
#pragma omp parallel num_threads(4)
{
#pragma omp for
for(int i=0;i<N*N*3;i+=3)
{int R=mat[i];
	int G=mat[i+1];
int B=mat[i+2];
mat_g[i]=(R*0.21)+(G*0.72)+(B*0.07);
mat_y[i]=(0.299*R)+(0.587*G)+(0.114*B);
mat_y[i+1]=(0.596*R)-(0.275*G)-(0.321*B);
mat_y[i+2]=(0.212*R)-(0.523*G)+(0.311*B);
}
}
end=omp_get_wtime();
cout<<"Total time taken by 4 threads in parallel= "<<(end-start)<<'\n';
//num_threads=8
start=omp_get_wtime();
#pragma omp parallel num_threads(8)
{
#pragma omp for
for(int i=0;i<N*N*3;i+=3)
{
int R=mat[i];
int G=mat[i+1];
int B=mat[i+2];
mat_g[i]=(R*0.21)+(G*0.72)+(B*0.07);
mat_y[i]=(0.299*R)+(0.587*G)+(0.114*B);
mat_y[i+1]=(0.596*R)-(0.275*G)-(0.321*B);
mat_y[i+2]=(0.212*R)-(0.523*G)+(0.311*B);
}
}
end=omp_get_wtime();
cout<<"Total time taken by 8 threads in parallel= "<<(end-start)<<'\n';
//num_threads=16
start=omp_get_wtime();
#pragma omp parallel num_threads(16)
{
#pragma omp for
for(int i=0;i<N*N*3;i+=3)
	{
		int R=mat[i];
int G=mat[i+1];
int B=mat[i+2];
mat_g[i]=(R*0.21)+(G*0.72)+(B*0.07);
mat_y[i]=(0.299*R)+(0.587*G)+(0.114*B);
mat_y[i+1]=(0.596*R)-(0.275*G)-(0.321*B);
mat_y[i+2]=(0.212*R)-(0.523*G)+(0.311*B);
}
}
end=omp_get_wtime();
cout<<"Total time taken by 16 threads in parallel= "<<(end-start)<<'\n';
freopen("output.txt","w",stdout);
cout<<"------------------------------------------conversion to Gray Scale format-----------------------------------------------\n";
for(int i=0;i<N*N;i++)
	cout<<mat_g[i]<<" ";
cout<<"\n\n\n------------------------------------------conversion to YIC format-----------------------------------------------\n";
for(int i=0;i<N*N*3;i++)
	cout<<mat_y[i]<<" ";
}