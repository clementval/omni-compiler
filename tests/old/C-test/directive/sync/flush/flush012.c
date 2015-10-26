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
/* flush 012:
 * nowait付きsections終了時の暗黙のflushを確認
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;
int	flag = 0;
int	chk = 0;


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  errors = 1;
  #pragma omp parallel 
  {
    int id = omp_get_thread_num ();

    #pragma omp sections nowait
    {
      #pragma omp section
      {
      }

      #pragma omp section
      {
	waittime(1);
	flag = 1;
      }
    }

    while (flag != 1) {
      if (id == omp_get_thread_num ()) {
	errors = 0;
      }
      #pragma omp flush
    }
    #pragma omp flush
  }


  if (errors == 0) {
    printf ("flush 012 : SUCCESS\n");
    return 0;
  } else {
    printf ("flush 012 : FAILED\n");
    return 1;
  }
}
