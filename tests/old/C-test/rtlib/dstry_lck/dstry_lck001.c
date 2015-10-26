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
/* omp_destroy_lock 001:
 * omp_destroy_lock の動作確認
 */

#include <omp.h>
#include "omni.h"


main ()
{
  omp_lock_t	lck, lck2, lck3;
  int		i;

  int	errors = 0;


  for (i=0; i<2; i++) {
    omp_init_lock (&lck);
    omp_destroy_lock (&lck);

    omp_init_lock (&lck2);
    omp_set_lock (&lck2);
    omp_unset_lock (&lck2);
    omp_destroy_lock (&lck2);

#ifdef __OMNI_SCASH__
    /*
     * Omni on SCASH is not support this case, yet.
     */
    printf ("test skip ! : Omni on SCASH is not support destroy lock variable that is locked anyone.\n");
#else
    omp_init_lock (&lck3);
    omp_set_lock (&lck3);
    omp_destroy_lock (&lck3);
#endif
  }


  if (errors == 0) {
    printf ("omp_destroy_lock 001 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_destroy_lock 001 : FAILED\n");
    return 1;
  }
}
