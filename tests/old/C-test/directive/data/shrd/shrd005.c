static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* shared 005 :
 * char���ѿ����Ф��ơ�shared��ؼ���������ư����ǧ
 */

#include <omp.h>
#include "omni.h"


int	errors = 0;
int	thds;


char	shrd;


void
func1 (char *shrd)
{
  #pragma omp critical
  *shrd += 1;
  #pragma omp barrier

  if (*shrd != thds) {
    #pragma omp critical
    errors += 1;
  }
  if (sizeof(*shrd) != sizeof(char)) {
    #pragma omp critical
    errors += 1;
  }
}


void
func2 ()
{
  #pragma omp critical
  shrd += 1;
  #pragma omp barrier

  if (shrd != thds) {
    #pragma omp critical
    errors += 1;
  }
  if (sizeof(shrd) != sizeof(char)) {
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


  shrd = 0;
  #pragma omp parallel shared(shrd)
  {
    #pragma omp critical
    shrd += 1;

    #pragma omp barrier

    if (shrd != thds) {
      #pragma omp critical
      errors += 1;
    }
    if (sizeof(shrd) != sizeof(char)) {
      #pragma omp critical
      errors += 1;
    }
  }


  shrd = 0;
  #pragma omp parallel shared(shrd)
  func1 (&shrd);


  shrd = 0;
  #pragma omp parallel shared(shrd)
  func2 ();


  if (errors == 0) {
    printf ("shared 005 : SUCCESS\n");
    return 0;
  } else {
    printf ("shared 005 : FAILED\n");
    return 1;
  }
}
