static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* omp_set_dynamic : 001
 * omp_set_dynamic�ǡ�dynamic scheduling �� 
 * enable/disable ��������ư����ǧ
 * dynamic scheduling �ϼ�����¸�ʤΤǡ��������塼��󥰼��Τϳ�ǧ���ʤ���
 * ��ǧ�ϡ�API�Τߡ�
 */

#include <omp.h>
#include "omni.h"


int
main ()
{
  int	errors = 0;


  omp_set_dynamic (1);
  if(omp_get_dynamic () == 0) {
    printf ("dynamic_threads is not implement.\n");
    goto END;
  }

  omp_set_dynamic (0);
  if(omp_get_dynamic () != 0) {
    errors += 1;
  }

  omp_set_dynamic (1);
  if(omp_get_dynamic () == 0) {
    errors += 1;
  }


 END:
  if (errors == 0) {
    printf ("omp_set_dynamic 001 : SUCCESS\n");
    return 0;
  } else {
    printf ("omp_set_dynamic 001 : FAILED\n");
    return 1;
  }
}
