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
/* threadprivate 024 :
 * threadprivateに配列変数を指定した場合の動作確認
 */

#include <omp.h>
#include "omni.h"


#define ARRAYSIZ	1024


int	errors = 0;
int	thds;

int	i[ARRAYSIZ];
#pragma omp threadprivate (i)


void
clear ()
{
  int	j;

  for (j=0; j<ARRAYSIZ; j++) {
    i[j] = j + ARRAYSIZ;
  }
}

void
func ()
{
  int	j;
  int	id = omp_get_thread_num ();

  for (j=0; j<ARRAYSIZ; j++) {
    if (i[j] != j + ARRAYSIZ) {
      #pragma omp critical
      errors += 1;
    }
  }
  for (j=0; j<ARRAYSIZ; j++) {
    i[j] = id + j;
  }
  #pragma omp barrier
  
  for (j=0; j<ARRAYSIZ; j++) {
    if (i[j] != id + j) {
      #pragma omp critical
      errors += 1;
    }
  }
  if (sizeof(i) != sizeof(int) * ARRAYSIZ) {
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
  #pragma omp parallel copyin(i)
  {
    int j;
    int	id = omp_get_thread_num ();

    for (j=0; j<ARRAYSIZ; j++) {
      if (i[j] != j + ARRAYSIZ) {
        #pragma omp critical
	errors += 1;
      }
    }
    for (j=0; j<ARRAYSIZ; j++) {
      i[j] = id + j;
    }
    #pragma omp barrier
  
    for (j=0; j<ARRAYSIZ; j++) {
      if (i[j] != id + j) {
        #pragma omp critical
	errors += 1;
      }
    }
    if (sizeof(i) != sizeof(int) * ARRAYSIZ) {
      #pragma omp critical
      errors += 1;
    }
  }

  clear ();
  #pragma omp parallel copyin(i)
  func ();

  clear ();
  func ();


  if (errors == 0) {
    printf ("threadprivate 024 : SUCCESS\n");
    return 0;
  } else {
    printf ("threadprivate 024 : FAILED\n");
    return 1;
  }
}
