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
/* reduction 006 :
 * reduction(|:...) の動作を確認
 */

#include <omp.h>
#include "omni.h"


#define	LOOPNUM	(thds * 2)

int	errors = 0;
int	thds;

int	rdct_lor, rdct_lor2, rdct_lor3;


void
func_reduction (int loop)
{
  int	i;

  #pragma omp for reduction(|:rdct_lor,rdct_lor2,rdct_lor3)
  for (i=0; i<loop; i++) {
    rdct_lor |= (1<<i);
    rdct_lor2 = rdct_lor2 | (1<<(i*2) | 2);
    rdct_lor3 = (1<<(i*3) | 3) | rdct_lor3;
  }
}


void
check (int init, int loop)
{
  int	rst_lor, rst_lor2, rst_lor3;
  int	i;


  rst_lor = rst_lor2 = rst_lor3 = init;
  for (i=0;  i<loop;  i++) {
    rst_lor |= (1<<i);
    rst_lor2 = rst_lor2 | (1<<(i*2) | 2);
    rst_lor3 = (1<<(i*3) | 3) | rst_lor3;
  }

  if (rst_lor != rdct_lor) {
    errors += 1;
  }

  if (rst_lor2 != rdct_lor2) {
    errors += 1;
  }

  if (rst_lor3 != rdct_lor3) {
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


  rdct_lor = rdct_lor2 = rdct_lor3 = 0;
  #pragma omp parallel
  {
    #pragma omp for reduction(|:rdct_lor,rdct_lor2,rdct_lor3)
    for (i=0; i<LOOPNUM; i++) {
      rdct_lor |= (1<<i);
      rdct_lor2 = rdct_lor2 | (1<<(i*2) | 2);
      rdct_lor3 = (1<<(i*3) | 3) | rdct_lor3;
    }
  }
  check (0, LOOPNUM);

  rdct_lor = rdct_lor2 = rdct_lor3 = (1<<8);
  #pragma omp parallel
  {
    #pragma omp for reduction(|:rdct_lor,rdct_lor2,rdct_lor3)
    for (i=0; i<LOOPNUM; i++) {
      rdct_lor |= (1<<i);
      rdct_lor2 = rdct_lor2 | (1<<(i*2) | 2);
      rdct_lor3 = (1<<(i*3) | 3) | rdct_lor3;
    }
  }
  check ((1<<8), LOOPNUM);

  rdct_lor = rdct_lor2 = rdct_lor3 = (1<<16);
  #pragma omp parallel
  func_reduction (LOOPNUM);
  check ((1<<16), LOOPNUM);

  rdct_lor = rdct_lor2 = rdct_lor3 = (1<<24);
  func_reduction (LOOPNUM);
  check ((1<<24), LOOPNUM);


  if (errors == 0) {
    printf ("reduction 006 : SUCCESS\n");
    return 0;
  } else {
    printf ("reduction 006 : FAILED\n");
    return 1;
  }
}
