static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of netsting 024 :
 * sections ����� barrier ��¸�ߤ�����
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
    #pragma omp sections
    {
      #pragma omp section
      {
	#pragma omp barrier
      }
    }
  }


  printf ("err_nesting 024 : FAILED, can not compile this program.\n");
  return 1;
}
