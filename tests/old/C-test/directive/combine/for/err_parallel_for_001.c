static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of parallel for 001:
 * ���ܥ֥�å����Ф��ơ�parallel for ����ꤷ�����
 */

#include <omp.h>


int	errors = 0;


main ()
{

  #pragma omp parallel for
  {
    errors = 1;
  }

  printf ("err_parallel_for 001 : FAILED, can not compile this program.\n");
  return 1;
}
