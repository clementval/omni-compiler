static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of private 004 :
 * threadprivate ������줿�ѿ��� private ������줿����ư���ǧ
 */

#include <omp.h>


int	errors = 0;
int	thds;


int	prvt;
#pragma omp threadprivate (prvt)


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel private (prvt)
  {
    int	id = omp_get_thread_num ();

    prvt = id;
    #pragma omp barrier

    if (prvt != id) {
      errors += 1;
    }
  }


  printf ("err_private 004 : FAILED, can not compile this program.\n");
  return 1;
}
