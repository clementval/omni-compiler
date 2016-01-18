static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* threadprivate 023 :
 * threadprivate�˥ݥ����ѿ�����ꤷ������ư���ǧ
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;

void 	*i;
#pragma omp threadprivate (i)


void
func ()
{
  int	id = omp_get_thread_num ();

  i = (void *)id;
  #pragma omp barrier

  if (i != (void *)id) {
    #pragma omp critical
    errors += 1;
  }
  if (sizeof (i) != sizeof (void *)) {
    #pragma omp critical
    errors += 1;
  }
}


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
    int	id = omp_get_thread_num ();

    i = (void *)id;
    #pragma omp barrier

    if (i != (void *)id) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof (i) != sizeof (void *)) {
      #pragma omp critical
      errors += 1;
    }
  }

  #pragma omp parallel 
  func ();

  func ();


  if (errors == 0) {
    printf ("threadprivate 023 : SUCCESS\n");
    return 0;
  } else {
    printf ("threadprivate 023 : FAILED\n");
    return 1;
  }
}
