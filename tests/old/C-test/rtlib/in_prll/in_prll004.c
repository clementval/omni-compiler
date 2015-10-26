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
/* omp_in_parallel : 004
 * parallel sections 内で omp_in_parallel の動作を確認
 */
#include <omp.h>
#include "omni.h"


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


  #pragma omp parallel sections
  {
    #pragma omp section
    {
      if (omp_in_parallel () == 0) {
	#pragma omp critical
	errors += 1;
      }
    }
    #pragma omp section
    {
      if (omp_in_parallel () == 0) {
	#pragma omp critical
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

    #pragma omp parallel sections
    {
      #pragma omp section
      {
	if (omp_in_parallel () == 0) {
	  #pragma omp critical
	  errors += 1;
	}
      }
      #pragma omp section
      {
	if (omp_in_parallel () == 0) {
	  #pragma omp critical
	  errors += 1;
	}
      }
    }
  }
#endif


  if (errors == 0) {
    printf ("omp_in_parallel 004 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_in_parallel 004 : FAILED\n");
    return 1;
  }
}
