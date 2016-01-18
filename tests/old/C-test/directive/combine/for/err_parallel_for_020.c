static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of parallel for 020:
 * nowait �����ꤵ�줿���Υ��顼���ǧ
 */

#include <omp.h>

main ()
{
  int	lp, thds;

  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);

  #pragma omp parallel for nowait
  for (lp=0; lp<thds; lp++) {
  }

  printf ("err_parallel_for 020 : FAILED, can not compile this program.\n");
  return 1;
}
