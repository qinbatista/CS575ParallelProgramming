//g++ -Xpreprocessor -fopenmp PerformanceCheck.cpp -lomp -o PerformanceCheck -DNUMT=6 -DNUMS=12
#include<omp.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NUMT
#define NUMT    8
#endif

#ifndef NUMS
#define NUMS    32
#endif

int main(int argc, char *argv[]) 
{
   fprintf(stderr,"NUMT = %d, NUMS = %d \n", NUMT,NUMS);
}




