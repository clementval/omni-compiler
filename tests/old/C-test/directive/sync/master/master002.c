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
/* master 001:
 * master directive の前後に barrier 同期が存在しないことを確認
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;


main ()
{
  int	tflag = 0, lflag = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);

  #pragma omp parallel
  {
    int	id = omp_get_thread_num ();

    #pragma omp barrier

    if (id == 0) {
      waittime (1);
      tflag = 1;
    }
    #pragma omp master
    {
      lflag = 1;
    }

    #pragma omp flush
    if (id != 0) {
      if(tflag != 0) {
	#pragma omp critical
	errors += 1;
      }
      if(lflag != 0) {
	#pragma omp critical
	errors += 1;
      }
    }
  }


  if (errors == 0) {
    printf ("master for 002 : SUCCESS\n");
    return 0;
  } else {
    printf ("master for 002 : FAILED\n");
    return 1;
  }
}
