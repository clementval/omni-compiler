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
/* firstprivate 002 :
 * �������ѿ����Ф��� firstprivate �����ư���ǧ
 */

#include <omp.h>
#include "omni.h"


#define MAGICNO		100

int	errors = 0;
int	thds;



void
func1 (int magicno, int *prvt, int *prvt2)
{
  int	id = omp_get_thread_num ();

  if (*prvt != magicno) {
    #pragma omp critical
    errors += 1;
  }
  if (*prvt2 != magicno+1) {
    #pragma omp critical
    errors += 1;
  }

  *prvt  = id;
  *prvt2 = id+magicno;

  #pragma omp barrier
  if (*prvt != id) {
    #pragma omp critical
    errors += 1;
  }
  #pragma omp barrier
  if (*prvt2 != id+magicno) {
    #pragma omp critical
    errors += 1;
  }
}


main ()
{
  int		prvt;
  static int	prvt2;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  prvt  = MAGICNO;
  prvt2 = MAGICNO + 1;
  #pragma omp parallel firstprivate (prvt) firstprivate(prvt2)
  {
    int	id = omp_get_thread_num ();

    if (prvt != MAGICNO) {
      #pragma omp critical
      errors += 1;
    }
    if (prvt2 != MAGICNO+1) {
      #pragma omp critical
      errors += 1;
    }

    prvt = id;
    prvt2 = id+MAGICNO;

    #pragma omp barrier
    if (prvt != id) {
      #pragma omp critical
      errors += 1;
    }
    #pragma omp barrier
    if (prvt2 != id+MAGICNO) {
      #pragma omp critical
      errors += 1;
    }
  }


  prvt  = MAGICNO*2;
  prvt2 = MAGICNO*2+1;
  #pragma omp parallel firstprivate (prvt) firstprivate(prvt2)
  func1 (MAGICNO*2, &prvt, &prvt2);


  if (errors == 0) {
    printf ("firstprivate 002 : SUCCESS\n");
    return 0;
  } else {
    printf ("firstprivate 002 : FAILED\n");
    return 1;
  }
}
