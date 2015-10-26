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
/* parallel for 008:
 * check implicit barrier at end of parallel for section.
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	*buf;


void clear()
{
  int	i;

  for (i=0; i<thds; i++) {
    buf[i] = -1;
  }
}

main ()
{
  int	lp, finish;

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

  finish = 0;
  clear ();
  #pragma omp parallel for schedule (static,1)
  for (lp=0; lp<thds; lp++) {
    int	id = omp_get_thread_num ();

    /* make barrier, and thread 1-x delay any sec from thread 0 */
    if (id == 0) {
      finish = 1;
    } else {
      while (finish == 0) {
        #pragma omp flush
      }
      waittime (1);
    }
    buf[id] = omp_get_thread_num ();
    #pragma omp flush
  }

  for (lp=0; lp<thds; lp++) {
    if (buf[lp] == -1) {
      errors += 1;
    }
  }


  finish = 0;
  clear ();
  #pragma omp parallel for schedule (dynamic,1)
  for (lp=0; lp<thds; lp++) {
    int	id = omp_get_thread_num ();

    barrier (thds);

    /* make barrier, and thread 1-x delay any sec from thread 0 */
    if (omp_get_thread_num () == 0) {
      finish = 1;
    } else {
      while (finish == 0) {
        #pragma omp flush
      }
      waittime (1);
    }
    buf[id] = omp_get_thread_num ();
    #pragma omp flush
  }

  for (lp=0; lp<thds; lp++) {
    if (buf[lp] == -1) {
      errors += 1;
    }
  }



  clear ();
  #pragma omp parallel for schedule (guided,1)
  for (lp=0; lp<thds*4; lp++) {
    int	id = omp_get_thread_num ();

    /* make barrier, and thread 1-x delay any sec from thread 0 */

    buf[id] = -2;
    #pragma omp flush

    if (id != 0) {
      waittime (1);
    }

    buf[id] = id;
    #pragma omp flush
  }

  for (lp=0; lp<thds; lp++) {
    if (buf[lp] == -2) {
      errors += 1;
    }
  }


  if (errors == 0) {
    printf ("parallel for 008 : SUCCESS\n");
    return 0;
  } else {
    printf ("parallel for 008 : FAILED\n");
    return 1;
  }
}
