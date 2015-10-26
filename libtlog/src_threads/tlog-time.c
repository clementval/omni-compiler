/* 
 * $TSUKUBA_Release: Omni Compiler Version 0.9.1 $
 * $TSUKUBA_Copyright:
 *  Copyright (C) 2010-2014 University of Tsukuba, 
 *  	      2012-2014  University of Tsukuba and Riken AICS
 *  
 *  This software is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 published by the Free Software Foundation.
 *  
 *  Please check the Copyright and License information in the files named
 *  COPYRIGHT and LICENSE under the top  directory of the Omni Compiler
 *  Software release kit.
 *  
 *  * The specification of XcalableMP has been designed by the XcalableMP
 *    Specification Working Group (http://www.xcalablemp.org/).
 *  
 *  * The development of this software was partially supported by "Seamless and
 *    Highly-productive Parallel Programming Environment for
 *    High-performance computing" project funded by Ministry of Education,
 *    Culture, Sports, Science and Technology, Japan.
 *  $
 */
/*
 *  TIMER routine
 */
#include <stddef.h>


#if !defined(__TTIME_GETTIMEOFDAY__) || !defined(__TTIME_MPI_WTIME__)

/**  BEGINNING OF MACHINE-DEPENDENT PART  **/

/***  SUN SOLARIS  ***/
#if defined(OMNI_OS_SOLARIS)
#include <sys/time.h>

#ifdef __GNUC__
#define USE_LL
#endif

#if __STDC__ - 0 == 0 && !defined(_NO_LONGLONG)
#define USE_LL
#endif

double
tlog_timestamp()
{
#ifdef USE_LL
    return ((double)gethrtime()) * .000000001;
#else
    hrtime_t hrT = gethrtime();
    return hrT._d * .000000001;
#endif /* USE_LL */
}

/***  SGI IRIX  ***/
#elif defined(OMNI_OS_IRIX)
#include <time.h>

double
tlog_timestamp()
{
    struct timespec t1;
    clock_gettime(CLOCK_SGI_CYCLE, &t1);
    return (double)t1.tv_sec + (double)t1.tv_nsec * .000000001;
}

/***  gettimeofday(2)  ***/
#else
#include <sys/time.h>

double
tlog_timestamp()
{
    struct timeval t1;
    gettimeofday(&t1, NULL);
    return (double)t1.tv_sec + (double)t1.tv_usec * .000001;
}

#endif

/**  END OF MACHINE-DEPENDENT PART  **/

/**  BEGINNING OF MACHINE-INDEPENDENT PART  **/

#elif defined(__TTIME_GETTIMEOFDAY__)

#include <sys/time.h>

double
tlog_timestamp()
{
    struct timeval t1;
    gettimeofday(&t1, NULL);
    return (double)t1.tv_sec + (double)t1.tv_usec * .000001;
}

#else /** defined(__TTIME_MPI_WTIME__) **/

/*
 *  TIMER routine for MPI
 */

double
tlog_timestamp()
{
    return MPI_Wtime();
}

#endif /** !defined(__TTIME_GETTIMEOFDAY__) || !defined(__TTIME_MPI_WTIME__) **/

/**  END OF MACHINE-INDEPENDENT PART  **/
