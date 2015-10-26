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
/* reduction 004 :
 * reduction(*:...) の動作を確認
 */

#include <omp.h>
#include "omni.h"


#define	LOOPNUM	(thds * 2)

int	errors = 0;
int	thds;

int	rdct_mul, rdct_mul2, rdct_mul3;


void
func_reduction (int loop)
{
  int	i;

  #pragma omp for reduction(*:rdct_mul,rdct_mul2,rdct_mul3)
  for (i=1; i<loop; i++) {
    rdct_mul *= i;
    rdct_mul2 = rdct_mul2 * (i*2);
    rdct_mul3 = i*3 * rdct_mul3;
  }
}


void
check (int init, int loop)
{
  int	rst_mul, rst_mul2, rst_mul3;
  int	i;


  rst_mul = rst_mul2 = rst_mul3 = init;
  for (i=1;  i<loop;  i++) {
    rst_mul *= i;
    rst_mul2 = rst_mul2 * i*2;
    rst_mul3 = i*3 * rst_mul3;
  }

  if (rst_mul != rdct_mul) {
    errors += 1;
  }

  if (rst_mul2 != rdct_mul2) {
    errors += 1;
  }

  if (rst_mul3 != rdct_mul3) {
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


  rdct_mul = rdct_mul2 = rdct_mul3 = 0;
  #pragma omp parallel
  {
    #pragma omp for reduction(*:rdct_mul,rdct_mul2,rdct_mul3)
    for (i=1; i<LOOPNUM; i++) {
      rdct_mul *= i;
      rdct_mul2 = rdct_mul2 * (i*2);
      rdct_mul3 = i*3 * rdct_mul3;
    }
  }
  check (0, LOOPNUM);

  rdct_mul = rdct_mul2 = rdct_mul3 = 1;
  #pragma omp parallel
  {
    #pragma omp for reduction(*:rdct_mul,rdct_mul2,rdct_mul3)
    for (i=1; i<LOOPNUM; i++) {
      rdct_mul *= i;
      rdct_mul2 = rdct_mul2 * (i*2);
      rdct_mul3 = i*3 * rdct_mul3;
    }
  }
  check (1, LOOPNUM);

  rdct_mul = rdct_mul2 = rdct_mul3 = 100;
  #pragma omp parallel
  func_reduction (LOOPNUM);
  check (100, LOOPNUM);

  rdct_mul = rdct_mul2 = rdct_mul3 = 200;
  #pragma omp parallel
  func_reduction (LOOPNUM);
  check (200, LOOPNUM);


  if (errors == 0) {
    printf ("reduction 004 : SUCCESS\n");
    return 0;
  } else {
    printf ("reduction 004 : FAILED\n");
    return 1;
  }
}
