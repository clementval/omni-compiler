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
/* lastprivate 004 :
 * 複数の変数に対してlastprivateを宣言した場合の動作確認
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;

int	prvt1, prvt2, prvt3;


void
func (int t)
{
  int	i;


  #pragma omp for schedule(static,1) lastprivate (prvt1,prvt2,prvt3)
  for (i=0; i<thds; i++) {
    prvt1 = i;
    prvt2 = i;
    prvt3 = i;
    barrier (t);
    if (prvt1 != i) {
      #pragma omp critical
      errors += 1;
    }
    if (prvt2 != i) {
      #pragma omp critical
      errors += 1;
    }
    if (prvt3 != i) {
      #pragma omp critical
      errors += 1;
    }
    if (i==0) {
      waittime (1);
    }
    prvt1 = i;
    prvt2 = i;
    prvt3 = i;
  }

  if (prvt1 != thds - 1) {
    #pragma omp critical
    errors += 1;
  }
  if (prvt2 != thds - 1) {
    #pragma omp critical
    errors += 1;
  }
  if (prvt3 != thds - 1) {
    #pragma omp critical
    errors += 1;
  }
}


main ()
{
  int	i;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel
  {
    #pragma omp for schedule(static,1) lastprivate (prvt1,prvt2) lastprivate (prvt3)
    for (i=0; i<thds; i++) {
      prvt1 = i;
      prvt2 = i;
      prvt3 = i;
      barrier (thds);
      if (prvt1 != i) {
	#pragma omp critical
	errors += 1;
      }
      if (prvt2 != i) {
	#pragma omp critical
	errors += 1;
      }
      if (prvt3 != i) {
	#pragma omp critical
	errors += 1;
      }
      if (i==0) {
	waittime (1);
      }
      prvt1 = i;
      prvt2 = i;
      prvt3 = i;
    }

    if (prvt1 != thds - 1) {
      #pragma omp critical
      errors += 1;
    }
    if (prvt2 != thds - 1) {
      #pragma omp critical
      errors += 1;
    }
    if (prvt3 != thds - 1) {
      #pragma omp critical
      errors += 1;
    }
  }


  #pragma omp parallel
  func (thds);


  func (1);


  if (errors == 0) {
    printf ("lastprivate 004 : SUCCESS\n");
    return 0;
  } else {
    printf ("lastprivate 004 : FAILED\n");
    return 1;
  }
}
