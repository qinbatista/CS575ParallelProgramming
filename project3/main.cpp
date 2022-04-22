// g++ -Xpreprocessor -I/opt/homebrew/Cellar/libomp/14.0.0/include -fopenmp   -L/opt/homebrew/Cellar/libomp/14.0.0/lib -lomp  *.cpp -o main
#include <omp.h>
#include "GameFunction.h"
#include "GameParellelBarrier.h"

int main(int argc, char *argv[])
{
    omp_set_num_threads(4); // same as # of sections
    InitBarrier(4);
#pragma omp parallel sections
    {
#pragma omp section
        {
            // std::cout << "Deer" << std::endl;
            Deer();
        }
#pragma omp section
        {
            // std::cout << "Grain" << std::endl;
            Grain();
        }

#pragma omp section
        {
            // std::cout << "Watcher" << std::endl;
            Watcher();
        }

#pragma omp section
        {
            // std::cout << "MyAgent" << std::endl;
            MyAgent(); // your own
        }
    } // implied barrier -- all functions must return in order
      // to allow any of them to get past here
    return 1;
}
