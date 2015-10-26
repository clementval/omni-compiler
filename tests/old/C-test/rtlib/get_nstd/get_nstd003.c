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
/* omp_get_nested : 003
 * omp_get_nested の結果が enable の場合、
 * nested parallel region が並列で実行される事を確認。
 */

#include <string.h>
#include <omp.h>
#include "omni.h"


int
main ()
{
  int	thds, *buf;

  int	errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi thread.\n");
    exit (0);
  }
  buf = (int *) malloc (sizeof(int) * (thds + 1));
  if (buf == NULL) {
    printf ("can not allocate memory.\n");
    exit (1);
  }

  omp_set_dynamic (0);
  omp_set_nested (1);
  if (omp_get_nested () == 0) {
    printf ("nested parallelism is not imprelment.\n");
    goto END;
  }


  omp_set_num_threads (1);

  #pragma omp parallel 
  {
    int	i, j;

    if (omp_get_num_threads () != 1) {
      #pragma omp critical
      errors += 1;
    }
    if (omp_get_thread_num () != 0) {
      errors += 1;
    }

    for (i=1; i<=thds; i++) {

      memset (buf, 0, sizeof(int) * (thds+1));
      omp_set_num_threads (i);

      #pragma omp parallel
      {
	int	id = omp_get_thread_num ();

	if (omp_get_num_threads () != i) {
	  #pragma omp critical
	  errors += 1;
	}
	buf[id] += 1;
      }

      for (j=0; j<i; j++) {
	if (buf[j] != 1) {
	  #pragma omp critical
	  errors += 1;
	}	
      }
      for (j=i; j<=thds; j++) {
	if (buf[j] != 0) {
	  #pragma omp critical
	  errors += 1;
	}	
      }
    }
  }


 END:
  if (errors == 0) {
    printf ("omp_get_nested 003 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_get_nested 003 : FAILED\n");
    return 1;
  }
}

