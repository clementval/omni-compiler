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
/* critical 007:
 * ラベル名付きcritical directive指定された処理が、
 * 異るチーム間でも排他処理が行われることを確認
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	errors = 0;

int	data;


void
clear ()
{
  data = 0;
}


int
read_data ()
{
  return data;
}


void
write_data (int d)
{
  data = d;
}


void
check (int n)
{
  if (data != n) {
    errors += 1;
  }
}


void
func_critical ()
{
  #pragma omp critical (label)
  {
    int i;

    i = read_data ();
    waittime (1);
    write_data (i+1);
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
  omp_set_nested(0);


  clear ();
  #pragma omp parallel
  {
    #pragma omp barrier

    #pragma omp parallel
    {
      /* this nested parallel region is serialized. */
      #pragma omp critical (name)
      {
	int i;

	i = read_data ();
	waittime (1);
	write_data (i+1);
      }
    }
  }
  check (thds);

  clear ();
  #pragma omp parallel
  {
    #pragma omp barrier

    #pragma omp parallel
    {
      /* this nested parallel region is serialized. */
      func_critical ();
    }
  }
  check (thds);


  clear ();
  func_critical ();
  check (1);


  if (errors == 0) {
    printf ("critical 007 : SUCCESS\n");
    return 0;
  } else {
    printf ("critical 007 : FAILED\n");
    return 1;
  }
}
