#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <complex.h>

int _xmp_omp_num_procs = 1;

void _XMP_pack_vector(char * restrict dst, char * restrict src,
		      int count, int blocklength, long stride){
  long i;
  if (_xmp_omp_num_procs > 1 && count > 8 * _xmp_omp_num_procs){
#pragma omp parallel for private(i)
    for (i = 0; i < count; i++){
      memcpy(dst + i * blocklength, src + i * stride, blocklength);
    }
  }
  else {
    for (i = 0; i < count; i++){
      memcpy(dst + i * blocklength, src + i * stride, blocklength);
    }
  }

}

void _XMP_pack_vector2(char * restrict dst, char * restrict src,
                       int count, int blocklength,
                       int nnodes, int type_size, int src_block_dim){
  long j,k;
  if (src_block_dim == 1){
#pragma omp parallel for private(j,k)
    for (j = 0; j < count; j++){
      for (k = 0; k < nnodes; k++){
        memcpy(dst + ((k * count +j ) * blocklength ) * type_size,
               src + ((k + j * nnodes) * blocklength ) * type_size,
               blocklength * type_size);
      }
    }
  }
}

void _XMP_unpack_vector(char * restrict dst, char * restrict src,
			int count, int blocklength, long stride){
  long i;
  if (_xmp_omp_num_procs > 1 && count > 8 * _xmp_omp_num_procs){
#pragma omp parallel for private(i)
    for (i = 0; i < count; i++){
      memcpy(dst + i * stride, src + i * blocklength, blocklength);
    }
  }
  else {
    for (i = 0; i < count; i++){
      memcpy(dst + i * stride, src + i * blocklength, blocklength);
    }
  }

}

void _XMPF_unpack_transpose_vector(char * restrict dst, char * restrict src,
                                   int dst_stride, int src_stride,
                                   int type_size, int dst_block_dim){
  long i,j;
  if (dst_block_dim == 1){
    if (type_size == 16){
      long ii,jj,imin,jmin,nblk=16;
      double _Complex *dst0 = (double _Complex *)dst;
      double _Complex *src0 = (double _Complex *)src;
      for (jj = 0; jj < src_stride; jj+=nblk){
        jmin=((jj+nblk) < src_stride)? (jj+nblk):src_stride;
#pragma omp parallel for private(i,j,ii,imin)
        for (ii = 0; ii < dst_stride; ii+=nblk){
          imin=((ii+nblk) < dst_stride)? (ii+nblk):dst_stride;
          for (j = jj; j < jmin; j++){
            for (i = ii; i < imin; i++){
              dst0[j * dst_stride + i] = src0[i * src_stride + j];
            }
          }
        }
      }
    }
    else {
      for (j = 0; j < src_stride; j++){
        for (i = 0; i < dst_stride; i++){
          memcpy(dst + (j * dst_stride + i) * type_size,
                 src + (i * src_stride + j) * type_size, type_size);
        }
      }
    }
  }
}

#include "xmp_internal.h"

int _xmp_reflect_pack_flag = 0;

void _XMP_check_reflect_type(void)
{
  char *reflect_type = getenv("XMP_REFLECT_TYPE");
  _xmp_omp_num_procs = omp_get_num_procs();

  if (reflect_type){

    if (strcmp(reflect_type, "REFLECT_NOPACK") == 0){
      _xmp_reflect_pack_flag = 0;
      //xmpf_dbg_printf("REFLECT_NOPACK\n");
      return;
    }
    else if (strcmp(reflect_type, "REFLECT_PACK") == 0){
      _xmp_reflect_pack_flag = 1;
      //xmpf_dbg_printf("REFLECT_PACK\n");
      return;
    }

  }

  // not specified or a wrong value
  if (_xmp_omp_num_procs > 1){
    _xmp_reflect_pack_flag = 1;
    //xmpf_dbg_printf("not specified and REFLECT_PACK\n");
  }
  else {
    _xmp_reflect_pack_flag = 0;
    //xmpf_dbg_printf("not specified and REFLECT_NOPACK\n");
  }

}
