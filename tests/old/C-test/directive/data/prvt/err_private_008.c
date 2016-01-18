static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of private 008 :
 * reduction �� private ��Ʊ���ѿ���������줿����ư���ǧ
 */

#include <omp.h>


int	errors = 0;
int	thds;


int	prvt;


main ()
{
  int	i;


  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel for private (prvt) reduction (+:prvt)
  for (i=0;  i<thds;  i++) {
    prvt += omp_get_thread_num ();
  }


  printf ("err_private 008 : FAILED, can not compile this program.\n");
  return 1;
}
