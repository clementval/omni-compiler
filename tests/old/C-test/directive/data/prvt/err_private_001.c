static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* error case of private 001 :
 * const�����ѿ��� private �˽���ʤ���
 */

#include <omp.h>

#define	MAGICNO	100

int	errors = 0;
int	thds;


const int	prvt = MAGICNO;


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  omp_set_dynamic (0);


  #pragma omp parallel private(prvt)
  {
    if (prvt != MAGICNO) {
      errors += 1;
    }
  }
  printf ("err_private 001 : FAILED, can not compile this program.\n");
  return 1;
}
