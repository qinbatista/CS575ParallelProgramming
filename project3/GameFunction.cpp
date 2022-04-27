#include "GameFunction.h"
#include "GameMath.h"
#include "GameParellelBarrier.h"
// starting date and time:
int NowMonth = 0;   // 0 - 11
int NowYear = 2021; // 2022 - 2027
// starting state (feel free to change this if you want):
float NowPrecip; // inches of rain per month
float NowTemp;   // temperature this month
// starting state (feel free to change this if you want):
float NowHeight = 1; // grain height in inches
int NowNumDeer = 1;  // number of deer in the current population
int NowHunter = 0;   // number of hunters in the current population
const float GRAIN_GROWS_PER_MONTH = 9.0;
const float ONE_DEER_EATS_PER_MONTH = 1.0;

const float AVG_PRECIP_PER_MONTH = 7.0; // average
const float AMP_PRECIP_PER_MONTH = 6.0; // plus or minus
const float RANDOM_PRECIP = 2.0;        // plus or minus noise

const float AVG_TEMP = 60.0;    // average
const float AMP_TEMP = 20.0;    // plus or minus
const float RANDOM_TEMP = 10.0; // plus or minus noise

const float MIDTEMP = 40.0;
const float MIDPRECIP = 10.0;

unsigned int seed = 0;
float dear_starving = 0.0;
void TemperatureAndPrecipitation()
{
    float ang = (30. * (float)NowMonth + 15.) * (M_PI / 180.);

    float temp = AVG_TEMP - AMP_TEMP * cos(ang);
    NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
    NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
    if (NowPrecip < 0.)
        NowPrecip = 0.;
    EarthTime();
}
void EarthTime()
{
    NowMonth++;
    if (NowMonth == 12)
    {
        NowYear++;
        NowMonth = 0;
    }
}

void Deer()
{
    while (NowYear < 2027)
    {
        float tempFactor = exp(-SQR((NowTemp - MIDTEMP) / 10.));
        float precipFactor = exp(-SQR((NowPrecip - MIDPRECIP) / 10.));

        int nextNumDeer = NowNumDeer;
        int carryingCapacity = (int)(NowHeight);
        if (nextNumDeer < carryingCapacity)
            nextNumDeer++;
        else if (nextNumDeer > carryingCapacity)
            nextNumDeer--;
        nextNumDeer = nextNumDeer-NowHunter;
        if (nextNumDeer < 0)
            nextNumDeer = 0;
            // std::cout << "Deer" << std::endl;
#pragma omp barrier
        WaitBarrier();
        NowNumDeer = nextNumDeer;
#pragma omp barrier
        WaitBarrier();
#pragma omp barrier
        WaitBarrier();
    }
}
void Grain()
{
    while (NowYear < 2027)
    {
        float tempFactor = exp(-SQR((NowTemp - MIDTEMP) / 10.));
        float precipFactor = exp(-SQR((NowPrecip - MIDPRECIP) / 10.));

        float nextHeight = NowHeight;
        nextHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        nextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        if (nextHeight < 0.)
            nextHeight = 0.;
#pragma omp barrier
        WaitBarrier();
        NowHeight = nextHeight;

#pragma omp barrier
        WaitBarrier();
#pragma omp barrier
        WaitBarrier();
    }
}
void Watcher()
{
    while (NowYear < 2027)
    {
        // std::cout << "Watcher" << std::endl;
#pragma omp barrier
        WaitBarrier();
#pragma omp barrier
        WaitBarrier();
        // std::cout <<"NowMonth," <<(NowYear-2021)*12+ NowMonth+1 << ",    NowHeight," << NowHeight << ",  NowNumDeer," << NowNumDeer << ",    NowTemp," <<(5./9.)*(NowTemp-32) <<",NowPrecip,"<<NowPrecip*2.54<< std::endl;
        std::cout <<(NowYear-2021)*12+ NowMonth+1 << "," << NowHeight << "," << NowNumDeer << "," <<(5./9.)*(NowTemp-32) <<","<<NowPrecip*2.54<<","<<NowHunter<< std::endl;
        TemperatureAndPrecipitation();
#pragma omp barrier
        WaitBarrier();
    }
}
void MyAgent()
{
    while (NowYear < 2027)
    {
        // std::cout << "Watcher" << std::endl;
        // int NextHunter = NowHunter;
        // if(NowNumDeer>=3)
        // {
        //     NextHunter++;
        // }
        // else
        // {
        //     NextHunter--;
        // }
        // if(NextHunter<0)
        // {
        //     NextHunter=0;
        // }
#pragma omp barrier
        WaitBarrier();
        // NowHunter = NextHunter;
#pragma omp barrier
        WaitBarrier();

#pragma omp barrier
        WaitBarrier();
    }
}