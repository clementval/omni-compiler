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
/* firstprivate 027 :
 * firstprivate ��������ѿ���for loop �Υ����󥿤˻��ѡ�
 */

#include <omp.h>
#include "omni.h"


#define MAGICNO	100

int	errors = 0;
int	thds;

int	prvt;


main ()
{
  int	sum = 0;

  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel 
  {

    #pragma omp for firstprivate(prvt) 
    for (prvt=0; prvt<thds; prvt ++) {
      #pragma omp critical
      sum += 1;
    }
  }

  if (sum != thds) {
    errors += 1;
  }


  if (errors == 0) {
    printf ("firstprivate 027 : SUCCESS\n");
    return 0;
  } else {
    printf ("firstprivate 027 : FAILED\n");
    return 1;
  }
}
