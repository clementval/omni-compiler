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
/* default 005 :
 * default(none)が宣言されていて、data attributeが宣言されている場合の動作確認
 */

#include <omp.h>
#include "omni.h"


#define	MAGICNO	100


int	errors = 0;
int	thds;

int	tprvt, prvt, fprvt, lprvt, rdct, shrd;
#pragma omp threadprivate (tprvt)


const int	cnst = MAGICNO;


main ()
{
  int	i, r;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);

  rdct = shrd = 0;
  fprvt = MAGICNO;
  #pragma omp parallel for default(none) private (prvt) firstprivate(fprvt) lastprivate(lprvt) reduction(+:rdct) shared(shrd,thds,errors) schedule (static,1)
  for (i=0; i<thds; i++) {
    #pragma omp critical
    {
      shrd  += 6*i;		      /* shrd is shared, i is private */
    }
    tprvt  = i;			      /* tprvt is threadprivate */
    prvt   = 2*i;		      /* prvt is private */
    fprvt += 3*i;		      /* fprvt is firstprivate */
    lprvt  = 4*i;		      /* lprvt is lastprivate */
    rdct  += 5*i;		      /* rdct is reduction(+) */
    waittime (1);

    if (prvt != 2*i) {		      /* check private */
      #pragma omp critical
      errors += 1;
    }
    if (fprvt != MAGICNO + 3*i) {
      #pragma omp critical
      errors += 1;
    }
  }

  r = 0;
  for (i=0; i<thds; i++) 
    r += i;
  if (rdct != r * 5) {
    errors += 1;
  }

  if (shrd != r * 6) {
    errors += 1;
  }

  if (lprvt != 4*(thds-1)) {
    errors += 1;
  }

  #pragma omp parallel for default(shared) schedule (static)
  for (i=0; i<thds; i++) {
    if (tprvt != i) {
      #pragma omp critical
      errors += 1;
    }
  }


  if (errors == 0) {
    printf ("default 005 : SUCCESS\n");
    return 0;
  } else {
    printf ("default 005 : FAILED\n");
    return 1;
  }
}
