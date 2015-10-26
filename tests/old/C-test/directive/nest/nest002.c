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
/* netsting 002 :
 * check nested parallel region at nested parallel is enabled.
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;


int	sum;


void
func_nesting ()
{
  #pragma omp parallel
  {
    int	add;

    if (omp_get_num_threads () == 1) {
      add = 2;
      printf ("nested parallel is serialized.\n");
    } else {
      add = 1;
    }

    #pragma omp critical
    {
      sum += add;
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
  omp_set_num_threads (2);
  omp_set_nested (1);
  if (omp_get_nested () == 0) {
    printf ("test skipped.\n");
    exit(0);
  }

  sum = 0;
  #pragma omp parallel
  {
    #pragma omp parallel
    {
      int	add;

      if (omp_get_num_threads () == 1) {
	add = 2;
	printf ("nested parallel is serialized.\n");
      } else {
	add = 1;
      }

      #pragma omp critical
      {
	sum += add;
      }
    }
  }
  if (sum != 2*2) {	
    errors += 1;
  }


  sum = 0;
  #pragma omp parallel
  func_nesting ();
  if (sum != 2*2) {	
    errors += 1;
  }


  if (errors == 0) {
    printf ("nesting 002 : SUCCESS\n");
    return 0;
  } else {
    printf ("nesting 002 : FAILED\n");
    return 1;
  }
}
