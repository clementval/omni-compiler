static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of for 002:
 * while ���Ф��ơ�for ����ꤷ�����
 */

#include <omp.h>


main ()
{
  int	true = 1;

  #pragma omp parallel
  {
    #pragma omp for
    while (true) {
      true = 0;
    }
  }

  printf ("err_for 002 : FAILED, can not compile this program.\n");
  return 1;
}
