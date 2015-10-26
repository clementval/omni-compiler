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
/* parallel for 011:
 * parallel for if が成立する場合の動作確認
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	*buf;

int	errors = 0;


int sameas(int v)
{
  return v;
}


void clear ()
{
  int lp;
  
  for (lp=0; lp<=thds; lp++) {
    buf[lp] = -1;
  }
}


check_parallel (int v)
{
  if (omp_in_parallel () != v) {
    #pragma omp critical
    errors += 1;
  }
  if (v) {
    if (omp_get_num_threads () != thds) {
      #pragma omp critical
      errors += 1;
    }
  } else {
    if (omp_get_num_threads () != 1) {
      #pragma omp critical
      errors += 1;
    }
  }
}


int
check_result (int v)
{
  int	lp;

  int	err = 0;


  for (lp = 0; lp<thds; lp++) {
    if (buf[lp] != lp) {
      err += 1;
    }
  }
  if (buf[thds] != -1) {
    err += 1;
  }

  return err;
}


main ()
{
  int	lp;

  int	 true = 3;
  double dtrue = 4.0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  buf = (int *) malloc (sizeof (int) * (thds + 1));
  if (buf == NULL) {
    printf ("can not allocate memory.\n");
    exit (1);
  }
  omp_set_dynamic (0);


  clear ();
  #pragma omp parallel for schedule(static,1) if (1)
  for (lp=0; lp<thds; lp++) {
    buf[lp] = omp_get_thread_num ();
    check_parallel (1);
  }
  errors += check_result (thds);

  clear ();
  #pragma omp parallel for schedule(static,1) if (dtrue)
  for (lp=0; lp<thds; lp++) {
    buf[lp] = omp_get_thread_num ();
    check_parallel (1);
  }
  errors += check_result (thds);

  clear ();
  #pragma omp parallel for schedule(static,1) if (true == 3)
  for (lp=0; lp<thds; lp++) {
    buf[lp] = omp_get_thread_num ();
    check_parallel (1);
  }
  errors += check_result (thds);

  clear ();
  #pragma omp parallel for schedule(static,1) if (sameas(4))
  for (lp=0; lp<thds; lp++) {
    buf[lp] = omp_get_thread_num ();
    check_parallel (1);
  }
  errors += check_result (thds);


  if (errors == 0) {
    printf ("parallel for 011 : SUCCESS\n");
    return 0;
  } else {
    printf ("parallel for 011 : FAILED\n");
    return 1;
  }
}
