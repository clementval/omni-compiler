static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of parallel structure 001:
 * prallel if ��2�İʾ嵭�Ҥ��줿���ϥ��顼�Ȥʤ롣
 */

#include <omp.h>


main ()
{
  int	true = 1;

  #pragma omp parallel if (1) if (true)
  {
    true = 1;
  }

  printf ("error parallel 001 : can not compile this program.\n");
  return 1;
}
