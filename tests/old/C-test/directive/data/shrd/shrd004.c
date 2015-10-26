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
/* shared 004 :
 * 複数の変数が shared directiveに指定された場合の動作確認
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;


int	shrd1;
int	shrd2;
int	shrd3;


void
func1 (int *shrd)
{
  #pragma omp critical
  *shrd += 1;
  #pragma omp barrier

  if (*shrd != thds) {
    #pragma omp critical
    errors += 1;
  }
}


void
func2 ()
{
  #pragma omp critical
  {
    shrd1 += 1;
    shrd2 += 1;
    shrd3 += 1;
  }
  #pragma omp barrier

  if (shrd1 != thds) {
    #pragma omp critical
    errors += 1;
  }
  if (shrd2 != thds) {
    #pragma omp critical
    errors += 1;
  }
  if (shrd3 != thds) {
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


  shrd1 = shrd2 = shrd3 = 0;
  #pragma omp parallel shared(shrd1,shrd2) shared(shrd3)
  {
    #pragma omp critical
    {
      shrd1 += 1;
      shrd2 += 1;
      shrd3 += 1;
    }

    #pragma omp barrier

    if (shrd1 != thds) {
      #pragma omp critical
      errors += 1;
    }
    if (shrd2 != thds) {
      #pragma omp critical
      errors += 1;
    }
    if (shrd3 != thds) {
      #pragma omp critical
      errors += 1;
    }
  }


  shrd1 = shrd2 = shrd3 = 0;
  #pragma omp parallel shared(shrd1,shrd2,shrd3)
  {
    func1 (&shrd1);
    func1 (&shrd2);
    func1 (&shrd3);
  }


  shrd1 = shrd2 = shrd3 = 0;
  #pragma omp parallel shared(shrd1) shared(shrd2) shared(shrd3)
  func2 ();


  if (errors == 0) {
    printf ("shared 004 : SUCCESS\n");
    return 0;
  } else {
    printf ("shared 004 : FAILED\n");
    return 1;
  }
}
