static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of for 017:
 * loop counter �� short or long �ѿ�(not int)�����ꤵ�줿��硢���顼�ˤʤ뤳�Ȥ��ǧ��
 * canonical shape is :
 *   for (init-expr; var logical-op b; incr-expr)
 *   init-expr = var = lb
 *   incr-expr = ++var,
 *		 var++,
 *		 --var,
 *		 var--,
 *		 var += incr,
 *		 var -= incr,
 *		 var = var + incr,
 *		 var = incr + var,
 *		 var = var - incr,
 *   logical-op = <, <=, >, >=
 */

#include <limits.h>
#include <omp.h>

int	ret_same (int);
int	thds;
int	*buf;


void clear ()
{
  int lp;

  for (lp=0; lp<=thds; lp++) {
    buf[lp] = 0;
  }
}


int
check_result (int v)
{
  int	lp;

  int	err = 0;


  for (lp = 0; lp<thds; lp++) {
    if (buf[lp] != v) {
      err += 1;
    }
  }
  if (buf[thds] != 0) {
    err += 1;
  }

  return err;
}


void
test_for_001 ()
{
#if (INT_MAX == SHORT_MAX)
  long	lp;
#else
  short lp;
#endif

  #pragma omp for
  for (lp=0; lp<thds; lp++) {
    buf[lp] += omp_get_num_threads ();
  }
}


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  buf = (int *) malloc (sizeof (int) * (thds + 1));
  if (buf == NULL) {
    printf ("can not allocate memory.\n");
    exit (1);
  }
  omp_set_dynamic (0);

  clear ();
  #pragma omp parallel
  test_for_001 ();
  check_result (thds);

  printf ("err_for 017 : FAILED, can not compile this program.\n");
  return 1;
}
