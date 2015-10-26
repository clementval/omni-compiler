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
/* condition compilation 002:
 * define パラメータの値の確認
 */

#include "omni.h"

main ()
{
  int	errors = 0;


  if (_OPENMP != 199810  &&		/* version 1.0 */
      _OPENMP != 200203			/* version 2.0 */
      ) {
    ERROR (errors);
  }

  if (errors == 0) {
    printf ("condition complilation 002 : SUCCESS\n");
    return 0;
  } else {
    printf ("condition complilation 002 : FAILED\n");
    return 1;
  }
}
