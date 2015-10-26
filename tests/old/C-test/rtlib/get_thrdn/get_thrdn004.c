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
/* omp_get_thread_num : 004
 * parallel sections region内で omp_get_thread_num の動作を確認
 */

#include <string.h>
#include <omp.h>
#include "omni.h"


int
main ()
{
  int	thds, *buf, i, j;

  int	errors = 0;


  /* initialize */
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");	
    exit (0);
  } else if (4<thds) {
    thds = 4;
  }


  buf = (int *) malloc ((thds + 1) * sizeof(int));
  if (buf == NULL) {
    printf ("can not allocate memory\n");
    exit (1);
  }
  omp_set_dynamic (0);


  memset (buf, 0, sizeof(int) * (thds+1));
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      int id = omp_get_thread_num ();

      if (1<=thds) {
        #pragma omp critical
	buf[id] += 1;

	barrier (thds);
      }
    }
    #pragma omp section
    {
      int id = omp_get_thread_num ();

      if (2<=thds) {
      #pragma omp critical
	buf[id] += 1;

	barrier (thds);
      }
    }
    #pragma omp section
    {
      int id = omp_get_thread_num ();

      if (3<=thds) {
        #pragma omp critical
	buf[id] += 1;

	barrier (thds);
      }
    }
    #pragma omp section
    {
      int id = omp_get_thread_num ();

      if (4<=thds) {
        #pragma omp critical
	buf[id] += 1;

	barrier (thds);
      }
    }
  }

  for (j=0; j<thds; j++) {
    if (buf[j] != 1) {
      errors += 1;
    }
  }
  if (buf[thds] != 0) {
    errors += 1;
  }


#if defined(__OMNI_SCASH__) || defined(__OMNI_SHMEM__)
  /* Omni on SCASH do not support omp_set_num_threads.
   * and, some test 
   */
  printf ("skip some tests. because, Omni on SCASH/SHMEM do not support omp_set_num_threads, yet.\n");
#else
  for (i=1; i<=thds; i++) {

    memset (buf, 0, sizeof(int) * (thds+1));
    omp_set_num_threads (i);

    #pragma omp parallel sections
    {
      #pragma omp section
      {
	int id = omp_get_thread_num ();

	if (1<=i) {
          #pragma omp critical
	  buf[id] += 1;

	  barrier (i);
	}
      }
      #pragma omp section
      {
	int id = omp_get_thread_num ();

	if (2<=i) {
          #pragma omp critical
	  buf[id] += 1;

	  barrier (i);
	}
      }
      #pragma omp section
      {
	int id = omp_get_thread_num ();

	if (3<=i) {
          #pragma omp critical
	  buf[id] += 1;

	  barrier (i);
	}
      }
      #pragma omp section
      {
	int id = omp_get_thread_num ();

	if (4<=i) {
          #pragma omp critical
	  buf[id] += 1;

	  barrier (i);
	}
      }
    }

    for (j=0; j<i; j++) {
      if (buf[j] != 1) {
	errors += 1;
      }
    }
    for (j=i; j<=thds; j++) {
      if (buf[thds] != 0) {
	errors += 1;
      }
    }
  }
#endif


  if (errors == 0) {
    printf ("omp_get_thread_num 004 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_get_thread_num 004 : FAILED\n");
    return 1;
  }
}
