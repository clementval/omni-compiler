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
/* sections 006:
 * nowait を指定した場合の動作を確認
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	buf[3];


int	errors = 0;


void
clear ()
{
  int	i;

  for (i=0; i<3; i++) {
    buf[i] = -1;
  }
}


void
func_sections()
{
  int	id = omp_get_thread_num ();


  #pragma omp barrier

  #pragma omp sections nowait
  {
    #pragma omp section
    {
      buf[0] = omp_get_thread_num ();
      barrier (2);
    }

    #pragma omp section
    {
      barrier (2);
      waittime(1);
      buf[1] = omp_get_thread_num ();
    }
  }

  if (buf[1] != -1  &&  buf[1] != id) {
    #pragma omp critical
    errors += 1;
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
    int	id = omp_get_thread_num ();
    #pragma omp barrier

    #pragma omp sections nowait
    {
      #pragma omp section
      {
	buf[0] = omp_get_thread_num ();
	barrier (2);
      }

      #pragma omp section
      {
	barrier (2);
	waittime(1);
	buf[1] = omp_get_thread_num ();
      }
    }

    if (buf[1] != -1  &&  buf[1] != id) {
      #pragma omp critical
      errors += 1;
    }
  }


  clear ();
  #pragma omp parallel
  {
    func_sections ();
  }


  if (errors == 0) {
    printf ("sections 006 : SUCCESS\n");
    return 0;
  } else {
    printf ("sections 006 : FAILED\n");
    return 1;
  }
}
