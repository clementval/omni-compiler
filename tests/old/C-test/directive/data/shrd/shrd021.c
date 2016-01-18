static char rcsid[] = "$Id$";
/* 
 * $TSUKUBA_Release: Omni OpenMP Compiler 3 $
 * $TSUKUBA_Copyright:
 *  PLEASE DESCRIBE LICENSE AGREEMENT HERE
 *  $
 */
/* shared 021 :
 * shared ��������ѿ���for directive��chunk�������˻��ꤷ������ư����ǧ
 */

#include <omp.h>
#include "omni.h"


#define	LOOPNUM	(100 * thds)

int	errors = 0;
int	thds, *buff;

int	shrd;


void
check(int s)
{
  int	i,j, id;

  for (i=0; i<LOOPNUM; i+=s) {
    id = (i/s) % thds;

    for (j=0; j<s; j++) {
      if ((i+j) < LOOPNUM) {
	if (buff[i+j] != id) {
	  #pragma omp critical
	  errors += 1;
	}
      }
    }
  }
}


main ()
{
  thds = omp_get_max_threads ();
  if (thds == 1) {
    printf ("should be run this program on multi threads.\n");
    exit (0);
  }
  buff = (int *)malloc(sizeof(int) * LOOPNUM);
  if (buff == NULL) {
    printf ("can not allocate memory.\n");
  }

  omp_set_dynamic (0);


  #pragma omp parallel shared(shrd) 
  {
    int	i, j;

    for (j=1; j<=10; j++) {
      shrd = j;
      #pragma omp barrier
      #pragma omp for schedule(static, shrd)
      for (i=0; i<LOOPNUM; i++) {
	buff[i] = omp_get_thread_num ();
      }
      check (shrd);

      #pragma omp barrier
    }
  }


  if (errors == 0) {
    printf ("shared 021 : SUCCESS\n");
    return 0;
  } else {
    printf ("shared 021 : FAILED\n");
    return 1;
  }
}
