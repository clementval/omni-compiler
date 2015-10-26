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
/* reduction 007 :
 * reduction(^:...) の動作を確認
 */

#include <omp.h>
#include "omni.h"


#define	LOOPNUM	(thds * 2)

int	errors = 0;
int	thds;

int	rdct_xor, rdct_xor2, rdct_xor3;


void
func_reduction (int loop)
{
  int	i;

  #pragma omp for reduction(^:rdct_xor,rdct_xor2,rdct_xor3)
  for (i=0; i<loop; i++) {
    rdct_xor ^= (1<<i);
    rdct_xor2 = rdct_xor2 ^ ((1<<(i*2))| 2);
    rdct_xor3 = ((1<<(i*3)) | 3) ^ rdct_xor3;
  }
}


void
check (int init, int loop)
{
  int	rst_xor, rst_xor2, rst_xor3;
  int	i;


  rst_xor = rst_xor2 = rst_xor3 = init;
  for (i=0;  i<loop;  i++) {
    rst_xor ^= (1<<i);
    rst_xor2 = rst_xor2 ^ ((1<<(i*2))| 2);
    rst_xor3 = ((1<<(i*3)) | 3) ^ rst_xor3;
  }

  if (rst_xor != rdct_xor) {
    errors += 1;
  }

  if (rst_xor2 != rdct_xor2) {
    errors += 1;
  }

  if (rst_xor3 != rdct_xor3) {
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


  rdct_xor = rdct_xor2 = rdct_xor3 = 0;
  #pragma omp parallel
  {
    #pragma omp for reduction(^:rdct_xor,rdct_xor2,rdct_xor3)
    for (i=0; i<LOOPNUM; i++) {
      rdct_xor ^= (1<<i);
      rdct_xor2 = rdct_xor2 ^ ((1<<(i*2))| 2);
      rdct_xor3 = ((1<<(i*3)) | 3) ^ rdct_xor3;
    }
  }
  check (0, LOOPNUM);

  rdct_xor = rdct_xor2 = rdct_xor3 = 1<<8;
  #pragma omp parallel
  {
    #pragma omp for reduction(^:rdct_xor,rdct_xor2,rdct_xor3)
    for (i=0; i<LOOPNUM; i++) {
      rdct_xor ^= (1<<i);
      rdct_xor2 = rdct_xor2 ^ ((1<<(i*2))| 2);
      rdct_xor3 = ((1<<(i*3)) | 3) ^ rdct_xor3;
    }
  }
  check (1<<8, LOOPNUM);

  rdct_xor = rdct_xor2 = rdct_xor3 = 1<<16;
  #pragma omp parallel
  func_reduction (LOOPNUM);
  check (1<<16, LOOPNUM);

  rdct_xor = rdct_xor2 = rdct_xor3 = 1<<24;
  func_reduction (LOOPNUM);
  check (1<<24, LOOPNUM);


  if (errors == 0) {
    printf ("reduction 007 : SUCCESS\n");
    return 0;
  } else {
    printf ("reduction 007 : FAILED\n");
    return 1;
  }
}
