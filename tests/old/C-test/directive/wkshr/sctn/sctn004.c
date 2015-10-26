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
/* sections 004:
 * sections が並列で実行されていることを確認
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	buf[2];

int	errors = 0;


void
clear()
{
  int	i;

  for (i=0; i<2; i++) {
    buf[i] = -1;
  }
}


void
check ()
{
  int	i;


  if (buf[0] == buf[1]) {
    errors += 1;
  }
  for (i=0; i<2; i++) {
    if (buf[i] == -1) {
      errors += 1;
    }
  }
}


void
func_sections()
{
  #pragma omp sections
  {
    #pragma omp section
    {
      buf[0] = omp_get_thread_num ();
      if (omp_get_num_threads () != 1) {
	barrier (2);
      }
    }

    #pragma omp section
    {
      buf[1] = omp_get_thread_num ();
      if (omp_get_num_threads () != 1) {
	barrier (2);
      }
    }
  }
}


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  clear ();
  #pragma omp parallel
  {
    #pragma omp sections
    {
      #pragma omp section
      {
	buf[0] = omp_get_thread_num ();
	barrier (2);
      }

      #pragma omp section
      {
	buf[1] = omp_get_thread_num ();
	barrier (2);
      }
    }
  }
  check ();


  clear();
  #pragma omp parallel
  {
    func_sections ();
  }
  check ();


  clear();
  func_sections ();
  check ();


  if (errors == 1) {
    printf ("sections 004 : SUCCESS\n");
    return 0;
  } else {
    printf ("sections 004 : FAILED\n");
    return 1;
  }
}
