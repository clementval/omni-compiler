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
/* error case of for 021:
 * schedule が複数回指定された場合にエラーになることを確認
 */

#include <omp.h>

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
  int	lp, lp2;

  int	err = 0;


  for (lp=0; lp*s<LOOPNUM; lp++) {
    for (lp2=0; lp2<s; lp2++) {
      if (LOOPNUM<=lp*s+lp2) {
	goto LOOPEND;
      }
      if (buf[lp*s+lp2] != lp%thds) {
	err += 1;
      }
    }
  }
 LOOPEND:
  if (buf[LOOPNUM] != -1) {
    err += 1;
  }

  return err;
}


main ()
{
  int	lp;

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
  #pragma omp parallel
  {
    #pragma omp for schedule (static) schedule (dynamic)
    for (lp=0; lp<LOOPNUM; lp++) {
      buf[lp] = omp_get_thread_num ();
    }
  }

  printf ("err_for 021 : FAILED, can not compile this program.\n");
  return 1;
}
