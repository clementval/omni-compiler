static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of critical 001:
 * critical �˼��̻Ҥ�2�Ļ��ꤵ�줿����ư����ǧ
 */

#include <omp.h>


int errors = 0;


main ()
{
  #pragma omp parallel
  {
    #pragma omp critical (lock1) (lock2)
    {
      errors = 1;
    }
  }

  printf ("err_critical 002 : FAILED, can not compile this program.\n");
  return 1;
}
