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
 *
 * @file timer.c
 */

/* timer functions */
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

/* #define USE_GETRUSAGE */

double second()
{
    double t;
#ifdef USE_GETRUSAGE
    struct rusage ru;
 
    getrusage(RUSAGE_SELF, &ru);
    t = (double)(ru.ru_utime.tv_sec+ru.ru_stime.tv_sec) + 
      ((double)(ru.ru_utime.tv_usec+ru.ru_stime.tv_usec))/1.0e6 ;
    return t ;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    t = (double)(tv.tv_sec) + ((double)(tv.tv_usec))/1.0e6;
    return t ;
#endif
}

static double start_time;

double start_timer()
{
    start_time = second();
    return start_time;
}

double lap_time(char *msg)
{
    double t;
    t = second();
    if (msg)
      printf("%s %f\n", msg, t-start_time);
    return t;
}

