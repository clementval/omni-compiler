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
/* parallel sections 005:
 * check implicit barrier at parallel sections.
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


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);
  omp_set_num_threads (2);

  clear ();
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      int id = omp_get_thread_num ();
      if (id == 0) {
	buf[0] = id;
	barrier (2);
      } else {
	barrier (2);
	waittime(1);
	buf[1] = id;
      }
    }

    #pragma omp section
    {
      int id = omp_get_thread_num ();
      if (id == 0) {
	buf[0] = id;
	barrier (2);
      } else {
	barrier (2);
	waittime(1);
	buf[1] = id;
      }
    }
  }

  if (buf[0] == -1) {
    errors += 1;
  }
  if (buf[1] == -1) {
    errors += 1;
  }


  if (errors == 0) {
    printf ("parallel sections 005 : SUCCESS\n");
    return 0;
  } else {
    printf ("parallel sections 005 : FAILED\n");
    return 1;
  }
}
