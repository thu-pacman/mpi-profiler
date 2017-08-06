/************************************************************

This file implements linux timer function with gettimeofday.

*************************************************************/
#include "timer.h"
#include <sys/time.h>
#include <stdlib.h>

/**************************************************************
						void WTIME(double);
**************************************************************/

inline void _wtime(double *t)
{
  struct timeval tv;
  gettimeofday(&tv, 0);
  *t = tv.tv_sec + 1.0e-6*tv.tv_usec;
}

/*****************************************************************/
/******         E  L  A  P  S  E  D  _  T  I  M  E          ******/
/*****************************************************************/
inline double _elapsed_time( void )
{
    double t;
    _wtime( &t );
    return( t );
}
inline double current_time(void)
{
    return _elapsed_time();
}

double start[64], elapsed[64];

/*****************************************************************/
/******            T  I  M  E  R  _  C  L  E  A  R          ******/
/*****************************************************************/
inline void _timer_clear( int n )
{
    elapsed[n] = 0.0;
}


/*****************************************************************/
/******            T  I  M  E  R  _  S  T  A  R  T          ******/
/*****************************************************************/
inline void _timer_start( int n )
{
    start[n] = _elapsed_time();
}


/*****************************************************************/
/******            T  I  M  E  R  _  S  T  O  P             ******/
/*****************************************************************/
inline void _timer_stop( int n )
{
    double t, now;

    now = _elapsed_time();
    t = now - start[n];
    elapsed[n] += t;

}

/*****************************************************************/
/******            T  I  M  E  R  _  R  E  A  D             ******/
/*****************************************************************/
inline double _timer_read( int n )
{
    return( elapsed[n] );
}
