
#include<iostream>
#include <omp.h>
#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

#ifndef NUMNODES
#define NUMNODES  100
#endif

#ifndef NUMT
#define NUMT      6
#endif

float Height( int, int );	// function prototype

const float N = 2.5f;
const float R = 1.2f;

int main( int argc, char *argv[ ] )
{
    // . . .
    omp_set_num_threads(NUMT);
    // the area of a single full-sized tile:
    // (not all tiles are full-sized, though)

    float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

    // sum up the weighted heights into the variable "volume"
    double volume = 0;
    double time0 = omp_get_wtime( );
    // using an OpenMP for-loop and a reduction:
    #pragma omp parallel for collapse(2) default(none) shared(fullTileArea) reduction(+:volume)
    for( int iv = 0; iv < NUMNODES; iv++ )
    {
        for( int iu = 0; iu < NUMNODES; iu++ )
        {
            // int iu = i % NUMNODES;
            // int iv = i / NUMNODES;
            float z = Height( iu, iv );
            volume += fullTileArea*z;
        }
    }
    double time1 = omp_get_wtime( );
    volume = volume- fullTileArea; // reduce 4 corner's areas 0.25 *fullTileArea *4
    volume = volume- (NUMNODES-1)*fullTileArea*2; // reduce 4 edge's areas (n-1)*(0.5*fullTileArea)*2
    std::cout <<"NUMNODES= "<< NUMNODES <<" NUMT= "<<NUMT<< " volume= " << volume<<" megatrials/sec= "<<(double)NUMNODES*NUMNODES / ( time1 - time0 ) / 1000000. << std::endl;
}

float Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
    float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
    float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

    float xn = pow( fabs(x), (double)N );
    float yn = pow( fabs(y), (double)N );
    float rn = pow( fabs(R), (double)N );
    float r = rn - xn - yn;
    if( r <= 0. )
            return 0.;
    float height = pow( r, 1./(double)N );
    return height;
}