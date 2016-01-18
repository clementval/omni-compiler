static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* lastprivate 014 :
 * �����Τ�lastprivate�������������ư���ǧ
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;

union x {
  int		i;
  double	d;
};


union x	prvt;


void
func (int t)
{
  int	i;


  #pragma omp for schedule(static,1) lastprivate (prvt)
  for (i=0; i<thds; i++) {
    prvt.i = i;
    barrier (t);
    if (prvt.i != i) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(prvt) != sizeof(union x)) {
      #pragma omp critical
      errors += 1;
    }
    if (i==0) {
      waittime (1);
    }
    prvt.i = i;
  }

  if (prvt.i != thds - 1) {
    #pragma omp critical
    errors += 1;
  }
}


main ()
{
  int	i;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel
  {
    #pragma omp for schedule(static,1) lastprivate (prvt)
    for (i=0; i<thds; i++) {
      prvt.i = i;
      barrier (thds);
      if (prvt.i != i) {
	#pragma omp critical
	errors += 1;
      }
      if (sizeof(prvt) != sizeof(union x)) {
        #pragma omp critical
        errors += 1;
      }
      if (i==0) {
	waittime (1);
      }
      prvt.i = i;
    }

    if (prvt.i != thds - 1) {
      #pragma omp critical
      errors += 1;
    }
  }


  #pragma omp parallel
  func (thds);


  func (1);


  if (errors == 0) {
    printf ("lastprivate 014 : SUCCESS\n");
    return 0;
  } else {
    printf ("lastprivate 014 : FAILED\n");
    return 1;
  }
}
