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
/* omp_test_lock 002:
 * スレッド間で、omp_test_lock関数の動作を確認します。
 */

#include <omp.h>
#include "omni.h"


main ()
{
  omp_lock_t	lck;
  int		thds;
  int		s,f;

  int		errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi thread.\n");
    exit (0);
  }

  omp_init_lock(&lck);
  s = f = 0;

  #pragma omp parallel
  {
    int	t;

    t = omp_test_lock (&lck);
    if (t != 0) {
      /* lock successful */
      #pragma omp critical
      s += 1;
    } else {
      /* lock fail */
      #pragma omp critical
      f += 1;
    }
  }

  if (s != 1) {
    errors += 1;
  }
  if (f != thds - 1) {
    errors += 1;
  }


  if (errors == 0) {
    printf ("omp_test_lock 002 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_test_lock 002 : FAILED\n");
    return 1;
  }
}
