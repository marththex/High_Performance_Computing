#include <stdio.h> 
#include <iostream> 
#define N 512
__global__ void kernel(int *a[], int n) 
{
	int index = threadIdx.x + blockDim.x * threadIdx.y;
	if(index < n)
	a[index] = &index;
	
}

int main(int argc, char **argv) 
{
	int n = N;
	if(argc == 2)
		n = atoi(argv[1]);
	else if (argc == 1)
		n = 512;
	else
		printf("Error # of Arguments");
	
	int* a = new int[n];
	int *dev_a[N];
	
	//allocate the memory on the GPU
	cudaMalloc( (void**)&dev_a, N * sizeof(int) );
	
	//creates a kernel
	kernel<<<1,N>>>(dev_a, n); 
	
	//copy the arrays 'a' to the GPU
	cudaMemcpy( dev_a, a, N * sizeof(int), cudaMemcpyHostToDevice );

	for (int i=0; i< n; i++) 
	{
		printf("%d\n",a[i]);
	}

	cudaFree( dev_a );
	delete[] a;
	
    return 0;
}
