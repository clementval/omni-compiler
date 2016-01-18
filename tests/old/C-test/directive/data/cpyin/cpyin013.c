static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* copyin 013 :
 * �ݥ����ѿ����Ф��� copyin ����򤷤�����ư���ǧ
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;


void *	org;
void *	prvt;
#pragma omp threadprivate(prvt)


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  prvt = org = (void *)-1;
  #pragma omp parallel copyin (prvt)
  {
    if (prvt != org || sizeof(prvt) != sizeof(void *)) {
      #pragma omp critical
      errors += 1;
    }
  }


  prvt = org = 0;
  #pragma omp parallel copyin (prvt)
  {
    if (prvt != org || sizeof(prvt) != sizeof(void *)) {
      #pragma omp critical
      errors += 1;
    }
  }


  prvt = org = (void *)1;
  #pragma omp parallel copyin (prvt)
  {
    if (prvt != org || sizeof(prvt) != sizeof(void *)) {
      #pragma omp critical
      errors += 1;
    }
  }


  if (errors == 0) {
    printf ("copyin 013 : SUCCESS\n");
    return 0;
  } else {
    printf ("copyin 013 : FAILED\n");
    return 1;
  }
}
