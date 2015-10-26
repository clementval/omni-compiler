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
/* omp_get_dynamic : 001
 * omp_get_dynamicで、dynamic schedulingがenable/disableを読み出します。
 * dynamic scheduling は実装依存なので、スケジューリング自体は確認しない。
 * 確認は、APIのみ。
 */

#include <omp.h>
#include "omni.h"


int
main ()
{
  int	errors = 0;


  omp_set_dynamic (0);
  if(omp_get_dynamic () != 0) {
    errors += 1;
  }

  omp_set_dynamic (1);
  if(omp_get_dynamic () == 0) {
    printf ("dynamic_threads is not implement.\n");
    goto END;
  }

  omp_set_dynamic (0);
  if(omp_get_dynamic () != 0) {
    errors += 1;
  }

 END:
  if (errors == 0) {
    printf ("omp_get_dynamic 001 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_get_dynamic 001 : FAILED\n");
    return 1;
  }
}
