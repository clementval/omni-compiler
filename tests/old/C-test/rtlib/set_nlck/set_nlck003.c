static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* omp_set_nest_lock 003:
 * ����lock����Ƥ����ѿ����Ф���omp_set_nest_lock��¹Ԥ���ȡ�
 * unlock�����ޤǡ��Ԥ����������ǧ���롣
 * ���ξ��֤ǡ���ʬ������nest lock���̤�����ǧ���롣
 */

#include <omp.h>
#include "omni.h"


main ()
{
  omp_nest_lock_t	lck;
  int			thds;
  volatile int		i;

  int		errors = 0;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi thread.\n");
    exit (0);
  }

  omp_init_nest_lock(&lck);
  i = 0;

  #pragma omp parallel
  {
    int	tmp;

    #pragma omp barrier

    omp_set_nest_lock (&lck);

    #pragma omp flush (i)
    i = i + 1;
    tmp  = i;
    waittime(1);

    #pragma omp flush (i)
    if (i != tmp) {	
      #pragma omp critical
      errors += 1;
    }
    omp_set_nest_lock (&lck);
    omp_unset_nest_lock (&lck);
    waittime(1);

    #pragma omp flush(i)
    if (i != tmp) {	
      #pragma omp critical
      errors += 1;
    }

    omp_unset_nest_lock (&lck);
  }

  if (i != thds) {
    errors += 1;
  }


  if (errors == 0) {
    printf ("omp_set_nest_lock 003 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_set_nest_lock 003 : FAILED\n");
    return 1;
  }
}
