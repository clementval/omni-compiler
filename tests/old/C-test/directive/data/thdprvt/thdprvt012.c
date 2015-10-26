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
/* threadprivate 012 :
 * threadprivateされた変数が for directiveが指定された
 * for ループのループカウンタに指定できる事を確認
 */

#include <omp.h>
#include "omni.h"


#define	STRIDE		100
#define LOOPNUM		(thds * STRIDE)

int	errors = 0;
int	thds, *buf, sum;

int	x;
#pragma omp threadprivate (x)


void
clear ()
{
  int	i;


  sum = 0;
  for (i=0; i<LOOPNUM; i++) {
    buf[x] = -1;
  }
}


void
check ()
{
  int	i;


  if (sum != LOOPNUM) {
    errors += 1;
  }
  for (i=0; i<LOOPNUM; i++) {
    if (buf[i] != i % thds) {
      errors += 1;
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
  buf = (int*) malloc (sizeof(int) * LOOPNUM);
  if (buf == NULL) {
    printf ("can not allocate memory\n");
    exit (1);
  }
  omp_set_dynamic (0);


  clear ();
  #pragma omp parallel
  {
    #pragma omp for schedule(static, 1)
    for (x=0; x<LOOPNUM; x++) {
      buf[x] = omp_get_thread_num ();
      #pragma omp critical
      sum += 1;
    }
  }
  check ();


  if (errors == 0) {
    printf ("threadprivate 012 : SUCCESS\n");
    return 0;
  } else {
    printf ("threadprivate 012 : FAILED\n");
    return 1;
  }
}
