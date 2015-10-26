static char rcsid[] = "$Id$";
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
/* flush 005:
 * check implicit flush at end of critical section
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;

int	a, b;


void
clear ()
{
  a = 0;
  b = 0;
}


void
func_flush ()
{
  a = 0;
  #pragma omp barrier

  if (omp_get_thread_num () == 0) {
    waittime (1);
    #pragma omp critical
    a = 1;
  } else {
    while (a == 0) {
      #pragma omp critical
      {
      }
    }
  }
}


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  clear ();
  #pragma omp parallel
  {
    a = 0;
    #pragma omp barrier

    if (omp_get_thread_num () == 0) {
      waittime (1);
      #pragma omp critical
      a = 1;
    } else {
      while (a == 0) {
	#pragma omp critical
	{
	}
      }
    }
  }


  clear ();
  #pragma omp parallel
  func_flush ();


  if (errors == 0) {
    printf ("flush 005 : SUCCESS\n");
    return 0;
  } else {
    printf ("flush 005 : FAILED\n");
    return 1;
  }
}
