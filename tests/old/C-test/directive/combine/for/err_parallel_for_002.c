static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of parallel for 002:
 * while に対して、parallel for を指定した場合
 */

#include <omp.h>


main ()
{
  int	true = 1;

  #pragma omp parallel for
  while (true) {
    true = 0;
  }

  printf ("err_parallel_for 002 : FAILED, can not compile this program.\n");
  return 1;
}
