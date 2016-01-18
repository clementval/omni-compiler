static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* reduction 025 :
 * parallel sections �� reduction ��������줿����ư���ǧ
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;

int	rdct;


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);

  #pragma omp parallel sections reduction(+:rdct)
  {
    #pragma omp section
    rdct += 1;
    #pragma omp section
    rdct += 1;
  }

  if (rdct != 2) {
    errors += 1;
  }


  if (errors == 0) {
    printf ("reduction 025 : SUCCESS\n");
    return 0;
  } else {
    printf ("reduction 025 : FAILED\n");
    return 1;
  }
}
