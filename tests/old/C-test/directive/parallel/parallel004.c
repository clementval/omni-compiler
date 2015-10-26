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
/* parallel structure 004:
 * parallel section 中に thread 数が変わらないことを確認。
 */

#include <omp.h>
#include "omni.h"


#define ITER	(thds*1000)

main ()
{
  int	errors = 0;
  int	thds, i;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel
  {
    if (thds != omp_get_num_threads ()) {
      #pragma omp critical
      errors += 1;
    }

    #pragma omp for
    for (i = 0;  i<ITER;  i++) {
      if (thds != omp_get_num_threads ()) {
	#pragma omp critical
	errors += 1;
      }
    }

    omp_set_num_threads (thds-1);

    if (thds != omp_get_num_threads ()) {
      #pragma omp critical
      errors += 1;
    }

    #pragma omp for
    for (i = 0;  i<1;  i++) {
      if (thds != omp_get_num_threads ()) {
	#pragma omp critical
	errors += 1;
      }
    }
  }

#if defined(__OMNI_SCASH__) || (__OMNI_SHMEM__)
  printf ("skip some tests. because Omni on SCASH/SHMEM is not support omp_set_num_threads.\n");
#else
  omp_set_num_threads (thds-1);
  #pragma omp parallel
  {
    if (thds-1 != omp_get_num_threads ()) {
      #pragma omp critical
      errors += 1;
    }

    #pragma omp for
    for (i = 0;  i<ITER;  i++) {
      if (thds-1 != omp_get_num_threads ()) {
	#pragma omp critical
	errors += 1;
      }
    }

    omp_set_num_threads (thds);

    if (thds-1 != omp_get_num_threads ()) {
      #pragma omp critical
      errors += 1;
    }

    #pragma omp for
    for (i = 0;  i<1;  i++) {
      if (thds-1 != omp_get_num_threads ()) {
	#pragma omp critical
	errors += 1;
      }
    }
  }
#endif


  if (errors == 0) {
    printf ("parallel 004 : SUCCESS\n");
    return 0;
  } else {
    printf ("parallel 004 : FAILED\n");
    return 1;
  }
}
