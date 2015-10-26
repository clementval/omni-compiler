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
/* private 004 :
 * 複数の変数が宣言された場合のprivate 宣言の動作確認
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;


int	prvt1, prvt2, prvt3;


void
func1 (int *prvt1, int *prvt2, int *prvt3)
{
  int	id = omp_get_thread_num ();

  *prvt1 = id;
  *prvt2 = id;
  *prvt3 = id;
  #pragma omp barrier

  if (*prvt1 != id  ||  *prvt2 != id  ||  *prvt3 != id) {
    #pragma omp critical
    errors += 1;
  }
}


void
func2 ()
{
  static int	err;
  int		id = omp_get_thread_num ();

  prvt1 = id;
  prvt2 = id;
  prvt3 = id;
  err  = 0;
  #pragma omp barrier

  if (prvt1 != id) {
    #pragma omp critical
    err += 1;
  }
  if (prvt2 != id) {
    #pragma omp critical
    err += 1;
  }
  if (prvt3 != id) {
    #pragma omp critical
    err += 1;
  }
  #pragma omp barrier
  #pragma omp master
  if (err != (thds - 1)*3) {
    #pragma omp critical
    errors ++;
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


  #pragma omp parallel private(prvt1) private(prvt2, prvt3) 
  {
    int	id = omp_get_thread_num ();

    prvt1 = id;
    prvt2 = id;
    prvt3 = id;
    #pragma omp barrier

    if (prvt1 != id  ||  prvt2 != id  ||  prvt3 != id) {
      #pragma omp critical
      errors += 1;
    }
  }


  #pragma omp parallel private(prvt1) private(prvt2, prvt3)
  func1 (&prvt1, &prvt2, &prvt3);


  #pragma omp parallel private(prvt1) private(prvt2, prvt3)
  func2 ();


  if (errors == 0) {
    printf ("private 004 : SUCCESS\n");
    return 0;
  } else {
    printf ("private 004 : FAILED\n");
  }
}
