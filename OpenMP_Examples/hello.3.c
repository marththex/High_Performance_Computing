/* An OpneMP  multithreaded program where each thread prints hello world. 
   Compile with an appropriate switch:
     cc -fopenmp file-name.c
*/

#include <omp.h> //OpenMP API
#include <stdio.h>

int main()
{
	printf("Hello from main.\n");
	omp_set_num_threads(20); // Requests a non-default number of threads.
	// Parallel region with the requested number of threads:	
	#pragma omp parallel //OpenMP Directive
	{
		// Runtime library function to return a thread ID:
		int myID = omp_get_thread_num();
		printf("hello(%d)", myID);
		printf("world(%d)\n", myID);
	}
}