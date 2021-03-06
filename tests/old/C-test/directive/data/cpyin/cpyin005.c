static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* copyin 005 :
 * long型変数に対して copyin 宣言をした場合の動作確認
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;


long	org;
long	prvt;
#pragma omp threadprivate(prvt)


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  prvt = org = -1;

  #pragma omp parallel copyin (prvt)
  {
    if (prvt != org  || sizeof(prvt) != sizeof(long)) {
      #pragma omp critical
      errors += 1;
    }
  }

  prvt = org = 0;

  #pragma omp parallel copyin (prvt)
  {
    if (prvt != org  || sizeof(prvt) != sizeof(long)) {
      #pragma omp critical
      errors += 1;
    }
  }

  prvt = org = 1;

  #pragma omp parallel copyin (prvt)
  {
    if (prvt != org  || sizeof(prvt) != sizeof(long)) {
      #pragma omp critical
      errors += 1;
    }
  }


  if (errors == 0) {
    printf ("copyin 005 : SUCCESS\n");
    return 0;
  } else {
    printf ("copyin 005 : FAILED\n");
    return 1;
  }
}
