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
/* for 001:
 * forの動作を確認
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	*buf;


void clear ()
{
  int lp;
  
  for (lp=0; lp<=thds; lp++) {
    buf[lp] = 0;
  }
}


int
check_result (int v)
{
  int	lp;

  int	err = 0;


  for (lp = 0; lp<thds; lp++) {
    if (buf[lp] != v) {
      err += 1;
    }
  }
  if (buf[thds] != 0) {
    err += 1;
  }

  return err;
}


void
func_for ()
{
  int	lp;

  #pragma omp for schedule(static,1)
  for (lp=0; lp<thds; lp++) {
    buf[lp] += omp_get_num_threads ();
  }
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
  buf = (int *) malloc (sizeof (int) * (thds + 1));
  if (buf == NULL) {
    printf ("can not allocate memory.\n");
    exit (1);
  }
  omp_set_dynamic (0);


  clear ();
  #pragma omp parallel
  {
    #pragma omp for schedule(static,1)
    for (lp=0; lp<thds; lp++) {
      buf[lp] += omp_get_num_threads ();
    }
  }
  errors += check_result (thds);

  clear ();
  #pragma omp parallel
  {
    func_for ();
  }
  errors += check_result (thds);

  clear ();
  func_for ();
  errors += check_result (1);


  if (errors == 0) {
    printf ("for 001 : SUCCESS\n");
    return 0;
  } else {
    printf ("for 001 : FAILED\n");
    return 1;
  }
}
