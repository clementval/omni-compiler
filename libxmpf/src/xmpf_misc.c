#include <stdlib.h>
#include "xmpf_internal.h"
#include "config.h"
//#define DBG 1

/*
 * For xmpf, initialize all
 */

void xmpf_init_all__()
{
  _XMP_init(0, NULL);

  _XMP_check_reflect_type();

  _XMPC_running = 0;
  _XMPF_running = 1;

  _xmp_pack_array = _XMPF_pack_array;
  _xmp_unpack_array = _XMPF_unpack_array;

#if defined(_XMP_GASNET) || defined(_XMP_FJRDMA) || defined(_XMP_MPI3_ONESIDED)
  /* for Coarray Fortran environment */
  _XMPF_coarray_init();
#endif

#if defined(OMNI_TARGET_CPU_KCOMPUTER) && defined(K_RDMA_REFLECT)
  FJMPI_Rdma_init();
#endif
}

//extern double t_sched, t_start, t_wait;

void xmpf_finalize_all__()
{

  //  xmpf_dbg_printf("sched = %f, start = %f, wait = %f\n", t_sched, t_start, t_wait);

#if defined(_XMP_GASNET) || defined(_XMP_FJRDMA) || defined(_XMP_MPI3_ONESIDED)
  xmpf_sync_all_auto_();
#endif

  xmpf_finalize_each__();
}

void xmpf_finalize_each__()
{

#if defined(OMNI_TARGET_CPU_KCOMPUTER) && defined(K_RDMA_REFLECT)
  FJMPI_Rdma_finalize();
#endif

  _XMP_finalize(0);
}


/*
 * dummy routines
 *  This routine will be called only if the user program does not
 *  require to generate the initialization routines for modules.
 */
//void xmpf_traverse_module_(void) { }
//void xmpf_traverse_initcoarray_(void) { }


void xmpf_debug_()
{
  int flag = 0;
  MPI_Initialized(&flag);
  printf("xmpf_debug init flag=%d\n",flag);
  if (!flag) {
    MPI_Init(NULL, NULL);
  }
  printf("_XMP_world_size=%d, _XMP_world_rank=%d\n",
	 _XMP_world_size, _XMP_world_rank);
  {
    int myrank, nproc;
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&nproc);
    printf("nproc=%d myrank=%d\n", nproc, myrank);
  }
}

#include <string.h>

void xmpf_print_(char *msg, int l)
{
  char buf[512];
  strncpy(buf,msg,(size_t)l);
  buf[l] = '\0';
  printf("[%d] %s\n",_XMP_world_rank, buf);
  MPI_Barrier(MPI_COMM_WORLD);
}


void xmpf_dbg_printf(char *fmt,...)
{
  char buf[512];
  va_list args;

  va_start(args,fmt);
  vsprintf(buf,fmt,args);
  va_end(args);

  printf("[%d] %s",_XMP_world_rank, buf);
  fflush(stdout);
}


void xmpf_array___(_XMP_array_t **a_desc)
{
  _XMP_array_t *a = *a_desc;
  xmpf_dbg_printf("array : a->array_addr_p = %p\n", a->array_addr_p);
}


/* void dumy(void) */
/* { */
/*   _XMP_pack_array(NULL, NULL, 0, (size_t)0, 0, NULL, NULL, NULL, NULL); */
/*   _XMP_unpack_array(NULL, NULL, 0, (size_t)0, 0, NULL, NULL, NULL, NULL); */
/* } */


size_t _XMP_get_datatype_size(int datatype)
{
  size_t size;

  // size of each type is obtained from config.h.
  // Note: need to fix when building a cross compiler.
  switch (datatype){

  case _XMP_N_TYPE_BOOL:
    size = _XMPF_running ? SIZEOF_UNSIGNED_INT : SIZEOF__BOOL;
    break;

  case _XMP_N_TYPE_CHAR:
  case _XMP_N_TYPE_UNSIGNED_CHAR:
    size = SIZEOF_UNSIGNED_CHAR; break;

  case _XMP_N_TYPE_SHORT:
  case _XMP_N_TYPE_UNSIGNED_SHORT:
    size = SIZEOF_UNSIGNED_SHORT; break;

  case _XMP_N_TYPE_INT:
  case _XMP_N_TYPE_UNSIGNED_INT:
    size = SIZEOF_UNSIGNED_INT; break;

  case _XMP_N_TYPE_LONG:
  case _XMP_N_TYPE_UNSIGNED_LONG:
    size = SIZEOF_UNSIGNED_LONG; break;

  case _XMP_N_TYPE_LONGLONG:
  case _XMP_N_TYPE_UNSIGNED_LONGLONG:
    size = SIZEOF_UNSIGNED_LONG_LONG; break;

  case _XMP_N_TYPE_FLOAT:
#ifdef __STD_IEC_559_COMPLEX__
  case _XMP_N_TYPE_FLOAT_IMAGINARY:
#endif
    size = SIZEOF_FLOAT; break;

  case _XMP_N_TYPE_DOUBLE:
#ifdef __STD_IEC_559_COMPLEX__
  case _XMP_N_TYPE_DOUBLE_IMAGINARY:
#endif
    size = SIZEOF_DOUBLE; break;

  case _XMP_N_TYPE_LONG_DOUBLE:
#ifdef __STD_IEC_559_COMPLEX__
  case _XMP_N_TYPE_LONG_DOUBLE_IMAGINARY:
#endif
    size = SIZEOF_LONG_DOUBLE; break;

  case _XMP_N_TYPE_FLOAT_COMPLEX:
    size = SIZEOF_FLOAT * 2; break;

  case _XMP_N_TYPE_DOUBLE_COMPLEX:
    size = SIZEOF_DOUBLE * 2; break;

  case _XMP_N_TYPE_LONG_DOUBLE_COMPLEX:
    size = SIZEOF_LONG_DOUBLE * 2; break;

  case _XMP_N_TYPE_NONBASIC: // should be fixed for structures.
  default:
    size = 0; break;
  }

  return size;
}


void xmp_desc_of_(){
}
