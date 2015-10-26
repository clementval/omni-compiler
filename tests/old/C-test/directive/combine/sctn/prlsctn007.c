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
/* parallel sections 007:
 * parallel sections if が成り立たない場合の動作確認
 */

#include <omp.h>
#include "omni.h"


int	thds, ids[2];
int	errors = 0;


int
sameas(int n)
{
  return n;
}


void
check_parallel ()
{
  if (omp_in_parallel () == 0) {
    #pragma omp critical
    errors += 1;
  }
  if (omp_get_num_threads () == 1) {
    #pragma omp critical
    errors += 1;
  }
}


void
check ()
{
  if (ids[0] == ids[1]) {
    errors += 1;
  }
}


main ()
{
  int	 true = 2;
  double dtrue = 3.0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel sections if (1)
  {
    #pragma omp section
    {	
      check_parallel ();
      ids[0] = omp_get_thread_num ();
      barrier (2);
    }
    #pragma omp section
    {	
      check_parallel ();
      ids[1] = omp_get_thread_num ();
      barrier (2);
    }
  }
  check();

  #pragma omp parallel sections if (true)
  {
    #pragma omp section
    {	
      check_parallel ();
      ids[0] = omp_get_thread_num ();
      barrier (2);
    }
    #pragma omp section
    {	
      check_parallel ();
      ids[1] = omp_get_thread_num ();
      barrier (2);
    }
  }
  check();

  #pragma omp parallel sections if (dtrue)
  {
    #pragma omp section
    {	
      check_parallel ();
      ids[0] = omp_get_thread_num ();
      barrier (2);
    }
    #pragma omp section
    {	
      check_parallel ();
      ids[1] = omp_get_thread_num ();
      barrier (2);
    }
  }
  check();

  #pragma omp parallel sections if (true == 2)
  {
    #pragma omp section
    {	
      check_parallel ();
      ids[0] = omp_get_thread_num ();
      barrier (2);
    }
    #pragma omp section
    {	
      check_parallel ();
      ids[1] = omp_get_thread_num ();
      barrier (2);
    }
  }
  check();

  #pragma omp parallel sections if (sameas(true))
  {
    #pragma omp section
    {	
      check_parallel ();
      ids[0] = omp_get_thread_num ();
      barrier (2);
    }
    #pragma omp section
    {	
      check_parallel ();
      ids[1] = omp_get_thread_num ();
      barrier (2);
    }
  }
  check();


  if (errors == 0) {
    printf ("parallel sections 007 : SUCCESS\n");
    return 0;
  } else {
    printf ("parallel sections 007 : FAILED\n");
    return 1;
  }
}
