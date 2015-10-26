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
/* omp_set_nest_lock 001:
 * omp_set_nest_lockの動作確認
 */

#include <omp.h>
#include "omni.h"


main ()
{
  omp_nest_lock_t	lck;

  int			errors = 0;

  omp_init_nest_lock (&lck);
  omp_set_nest_lock (&lck);
  omp_unset_nest_lock (&lck);
  omp_destroy_nest_lock (&lck);

  omp_init_nest_lock (&lck);
  omp_set_nest_lock (&lck);
  omp_unset_nest_lock (&lck);
  omp_destroy_nest_lock (&lck);

  omp_init_nest_lock (&lck);
  omp_set_nest_lock (&lck);
  omp_unset_nest_lock (&lck);
  omp_destroy_nest_lock (&lck);

#ifdef __OMNI_SCASH__
  printf ("skip some tests. because, Omni on SCASH do not support destroy lock variable that is locked anyone.\n");
#else
  omp_init_nest_lock (&lck);
  omp_set_nest_lock (&lck);
  omp_destroy_nest_lock (&lck);

  omp_init_nest_lock (&lck);
  omp_set_nest_lock (&lck);
  omp_set_nest_lock (&lck);
  omp_destroy_nest_lock (&lck);

  omp_init_nest_lock (&lck);	
  omp_set_nest_lock (&lck);

  omp_init_nest_lock (&lck);
  omp_set_nest_lock (&lck);
  omp_set_nest_lock (&lck);
#endif


  if (errors == 0) {
    printf ("omp_set_nest_lock 001 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_set_nest_lock 001 : FAILED\n");
    return 1;
  }
}
