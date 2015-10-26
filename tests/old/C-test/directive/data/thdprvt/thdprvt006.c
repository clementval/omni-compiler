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
/* threadprivate 006 :
 * parallel section �֤�threadprivate���ͤ��ݾڤ���Ƥ�������ǧ��
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;

int	i;
#pragma omp threadprivate (i)


void
func_init ()
{
  i = omp_get_thread_num ();
}


void
func_check ()
{
  if(i != omp_get_thread_num ()) {
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

  #pragma omp parallel
  {
    i = omp_get_thread_num ();
  }
  i = omp_get_thread_num ();
  
  #pragma omp parallel
  {
    if(i != omp_get_thread_num ()) {
      #pragma omp critical
      errors += 1;
    }
  }


  #pragma omp parallel 
  func_init ();
  i = omp_get_thread_num ();
  #pragma omp parallel
  func_check ();


  func_init ();
  func_check ();


  if (errors == 0) {
    printf ("threadprivate 006 : SUCCESS\n");
    return 0;
  } else {
    printf ("threadprivate 006 : FAILED\n");
    return 1;
  }
}
