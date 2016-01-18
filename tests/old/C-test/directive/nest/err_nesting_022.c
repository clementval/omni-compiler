static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of netsting 022 :
 * for ����� barrier ��¸�ߤ�����
 */

#include <omp.h>


int	errors = 0;
int	thds;
int	sum;


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
    int	i;

    #pragma omp for
    for (i=0; i<1; i++) {
      #pragma omp barrier
    }
  }


  printf ("err_nesting 022 : FAILED, can not compile this program.\n");
  return 1;
}
