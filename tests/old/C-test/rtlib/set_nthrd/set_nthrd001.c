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
/* omp_set_num_threads : 001
 * omp_set_num_threads でスレッド数を変更し omp parallel で動作確認
 */

#include <omp.h>
#include "omni.h"


main ()
{
  int	thds, i, sum;

  int	errors = 0;


#if defined(__OMNI_SCASH__) || defined(__OMNI_SHMEM__)
  printf ("Omni on SCASH/SHMEM do not support omp_set_num_threads, yet.\n");
  printf ("test skipped.\n");
  exit (0);
#endif

  /* initialize */
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi thread.\n");
    exit(0);
  }
  omp_set_dynamic (0);


  for (i=1;  i<=thds; i++) {

    omp_set_num_threads (i);

    sum = 0;
#pragma omp parallel
    {
      if (omp_get_num_threads () != i) {
	#pragma omp critical
	errors += 1;
      }
      
      #pragma omp critical
      sum += 1;
    }
    if (sum != i) {
      errors += 1;
    }
  }


  if (errors == 0) {
    printf ("omp_set_num_threads 001 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_set_num_threads 001 : FAILED\n");
    return 1;
  }
}
