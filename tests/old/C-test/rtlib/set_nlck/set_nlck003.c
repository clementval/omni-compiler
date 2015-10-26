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
/* omp_set_nest_lock 003:
 * 既にlockされている変数に対してomp_set_nest_lockを実行すると、
 * unlockされるまで、待たされる事を確認する。
 * その状態で、自分自信はnest lockが通る事を確認する。
 */

#include <omp.h>
#include "omni.h"


main ()
{
  omp_nest_lock_t	lck;
  int			thds;
  volatile int		i;

  int		errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi thread.\n");
    exit (0);
  }

  omp_init_nest_lock(&lck);
  i = 0;

  #pragma omp parallel
  {
    int	tmp;

    #pragma omp barrier

    omp_set_nest_lock (&lck);

    #pragma omp flush (i)
    i = i + 1;
    tmp  = i;
    waittime(1);

    #pragma omp flush (i)
    if (i != tmp) {	
      #pragma omp critical
      errors += 1;
    }
    omp_set_nest_lock (&lck);
    omp_unset_nest_lock (&lck);
    waittime(1);

    #pragma omp flush(i)
    if (i != tmp) {	
      #pragma omp critical
      errors += 1;
    }

    omp_unset_nest_lock (&lck);
  }

  if (i != thds) {
    errors += 1;
  }


  if (errors == 0) {
    printf ("omp_set_nest_lock 003 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_set_nest_lock 003 : FAILED\n");
    return 1;
  }
}
