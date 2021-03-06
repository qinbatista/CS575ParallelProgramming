// g++ -Xpreprocessor -fopenmp  -L/usr/local/lib -lomp  *.cpp -o main -DNUMT=4
#include <omp.h>
#include <stdio.h>
#include <math.h>

#ifndef NUMT
#define NUMT    4// number of threads to use
#endif

#define SIZE    128*128*128

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
		for( int trailer = 1; trailer < NUMTRIES+1; trailer++)
		{
			for( int t = 0; t < trailer; t++ )
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
			printf("%d	threads	%d	trailer:Peak Performance =	%8.2lf	MegaMults/Sec\n", thread_idx,trailer, maxMegaMults );
		}
	}
	// note: %lf stands for "long float", which is how printf prints a "double"
	//        %d stands for "decimal integer", not "double"
	return 0;
}
void list_append_float(list