static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of default 007 :
 * critical ���Ф��� default �����ꤵ�줿����ư���ǧ
 */

#include <omp.h>


int	errors = 0;
int	thds;

int	shrd;


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
    #pragma omp atomic default(shared)
    shrd += 1;
  }


  printf ("err_default 007 : FAILED, can not compile this program.\n");
  return 1;
}
