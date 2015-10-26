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
 * reduction(+:...) の動作を確認
 */

#include <omp.h>
#include "omni.h"


#define	LOOPNUM	(thds * 2)

int	errors = 0;
int	thds;

int	rdct_inc, rdct_inc2, rdct_pls, rdct_pls2, rdct_pls3;


void
func_reduction (int loop)
{
  int	i;

  #pragma omp for reduction(+:rdct_inc,rdct_inc2,rdct_pls,rdct_pls2,rdct_pls3) 
  for (i=0; i<loop; i++) {
    rdct_inc ++;
    ++ rdct_inc2;
    rdct_pls += i*2;
    rdct_pls2 = rdct_pls2 + i*3;
    rdct_pls3 = i*4 + rdct_pls3;
  }
}


void
check (int init, int loop)
{
  int	rst_inc, rst_inc2, rst_pls, rst_pls2, rst_pls3;
  int	i;


  rst_inc = rst_inc2 = rst_pls = rst_pls2 = rst_pls3 = init;
  for (i=0;  i<loop;  i++) {
    rst_inc ++;
    ++ rst_inc2;
    rst_pls += i*2;
    rst_pls2 = rst_pls2 + i*3;
    rst_pls3 = i*4 + rst_pls3;
  }

  if (rst_inc != rdct_inc) {
    errors += 1;
  }

  if (rst_inc2 != rdct_inc2) {
    errors += 1;
  }

  if (rst_pls != rdct_pls) {
    errors += 1;
  }

  if (rst_pls2 != rdct_pls2) {
    errors += 1;
  }

  if (rst_pls3 != rdct_pls3) {
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


  rdct_inc = rdct_inc2 = rdct_pls = rdct_pls2 = rdct_pls3 = 0;
  #pragma omp parallel
  {
    #pragma omp for reduction(+:rdct_inc,rdct_inc2,rdct_pls,rdct_pls2,rdct_pls3) 
    for (i=0; i<LOOPNUM; i++) {
      rdct_inc ++;
      ++ rdct_inc2;
      rdct_pls += i*2;
      rdct_pls2 = rdct_pls2 + i*3;
      rdct_pls3 = i*4 + rdct_pls3;
    }
  }
  check (0, LOOPNUM);


  rdct_inc = rdct_inc2 = rdct_pls = rdct_pls2 = rdct_pls3 = 100;
  #pragma omp parallel
  func_reduction (LOOPNUM);
  check (100, LOOPNUM);


  rdct_inc = rdct_inc2 = rdct_pls = rdct_pls2 = rdct_pls3 = 200;
  func_reduction (LOOPNUM);
  check (200, LOOPNUM);


  if (errors == 0) {
    printf ("reduction 002 : SUCCESS\n");
    return 0;
  } else {
    printf ("reduction 002 : FAILED\n");
    return 1;
  }
}
