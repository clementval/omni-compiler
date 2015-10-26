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
/* error case of firstprivate 002 :
 * firstprivate 宣言した変数を、再度 firstprivate 宣言することは出来ない
 */

#include <omp.h>


#define	MAGICNO		100

int	errors = 0;
int	thds;


int	prvt;


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  prvt = MAGICNO
  #pragma omp parallel firstprivate(prvt)
  {
    int	id = omp_get_thread_num ();
    int	i;

    #pragma omp for firstprivate(prvt)
    for (i=0; i<thds; i++) {
      prvt += id;
      sleep (1);
      if (prvt != MAGICNO + id) {
	errors += 1;
      }
    }
  }
  printf ("err_firstprivate 002 : FAILED, can not compile this program.\n");
  return 1;
}
