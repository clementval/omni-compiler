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
/* copyin 020 :
 * parallel forのループカウンタに対してcopyinした場合の動作を確認
 */

#include <omp.h>
#include "omni.h"


#define LOOPNUM		(100*thds)

int	errors = 0;
int	thds;
int	*buff;


int	prvt;
#pragma omp threadprivate(prvt)


void
check(int s)
{
  int   i,j, id;

  for (i=0; i<LOOPNUM; i+=s) {
    id = (i/s) % thds;

    for (j=0; j<s; j++) {
      if ((i+j) < LOOPNUM) {
        if (buff[i+j] != id) {
          #pragma omp critical
          errors += 1;
        }
      }
    }
  }
}


main ()
{
  int	ln;

  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  buff = (int *)malloc(sizeof(int) * LOOPNUM);
  if (buff == NULL) {
    printf ("can not allocate memory.\n");
  }
  omp_set_dynamic (0);

  ln = LOOPNUM;
  #pragma omp parallel for schedule(static,ln/thds) copyin(prvt) 
  for (prvt=0; prvt<LOOPNUM; prvt++) {
    buff[prvt] = omp_get_thread_num ();
  }
  check (LOOPNUM/thds);


  if (errors == 0) {
    printf ("copyin 020 : SUCCESS\n");
    return 0;
  } else {
    printf ("copyin 020 : FAILED\n");
    return 1;
  }
}
