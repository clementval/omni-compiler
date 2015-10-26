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
/* reduction 016 :
 * long long �ѿ��� reduction �����ꤵ�줿����ư���ǧ
 */

#include <omp.h>
#include "omni.h"


#define	LOOPNUM	(thds * 2)

int	errors = 0;
int	thds;

long long	rdct_inc, rdct_inc2, rdct_pls, rdct_pls2, rdct_pls3;
long long	rdct_dec, rdct_dec2, rdct_mns, rdct_mns2;
long long	rdct_mul, rdct_mul2, rdct_mul3;
long long	rdct_land, rdct_land2, rdct_land3;
long long	rdct_lor, rdct_lor2, rdct_lor3;
long long	rdct_xor, rdct_xor2, rdct_xor3;
long long	rdct_and, rdct_and2;
long long	rdct_or, rdct_or2;

long long	rst_inc, rst_inc2, rst_pls, rst_pls2, rst_pls3;
long long	rst_dec, rst_dec2, rst_mns, rst_mns2;
long long	rst_mul, rst_mul2, rst_mul3;
long long	rst_land, rst_land2, rst_land3;
long long	rst_lor, rst_lor2, rst_lor3;
long long	rst_xor, rst_xor2, rst_xor3;
long long	rst_and, rst_and2;
long long	rst_or, rst_or2;


main ()
{
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

    if (sizeof(rdct_inc) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_inc2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_pls) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_pls2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_pls3) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_dec) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_dec2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_mns) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_mns2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_mul) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_mul2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_mul3) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_land) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_land2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_land3) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_lor) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_lor2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_lor3) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_xor) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_xor2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_xor3) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_and) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_and2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_or) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(rdct_or2) != sizeof(long long)) {
      #pragma omp critical
      errors += 1;
    }
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
  if (rst_xor != rdct_xor) {
    errors += 1;
  }
  if (rst_xor2 != rdct_xor2) {
    errors += 1;
  }
  if (rst_xor3 != rdct_xor3) {
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
    printf ("reduction 016 : SUCCESS\n");
    return 0;
  } else {
    printf ("reduction 016 : FAILED\n");
    return 1;
  }
}
