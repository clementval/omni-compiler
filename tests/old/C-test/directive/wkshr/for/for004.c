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
/* for 004:
 * dynamic スケジューリングを指定した場合の動作を確認
 */

#include <omp.h>
#include "omni.h"


#define	MAX_CHUNK	10
#define LOOPNUM		(MAX_CHUNK*thds)

int ret_same (int);

int	thds;
int	*buf;


void
clear ()
{
  int lp;
  
  for (lp=0; lp<=LOOPNUM; lp++) {
    buf[lp] = -1;
  }
}


int
check_result (int s)
{
  int	lp, lp2, id;

  int	err = 0;


  for (lp=0; lp*s<LOOPNUM; lp++) {
    id = buf[lp*s];
    if (id<0 || thds<=id) {
      err += 1;
    }
    for (lp2=0; lp2<s; lp2++) {
      if (LOOPNUM<=lp*s+lp2) {
	goto LOOPEND;
      }
      if (buf[lp*s+lp2] != id) {
	err += 1;
      }
    }
  }
 LOOPEND:
  if (buf[LOOPNUM] != -1) {
    err += 1;
  }

  return err;
}


main ()
{
  int	lp;

  int	chunk = 3;
  int	errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  buf = (int *) malloc (sizeof (int) * (LOOPNUM + 1));
  if (buf == NULL) {
    printf ("can not allocate memory.\n");
    exit (1);
  }
  omp_set_dynamic (0);

  clear ();
  #pragma omp parallel
  {
    #pragma omp for schedule (dynamic)
    for (lp=0; lp<LOOPNUM; lp++) {
      if (lp != 0) {
	while (buf[lp-1] == -1) {
	  waittime(1); /* for SCASH */
	  #pragma omp flush
	}
      }
      buf[lp] = omp_get_thread_num ();
      #pragma omp flush
    }
  }
  errors += check_result (1);

  clear ();
  #pragma omp parallel
  {
    #pragma omp for schedule (dynamic,1)
    for (lp=0; lp<LOOPNUM; lp++) {
      if (lp != 0) {
	while (buf[lp-1] == -1) {
	  waittime(1); /* for SCASH */
	  #pragma omp flush
	}
      }
      buf[lp] = omp_get_thread_num ();
      #pragma omp flush
    }
  }
  errors += check_result (1);

  clear ();
  #pragma omp parallel
  {
    #pragma omp for schedule (dynamic,2)
    for (lp=0; lp<LOOPNUM; lp++) {
      if (lp != 0) {
	while (buf[lp-1] == -1) {
	  waittime(1); /* for SCASH */
	  #pragma omp flush
	}
      }
      buf[lp] = omp_get_thread_num ();
      #pragma omp flush
    }
  }
  errors += check_result (2);

  clear ();
  #pragma omp parallel
  {
    #pragma omp for schedule (dynamic,chunk)
    for (lp=0; lp<LOOPNUM; lp++) {
      if (lp != 0) {
	while (buf[lp-1] == -1) {
	  waittime(1); /* for SCASH */
	  #pragma omp flush
	}
      }
      buf[lp] = omp_get_thread_num ();
      #pragma omp flush
    }
  }
  errors += check_result (chunk);

  clear ();
  #pragma omp parallel
  {
    #pragma omp for schedule (dynamic,2+1)
    for (lp=0; lp<LOOPNUM; lp++) {
      if (lp != 0) {
	while (buf[lp-1] == -1) {
	  waittime(1); /* for SCASH */
	  #pragma omp flush
	}
      }
      buf[lp] = omp_get_thread_num ();
      #pragma omp flush
    }
  }
  errors += check_result (2+1);

  clear ();
  #pragma omp parallel
  {
    #pragma omp for schedule (dynamic,ret_same(3))
    for (lp=0; lp<LOOPNUM; lp++) {
      if (lp != 0) {
	while (buf[lp-1] == -1) {
	  waittime(1); /* for SCASH */
	  #pragma omp flush
	}
      }
      buf[lp] = omp_get_thread_num ();
      #pragma omp flush
    }
  }
  errors += check_result (ret_same(3));

  clear ();
  #pragma omp parallel
  {
    #pragma omp for schedule (dynamic,ret_same(3)+1)
    for (lp=0; lp<LOOPNUM; lp++) {
      if (lp != 0) {
	while (buf[lp-1] == -1) {
	  waittime(1); /* for SCASH */
	  #pragma omp flush
	}
      }
      buf[lp] = omp_get_thread_num ();
      #pragma omp flush
    }
  }
  errors += check_result (ret_same(3)+1);

  clear ();
  #pragma omp parallel
  {
    int	ln = LOOPNUM;

    #pragma omp for schedule (dynamic,ln+1)
    for (lp=0; lp<LOOPNUM; lp++) {
      if (lp != 0) {
	while (buf[lp-1] == -1) {
	  waittime(1); /* for SCASH */
	  #pragma omp flush
	}
      }
      buf[lp] = omp_get_thread_num ();
      #pragma omp flush
    }
  }
  errors += check_result (LOOPNUM+1);

  if (errors == 0) {
    printf ("for 004 : SUCCESS\n");
    return 0;
  } else {
    printf ("for 004 : FAILED\n");
    return 1;
  }
}


int
ret_same (int i)
{
  return i;
};
