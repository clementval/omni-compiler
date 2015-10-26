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
/* for structure 011:
 * data attribute が指定された場合の動作を確認
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	errors = 0;

int	prvt, fprvt, lprvt;
int	rdct, ordd;


main ()
{
  int	i;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  prvt = fprvt = -1;
  rdct = ordd = 0;
  #pragma omp parallel
  {
    #pragma omp for private(prvt) firstprivate(fprvt) lastprivate(lprvt) \
		    reduction(+:rdct) ordered schedule(static,1)
    for (i=0; i<thds; i++) {
      int id = omp_get_thread_num ();

      if (omp_in_parallel() == 0) {
        #pragma omp critical
	errors += 1;
      }
      if (omp_get_num_threads() != thds) {
        #pragma omp critical
	errors += 1;
      }
      if (omp_get_thread_num() >= thds) {
        #pragma omp critical
	errors += 1;
      }

      if (fprvt != -1) {
        #pragma omp critical
	errors += 1;
      }

      prvt = id;
      fprvt = id;
      lprvt = i;
      rdct += 1;

      barrier (thds);

      if (prvt != id) {
        #pragma omp critical
	errors += 1;
      }
      if (fprvt != id) {
        #pragma omp critical
	errors += 1;
      }
      if (lprvt != i) {
        #pragma omp critical
	errors += 1;
      }

      #pragma omp ordered
      {
	if (i != ordd) {
	  errors += 1;
	}
	ordd += 1;
      }
    }
  }

  if (lprvt != thds-1) {
    errors += 1;
  }

  if (rdct != thds) {
    errors += 1;
  }

  if (errors == 0) {
    printf ("for 011 : SUCCESS\n");
    return 0;
  } else {
    printf ("for 011 : FAILED\n");
    return 1;
  }
}
