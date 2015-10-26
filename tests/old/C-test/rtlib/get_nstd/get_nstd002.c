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
/* omp_get_nested : 002
 * omp_get_nestedの結果が0の場合,
 * nested parallel region serialize される事を確認。
 */

#include <omp.h>
#include "omni.h"


int
main ()
{
  int	thds, i;

  int	errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi thread.\n");
    exit (0);
  }

  omp_set_dynamic (0);
  omp_set_nested (0);
  if (omp_get_nested() != 0) {
    errors += 1;
    goto END;
  }


  #pragma omp parallel 
  {
    #pragma omp parallel
    {
      if (omp_get_num_threads () != 1) {
        #pragma omp critical
	errors += 1;
      }
      if (omp_get_thread_num () != 0) {
	errors += 1;
      }
    }
  }

#if defined(__OMNI_SCASH__) || defined(__OMNI_SHMEM__)
  /* Omni on SCASH do not support omp_set_num_threads.
   * and, some test 
   */
  printf ("skip some tests. because, Omni on SCASH/SHMEM do not support omp_set_num_threads, yet.\n");
#else
  for (i=1; i<=thds; i++) {
    omp_set_num_threads (i);

    #pragma omp parallel 
    {
      #pragma omp parallel
      {
	if (omp_get_num_threads () != 1) {
	  #pragma omp critical
	  errors += 1;
	}
	if (omp_get_thread_num () != 0) {
	  errors += 1;
	}
      }
    }
  }
#endif


 END:
  if (errors == 0) {
    printf ("omp_get_nested 002 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_get_nested 002 : FAILED\n");
    return 1;
  }
}

