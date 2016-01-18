static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* threadprivate 025 :
 * parallel if �ǻ��Ȥ��Ƥ����ѿ���threadprivate �����������ư����ǧ
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;

int	prvt;
#pragma omp threadprivate(prvt)


void
check_parallel (int n)
{
  if (n == 1) {
    if (omp_in_parallel() != 0) {
      #pragma omp critical
      errors += 1;
    }
    if (omp_get_num_threads() != 1) {
      #pragma omp critical
      errors += 1;
    }

  } else {
    if (omp_in_parallel() == 0) {
      #pragma omp critical
      errors += 1;
    }
    if (omp_get_num_threads() != n) {
      #pragma omp critical
      errors += 1;
    }
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


  prvt = 0;
  #pragma omp parallel if(prvt)
  {
    check_parallel (1);
  }

  prvt = 1;
  #pragma omp parallel if(prvt)
  {
    check_parallel (thds);
  }

  prvt = 2;
  #pragma omp parallel if(prvt)
  {
    check_parallel (thds);
  }


  if (errors == 0) {
    printf ("threadprivate 025 : SUCCESS\n");
    return 0;
  } else {
    printf ("threadprivate 025 : FAILED\n");
    return 1;
  }
}
