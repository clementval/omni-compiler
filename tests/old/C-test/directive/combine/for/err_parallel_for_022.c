static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of parallel for 022:
 * runtime�������塼��󥰤ǡ�stride ����ꤷ�����˥��顼�ˤʤ뤳�Ȥ��ǧ
 */

#include <omp.h>

#define	MAX_STRIDE	10
#define LOOPNUM		(MAX_STRIDE*thds)

int	thds;
int	*buf;


void
clear ()
{
  int lp;
  
  for (lp=0; lp<=LOOPNUM; lp++) {
    buf[lp] = -1;
  }
}


main ()
{
  int	lp;

  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  buf = (int *) malloc (sizeof (int) * (LOOPNUM + 1));
  if (buf == NULL) {
    printf ("can not allocate memory.\n");
    exit (1);
  }
  omp_set_dynamic (0);

  clear ();
  #pragma omp parallel for schedule (runtime,1)
  for (lp=0; lp<LOOPNUM; lp++) {
    buf[lp] = omp_get_thread_num ();
  }

  printf ("err_parallel_for 022 : FAILED, can not compile this program.\n");
  return 1;
}
