#include<omp.h>ls
double time0 = omp_get_wtime();
double time1 = omp_get_wtime( );
// print( stderr, “Elapsed time = %10.2lf microseconds\n”, 1000000. * ( time1 – time0 ) );