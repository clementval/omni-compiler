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
/* copyin 010 :
 * 構造体に対して copyin 宣言をした場合の動作確認
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;


struct x {
  int		i;
  double	d;
};

struct x	org;
struct x	prvt;
#pragma omp threadprivate(prvt)


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  prvt.i = org.i = -1;
  prvt.d = org.d = 1;
  #pragma omp parallel copyin (prvt)
  {
    if (prvt.i != org.i || prvt.d != org.d || sizeof(prvt) != sizeof(struct x)) {
      #pragma omp critical
      errors += 1;
    }
  }


  prvt.i = org.i = 0;
  prvt.d = org.d = 3;
  #pragma omp parallel copyin (prvt)
  {
    if (prvt.i != org.i || prvt.d != org.d || sizeof(prvt) != sizeof(struct x)) {
      #pragma omp critical
      errors += 1;
    }
  }


  prvt.i = org.i = -2;
  prvt.d = org.d = 2;
  #pragma omp parallel copyin (prvt)
  {
    if (prvt.i != org.i || prvt.d != org.d || sizeof(prvt) != sizeof(struct x)) {
      #pragma omp critical
      errors += 1;
    }
  }


  if (errors == 0) {
    printf ("copyin 010 : SUCCESS\n");
    return 0;
  } else {
    printf ("copyin 010 : FAILED\n");
    return 1;
  }
}
