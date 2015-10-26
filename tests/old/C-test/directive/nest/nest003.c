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
/* netsting 003 :
 * for,sections,single が parallel にbinding 出来る事を確認
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;
int	sum_for, sum_sct, sum_sngl;


void
func ()
{
  int		i;

  #pragma omp for 
  for (i=0; i<thds; i++) {
    #pragma omp critical
    sum_for += 1;
  }

  #pragma omp sections
  {
    #pragma omp section
    {
      #pragma omp critical
      sum_sct += 1;
    }
    #pragma omp section
    {
      #pragma omp critical
      sum_sct += 1;
    }
    #pragma omp section
    {
      #pragma omp critical
      sum_sct += 1;
    }
  }

  #pragma omp single
  {
    #pragma omp critical
    {
      sum_sngl += 1;
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


  sum_for = 0;
  sum_sct = 0;
  sum_sngl = 0;

  #pragma omp parallel
  {
    int		i;

    #pragma omp for 
    for (i=0; i<thds; i++) {
      #pragma omp critical
      sum_for += 1;
    }

    #pragma omp sections
    {
      #pragma omp section
      {
	#pragma omp critical
	sum_sct += 1;
      }
      #pragma omp section
      {
	#pragma omp critical
	sum_sct += 1;
      }
      #pragma omp section
      {
	#pragma omp critical
	sum_sct += 1;
      }
    }

    #pragma omp single
    {
      #pragma omp critical
      {
	sum_sngl += 1;
      }
    }
  }

  if (sum_for != thds) {
    errors += 1;
  }
  if (sum_sct != 3) {
    errors += 1;
  }
  if (sum_sngl != 1) {
    errors += 1;
  }


  sum_for = 0;
  sum_sct = 0;
  sum_sngl = 0;

  #pragma omp parallel
  func ();

  if (sum_for != thds) {
    errors += 1;
  }
  if (sum_sct != 3) {
    errors += 1;
  }
  if (sum_sngl != 1) {
    errors += 1;
  }


  if (errors == 0) {
    printf ("nesting 003 : SUCCESS\n");
    return 0;
  } else {
    printf ("nesting 003 : FAILED\n");
    return 1;
  }
}
