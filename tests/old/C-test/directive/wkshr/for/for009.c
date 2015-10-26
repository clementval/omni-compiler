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
/* for 009:
 * check no implicit barrier at the end of for loop with nowait
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	*buf;


void
clear ()
{
  int lp;
  
  for (lp=0; lp<thds; lp++) {
    buf[lp] = -1;
  }
}


main ()
{
  int	lp, lp0;

  int	errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  buf = (int *) malloc (sizeof (int) * thds);
  if (buf == NULL) {
    printf ("can not allocate memory.\n");
    exit (1);
  }
  omp_set_dynamic (0);


  clear ();
  #pragma omp parallel
  {
    int	id = omp_get_thread_num ();
    int	i;

    #pragma omp for schedule (static,1) nowait
    for (lp=0; lp<thds; lp++) {
      barrier (thds);
      if (id == 0) {
	for (i=1; i<thds; i++) {
	  while (buf[i] != i) {
	    waittime(1); /* for SCASH */
	    #pragma omp flush
	  }
	}
	buf[id] = id;
	#pragma omp flush
      }
    }

    if (id != 0) {
      #pragma omp flush
      if (buf[0] != -1) {
        #pragma omp critical
	{
	  ERROR (errors);
	}
      }
      buf[id] = id;
      #pragma omp flush
    }
  }

  clear ();
  #pragma omp parallel
  {
    int	id = omp_get_thread_num ();
    int	i;

    #pragma omp for schedule (dynamic,1) nowait
    for (lp=0; lp<thds; lp++) {
      barrier (thds);
      if (id == 0) {
	for (i=1; i<thds; i++) {
	  while (buf[i] != i) {
	    waittime(1); /* for SCASH */
	    #pragma omp flush
	  }
	}
	buf[id] = id;
	#pragma omp flush
      }
    }

    if (id != 0) {
      #pragma omp flush
      if (buf[0] != -1) {
        #pragma omp critical
	{
	  ERROR (errors);
	}
      }
      buf[id] = id;
      #pragma omp flush
    }
  }


  lp0 = -1;
  clear ();
  #pragma omp parallel
  {
    int	id = omp_get_thread_num ();
    int	i;

    #pragma omp for schedule (guided,1) nowait
    for (lp=0; lp<thds*4; lp++) {
      if (lp == 0) {
	lp0 = id;
        #pragma omp flush
	for (i=0; i<thds; i++) {
	  if (id == i) {
	    continue;
	  }
	  while (buf[i] != i) {
	    waittime(1); /* for SCASH */
	    #pragma omp flush
	  }
	}
	buf[id] = id;
	#pragma omp flush
      }
    }

    while (lp0 == -1) {
      #pragma omp flush
    }
    if (id != lp0) {
      #pragma omp flush
      if (buf[lp0] != -1) {
        #pragma omp critical
	{
	  ERROR (errors);
	}
      }
      buf[id] = id;
      #pragma omp flush
    }
  }


  if (errors == 0) {
    printf ("for 009 : SUCCESS\n");
    return 0;
  } else {
    printf ("for 009 : FAILED\n");
    return 1;
  }
}
