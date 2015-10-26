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
/* omp_set_lock 003:
 * lock変数毎に、個別に制御ができる事を確認。
 */

#include <omp.h>
#include "omni.h"


main ()
{
  omp_lock_t	lck, lck2;
  int		thds;

  int		errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi thread.\n");
    exit (0);
  }

  omp_init_lock(&lck);
  omp_init_lock(&lck2);

  #pragma omp parallel sections
  {
    #pragma omp section
    {
      barrier (2);

      omp_set_lock (&lck);
      barrier (2);
      omp_unset_lock (&lck);

      omp_set_lock (&lck2);
      barrier (2);
      omp_unset_lock (&lck2);
    }

    #pragma omp section
    {
      barrier (2);

      omp_set_lock (&lck2);
      barrier (2);
      omp_unset_lock (&lck2);

      omp_set_lock (&lck);
      barrier (2);
      omp_unset_lock (&lck);
    }
  }


  if (errors == 0) {
    printf ("omp_set_lock 003 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_set_lock 003 : FAILED\n");
    return 1;
  }
}
