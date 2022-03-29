//g++ -Xpreprocessor -fopenmp BasicTiming.cpp -lomp -o BasicTiming
#include<omp.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char ** argv) 
{
    double time0 = omp_get_wtime();
    double time1 = omp_get_wtime();
    fprintf(stderr,"Elapsed time = %10.2lf microseconds\n", 1000000. * ( time1-time0 ) );
}



