static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* lastprivate 005 :
 * shared��������줿�ѿ��ϡ�lastprivate �ˤǤ��롣
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;

int	prvt;


main ()
{
  int	i;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel shared(prvt)
  {
    #pragma omp for schedule(static,1) lastprivate (prvt)
    for (i=0; i<thds; i++) {
      prvt = i;
      barrier (thds);
      if (prvt != i) {
	#pragma omp critical
	errors += 1;
      }
      if (i==0) {
	waittime (1);
      }
      prvt = i;
    }

    if (prvt != thds - 1) {
      #pragma omp critical
      errors += 1;
    }
  }


  if (errors == 0) {
    printf ("lastprivate 005 : SUCCESS\n");
    return 0;
  } else {
    printf ("lastprivate 005 : FAILED\n");
    return 1;
  }
}
