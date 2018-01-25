/******************************************************************************
* FILE: omp_getEnvInfo.c
* DESCRIPTION:
*   OpenMP Example - Get Environment Information - C/C++ Version
*   The master thread queries and prints selected environment information.
* AUTHOR: Blaise Barney  7/06
* LAST REVISED: 07/12/06
******************************************************************************/

#include <omp.h> //OpenMP API
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, tid, procs, maxt, inpar, dynamic, nested; //Declaration of Variables

/* Start parallel region */
#pragma omp parallel private(nthreads, tid) //OpenMP Directive
  {

  /* Obtain thread number */
  tid = omp_get_thread_num();

  /* Only master thread does this */
  if (tid == 0) 
    {
    printf("Thread %d getting environment info...\n", tid);

    /* Get environment information */
    procs = omp_get_num_procs(); //# of Processors
    nthreads = omp_get_num_threads(); // # of Threads
    maxt = omp_get_max_threads(); // Max # of Threads
    inpar = omp_in_parallel(); // Returns whether machine is Parallel or not
    dynamic = omp_get_dynamic(); // Returns whether dynamic threads are enable
    nested = omp_get_nested(); // Returns wheather Nested threads are enable

    /* Print environment information */
    printf("Number of processors = %d\n", procs);
    printf("Number of threads = %d\n", nthreads);
    printf("Max threads = %d\n", maxt);
    printf("In parallel? = %d\n", inpar);
    printf("Dynamic threads enabled? = %d\n", dynamic);
    printf("Nested parallelism enabled? = %d\n", nested);

    }

  }  /* Done */

}