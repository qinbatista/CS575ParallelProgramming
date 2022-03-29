//g++ -Xpreprocessor -fopenmp SimpleOpenMPExperiment.cpp -lomp -o SimpleOpenMPExperiment -DNUMT=6 -DNUMS=12
#include <omp.h>
#include <stdio.h>
#include <math.h>

#ifndef NUMT
#define NUMT    4// number of threads to use
#endif

#define SIZE    128*128

#define NUMTRIES    10// how many times to run the timing -- you get to decide


float A[SIZE];
float B[SIZE];
float C[SIZE];

int
main( )
{
#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
#endif

	// inialize the arrays:
	for( int i = 0; i < SIZE; i++ )
	{
		A[i] = 1.;
		B[i] = 2.;
	}
    for( int thread_idx = 1; thread_idx <= NUMT; thread_idx++ )
    {
        omp_set_num_threads( thread_idx );
        // fprintf( stderr, "Using %d threads\n", thread_idx );
        double maxMegaMults = 0.;
        for( int t = 0; t < NUMTRIES; t++ )
        {
                double time0 = omp_get_wtime( );

                #pragma omp parallel for
                for( int i = 0; i < SIZE; i++ )
                {
                        C[i] = A[i] * B[i];
                }

                double time1 = omp_get_wtime( );
                double megaMults = (double)SIZE/(time1-time0)/1000000.;
                if( megaMults > maxMegaMults )
                        maxMegaMults = megaMults;
        }
        printf( "Using %d threads:Peak Performance = %8.2lf MegaMults/Sec\n", thread_idx, maxMegaMults );
    }
    // note: %lf stands for "long float", which is how printf prints a "double"
    //        %d stands for "decimal integer", not "double"
    return 0;
}