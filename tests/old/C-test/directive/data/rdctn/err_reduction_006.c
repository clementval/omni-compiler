static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of reduction 006 :
 * firstprivate ������줿�ѿ����Ф��� reduction ������������
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;


int	rdct;


main ()
{
  int	i;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);

  #pragma omp parallel for lastprivate (rdct) reduction(+:rdct)
  for (i=0;i<thds;i++) {
    rdct += i;
  }


  printf ("err_reduction 006 : FAILED, can not compile this program.\n");
  return 1;
}
