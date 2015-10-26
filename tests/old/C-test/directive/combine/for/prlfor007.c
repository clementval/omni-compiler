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
/* parallel for 007:
 * continue が通る事を確認
 */
#include <omp.h>
#include "omni.h"

#define	MAX_STRIDE	10
#define LOOPNUM		(MAX_STRIDE*thds)

int	thds;
int	*buf;


void
clear ()
{
  int lp;
  
  for (lp=0; lp<=LOOPNUM; lp++) {
    buf[lp] = -1;
  }
}


int
check_result (int s)
{
  int	lp, lp2, id;

  int	err = 0;


  for (lp=0; lp<LOOPNUM; ) {
    id = buf[lp];
    if (id<0 && thds<=id) {
      err += 1;
    }
    for (lp2=0; lp2<(LOOPNUM-lp); lp2++) {
      if (buf[lp+lp2] != id) {
	if (lp2+1<s) {
	  err += 1;
	}
      }
    }
    lp += lp2;
  }
  if (buf[LOOPNUM] != -1) {
    err += 1;
  }

  return err;
}


main ()
{
  int	lp;

  int	errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  buf = (int *) malloc (sizeof (int) * (LOOPNUM + 1));
  if (buf == NULL) {
    printf ("can not allocate memory.\n");
    exit (1);
  }
  omp_set_dynamic (0);

  clear ();
  #pragma omp parallel for schedule (runtime)
  for (lp=0; lp<LOOPNUM; lp++) {
    buf[lp] = omp_get_thread_num ();
    if (omp_get_thread_num () == 0)
      continue;
  }
  errors += check_result (1);

  #pragma omp parallel for schedule (static)
  for (lp=0; lp<LOOPNUM; lp++) {
    buf[lp] = omp_get_thread_num ();
    if (omp_get_thread_num () == 0)
      continue;
  }
  errors += check_result (1);

  #pragma omp parallel for schedule (dynamic)
  for (lp=0; lp<LOOPNUM; lp++) {
    buf[lp] = omp_get_thread_num ();
    if (omp_get_thread_num () == 0)
      continue;
  }
  errors += check_result (1);

  #pragma omp parallel for schedule (guided)
  for (lp=0; lp<LOOPNUM; lp++) {
    buf[lp] = omp_get_thread_num ();
    if (omp_get_thread_num () == 0)
      continue;
  }
  errors += check_result (1);

  if (errors == 0) {
    printf ("parallel for 007 : SUCCESS\n");
    return 0;
  } else {
    printf ("parallel for 007 : FAILED\n");
    return 1;
  }
}
