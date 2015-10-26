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
/* parallel structure 001:
 * parallel directive test
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	errors = 0;


void
check_parallel (int v)
{
  if (omp_in_parallel () != v) {
    #pragma omp critical
    {
      ERROR (errors);
    }
  }
}



main ()
{
  int true = 1;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);

  check_parallel (0);		      /* not parallel */

  #pragma omp parallel
  check_parallel (1);		      /* here is parallel */

  check_parallel (0);		      /* not parallel */

  #pragma omp parallel
  {				      /* this block is parallel */
    check_parallel(1);
  }

  check_parallel (0);		      /* not parallel */

  #pragma omp parallel 
  if (true) {			      /* this if-block is parallel */
    check_parallel (1);
  }


  if (errors == 0) {
    printf ("parallel 001 : SUCCESS\n");
    return 0;
  } else {
    printf ("parallel 001 : FAILED\n");
    return 1;
  }
}
