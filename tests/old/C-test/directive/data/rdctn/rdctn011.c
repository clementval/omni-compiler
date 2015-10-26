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
/* reduction 011 :
 * localのstatic変数に reduction が指定された場合の動作確認
 */

#include <omp.h>
#include "omni.h"


#define	LOOPNUM	(thds * 2)

int	errors = 0;
int	thds;


main ()
{
  static int	rdct_inc, rdct_inc2, rdct_pls, rdct_pls2, rdct_pls3;
  static int	rdct_dec, rdct_dec2, rdct_mns, rdct_mns2;
  static int	rdct_mul, rdct_mul2, rdct_mul3;
  static int	rdct_land, rdct_land2, rdct_land3;
  static int	rdct_lor, rdct_lor2, rdct_lor3;
  static int	rdct_xor, rdct_xor2, rdct_xor3;
  static int	rdct_and, rdct_and2;
  static int	rdct_or, rdct_or2;

  static int	rst_inc, rst_inc2, rst_pls, rst_pls2, rst_pls3;
  static int	rst_dec, rst_dec2, rst_mns, rst_mns2;
  static int	rst_mul, rst_mul2, rst_mul3;
  static int	rst_land, rst_land2, rst_land3;
  static int	rst_lor, rst_lor2, rst_lor3;
  static int	rst_xor, rst_xor2, rst_xor3;
  static int	rst_and, rst_and2;
  static int	rst_or, rst_or2;

  int	i;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  rdct_inc = rdct_inc2 = rdct_pls = rdct_pls2 = rdct_pls3 = 1;
  rdct_dec = rdct_dec2 = rdct_mns = rdct_mns2 = 2;
  rdct_mul = rdct_mul2 = rdct_mul3 = 3;
  rdct_land = rdct_land2 = rdct_land3 = -2;
  rdct_lor = rdct_lor2 = rdct_lor3 = 1;
  rdct_xor = rdct_xor2 = rdct_xor3 = 2;
  rdct_and = rdct_and2 = 1;
  rdct_or = rdct_or2 = 0;

  #pragma omp parallel for reduction(+:rdct_inc,rdct_inc2,rdct_pls,rdct_pls2,rdct_pls3) \
			   reduction(-:rdct_dec,rdct_dec2,rdct_mns,rdct_mns2) \
			   reduction(*:rdct_mul,rdct_mul2,rdct_mul3) \
			   reduction(&:rdct_land,rdct_land2,rdct_land3) \
			   reduction (|:rdct_lor,rdct_lor2,rdct_lor3) \
			   reduction (^:rdct_xor,rdct_xor2,rdct_xor3) \
			   reduction (&&:rdct_and,rdct_and2) \
			   reduction (||:rdct_or,rdct_or2)
  for (i=0; i<LOOPNUM; i++) {

    rdct_inc ++;
    ++ rdct_inc2;
    rdct_pls += i;
    rdct_pls2 = rdct_pls2 + i;
    rdct_pls3 = i + rdct_pls3;

    rdct_dec --;
    -- rdct_dec2;
    rdct_mns -= i;
    rdct_mns2 = rdct_mns2 - i;

    rdct_mul *= i;
    rdct_mul2 = rdct_mul2 * i;
    rdct_mul3 = i * rdct_mul3;

    rdct_land &= 1<<i;
    rdct_land2 = rdct_land2 & (1<<i);
    rdct_land3 = (1<<i) & rdct_land3;

    rdct_lor |= 1<<i;
    rdct_lor2 = rdct_lor2 | (1<<i);
    rdct_lor3 = (1<<i) | rdct_lor3;

    rdct_xor ^= 1<<i;
    rdct_xor2 = rdct_xor2 ^ (1<<i);
    rdct_xor3 = (1<<i) ^ rdct_xor3;

    rdct_and = rdct_and && i;
    rdct_and2 = (i+1) && rdct_and2;

    rdct_or = rdct_or || i;
    rdct_or2 = 0 || rdct_or2;
  }


  rst_inc = rst_inc2 = rst_pls = rst_pls2 = rst_pls3 = 1;
  rst_dec = rst_dec2 = rst_mns = rst_mns2 = 2;
  rst_mul = rst_mul2 = rst_mul3 = 3;
  rst_land = rst_land2 = rst_land3 = -2;
  rst_lor = rst_lor2 = rst_lor3 = 1;
  rst_xor = rst_xor2 = rst_xor3 = 2;
  rst_and = rst_and2 = 1;
  rst_or = rst_or2 = 0;

  for (i=0; i<LOOPNUM; i++) {

    rst_inc ++;
    ++ rst_inc2;
    rst_pls += i;
    rst_pls2 = rst_pls2 + i;
    rst_pls3 = i + rst_pls3;

    rst_dec --;
    -- rst_dec2;
    rst_mns -= i;
    rst_mns2 = rst_mns2 - i;

    rst_mul *= i;
    rst_mul2 = rst_mul2 * i;
    rst_mul3 = i * rst_mul3;

    rst_land &= 1<<i;
    rst_land2 = rst_land2 & (1<<i);
    rst_land3 = (1<<i) & rst_land3;

    rst_lor |= 1<<i;
    rst_lor2 = rst_lor2 | (1<<i);
    rst_lor3 = (1<<i) | rst_lor3;

    rst_xor ^= 1<<i;
    rst_xor2 = rst_xor2 ^ (1<<i);
    rst_xor3 = (1<<i) ^ rst_xor3;

    rst_and = rst_and && i;
    rst_and2 = (i+1) && rst_and2;

    rst_or = rst_or || i;
    rst_or2 = 0 || rst_or2;
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
  if (rst_dec != rdct_dec) {
    errors += 1;
  }
  if (rst_dec2 != rdct_dec2) {
    errors += 1;
  }
  if (rst_mns != rdct_mns) {
    errors += 1;
  }
  if (rst_mns2 != rdct_mns2) {
    errors += 1;
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
  if (rst_land != rdct_land) {
    errors += 1;
  }
  if (rst_land2 != rdct_land2) {
    errors += 1;
  }
  if (rst_land3 != rdct_land3) {
    errors += 1;
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
  if (rst_and != rdct_and) {
    errors += 1;
  }
  if (rst_and2 != rdct_and2) {
    errors += 1;
  }
  if (rst_or != rdct_or) {
    errors += 1;
  }
  if (rst_or2 != rdct_or2) {
    errors += 1;
  }


  if (errors == 0) {
    printf ("reduction 011 : SUCCESS\n");
    return 0;
  } else {
    printf ("reduction 011 : FAILED\n");
    return 1;
  }
}
