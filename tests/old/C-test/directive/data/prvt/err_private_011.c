static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of private 011 :
 * atomic �ˤϡ�private ���������ʤ������ǧ
 */

#include <omp.h>


int	errors = 0;
int	thds;


int	prvt;


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel
  {
    #pragma omp atomic private(prvt)
    prvt += 1;
  }


  printf ("err_private 011 : FAILED, can not compile this program.\n");
  return 1;
}
