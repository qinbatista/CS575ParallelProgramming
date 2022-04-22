#include <omp.h>
#include <iostream>
// Barrier variables
omp_lock_t Lock;
volatile int NumInThreadTeam;
volatile int NumAtBarrier;
volatile int NumGone;
void InitBarrier(int n)
{
    // std::cout << "InitBarrier" << std::endl;
    NumInThreadTeam = n;
    NumAtBarrier = 0;
    omp_init_lock(&Lock);
}
void WaitBarrier()
{
    // std::cout << "WaitBarrier" << std::endl;
    omp_set_lock(&Lock);
    {
        NumAtBarrier++;
        if (NumAtBarrier == NumInThreadTeam)
        {
            NumGone = 0;
            NumAtBarrier = 0;
            // let all other threads get back to what they were doing
            // before this one unlocks, knowing that they might immediately
            // call WaitBarrier( ) again:
            while (NumGone != NumInThreadTeam - 1)
                ;
            omp_unset_lock(&Lock);
            return;
        }
    }
    omp_unset_lock(&Lock);
    while (NumAtBarrier != 0)
        ; // this waits for the nth thread to arrive
#pragma omp atomic
    NumGone++; // this flags how many threads have returned
}