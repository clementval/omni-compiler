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
/* parallel sections 006:
 * data attribute を設定した場合の動作確認
 */

#include <omp.h>
#include "omni.h"


int	thds, ids[2];
int	errors = 0;

int	shrd;
int	prvt, fprvt, lprvt, tprvt;
int	rdct;

#pragma omp threadprivate (tprvt)


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  fprvt = tprvt = shrd = -1;
  rdct = 0;

  #pragma omp parallel sections private(prvt) firstprivate(fprvt) \
				lastprivate(lprvt) reduction(+:rdct) \
				default(none) shared(shrd,errors,thds,ids) copyin(tprvt)
  {
    #pragma omp section
    {
      int id = omp_get_thread_num ();

      if (omp_get_num_threads() != thds) {
        #pragma omp critical
	errors += 1;
      }

      if (fprvt != -1) {
        #pragma omp critical
	errors += 1;
      }

      if (tprvt != -1) {
        #pragma omp critical
	errors += 1;
      }

      if (shrd != -1) {
        #pragma omp critical
	errors += 1;
      }
      barrier (2);

      ids[0] = id;
      prvt = id;
      shrd = id;
      fprvt = id;
      lprvt = id;
      rdct += 1;

      barrier (2);
     
      if (shrd != id) {
	#pragma omp critical
	errors += 1;
      }
      if (prvt != id) {
	#pragma omp critical
	errors += 1;
      }
      if (fprvt != id) {
	#pragma omp critical
	errors += 1;
      }
      if (lprvt != id) {
	#pragma omp critical
	errors += 1;
      }
    }

    #pragma omp section
    {
      int id = omp_get_thread_num ();

      if (omp_get_num_threads() != thds) {
        #pragma omp critical
	errors += 1;
      }

      if (fprvt != -1) {
        #pragma omp critical
	errors += 1;
      }

      if (tprvt != -1) {
        #pragma omp critical
	errors += 1;
      }

      if (shrd != -1) {
        #pragma omp critical
	errors += 1;
      }

      barrier (2);

      ids[1] = id;
      prvt = id;
      shrd = id;
      fprvt = id;
      lprvt = id;
      rdct += 1;

      barrier (2);
     
      if (shrd != id) {
	#pragma omp critical
	errors += 1;
      }
      if (prvt != id) {
	#pragma omp critical
	errors += 1;
      }
      if (fprvt != id) {
	#pragma omp critical
	errors += 1;
      }
      if (lprvt != id) {
	#pragma omp critical
	errors += 1;
      }

      shrd = lprvt;
    }
  }

  if (rdct != 2) {
    errors += 1;
  }
  if (lprvt != shrd) {
    errors += 1;
  }
  if (ids[0] == ids[1]) {
    errors += 1;
  }


  if (errors == 1) {
    printf ("parallel sections 006 : SUCCESS\n");
    return 0;
  } else {
    printf ("parallel sections 006 : FAILED\n");
    return 1;
  }
}
