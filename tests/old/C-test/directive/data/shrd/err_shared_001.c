static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of shared 001 :
 * for �� shared ������Ǥ��ʤ������ǧ
 */

#include <omp.h>


int	errors = 0;
int	thds;

int	shrd;


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel
  {
    int	i;

    #pragma omp for shared (shrd)
    for (i=0; i<thds; i++){	
      #pragma omp critical
      shrd += 1;
    }
  }


  printf ("err_shared 001 : FAILED, can not compile this program.\n");
  return 1;
}
