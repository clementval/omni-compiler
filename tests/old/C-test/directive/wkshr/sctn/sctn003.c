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
/* sections 003:
 * sections directive に section が現われないケース
 */

#include <omp.h>
#include "omni.h"


int	thds;
int	buf[3];


void
func_sections()
{
  #pragma omp sections
  {
    {
      buf[0] += 1;
      buf[1] += 2; 
      buf[2] += 3;
    }
  }
}


main ()
{

  int	errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  memset (buf, 0, sizeof (buf));
  #pragma omp parallel
  {
    #pragma omp sections
    {
      {
	buf[0] += 1;
	buf[1] += 2;
	buf[2] += 3;
      }
    }
  }

  if (buf[0] != 1  ||  buf[1] != 2  ||  buf[2] != 3) {
    errors += 1;
  }

  memset (buf, 0, sizeof (buf));
  #pragma omp parallel
  {
    func_sections ();
  }

  if (buf[0] != 1  ||  buf[1] != 2  ||  buf[2] != 3) {
    errors += 1;
  }


  if (errors == 0) {
    printf ("sections 003 : SUCCESS\n");
    return 0;
  } else {
    printf ("sections 003 : FAILED\n");
    return 1;
  }
}
