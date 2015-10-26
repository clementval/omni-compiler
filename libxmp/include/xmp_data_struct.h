/*
 * $TSUKUBA_Release: Omni Compiler Version 0.9.1 $
 * $TSUKUBA_Copyright:
 *  Copyright (C) 2010-2014 University of Tsukuba, 
 *  	      2012-2014  University of Tsukuba and Riken AICS
 *  
 *  This software is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 published by the Free Software Foundation.
 *  
 *  Please check the Copyright and License information in the files named
 *  COPYRIGHT and LICENSE under the top  directory of the Omni Compiler
 *  Software release kit.
 *  
 *  * The specification of XcalableMP has been designed by the XcalableMP
 *    Specification Working Group (http://www.xcalablemp.org/).
 *  
 *  * The development of this software was partially supported by "Seamless and
 *    Highly-productive Parallel Programming Environment for
 *    High-performance computing" project funded by Ministry of Education,
 *    Culture, Sports, Science and Technology, Japan.
 *  $
 */
#ifndef _XMP_DATA_STRUCT
#define _XMP_DATA_STRUCT
#include <mpi.h>
#include <stdbool.h>
#include "xmp_constant.h"
#if defined(OMNI_TARGET_CPU_KCOMPUTER) && defined(K_RDMA_REFLECT)
#include <mpi-ext.h>
#endif

#define _XMP_comm_t void

// nodes descriptor
typedef struct _XMP_nodes_inherit_info_type {
  int shrink;
  // enable when shrink is false
  int lower;
  int upper;
  int stride;
  // ---------------------------

  int size;
} _XMP_nodes_inherit_info_t;

typedef struct _XMP_nodes_info_type {
  int size;

  // enable when is_member is true
  int rank;
  // -----------------------------
  int multiplier;
} _XMP_nodes_info_t;

typedef struct _XMP_nodes_type {
  unsigned long long on_ref_id;

  int is_member;
  int dim;
  int comm_size;

  // enable when is_member is true
  int comm_rank;
  _XMP_comm_t *comm;
  // -----------------------------

  struct _XMP_nodes_type *inherit_nodes;
  // enable when inherit_nodes is not NULL
  _XMP_nodes_inherit_info_t *inherit_info;
  // -------------------------------------
  _XMP_nodes_info_t info[1];
} _XMP_nodes_t;

typedef struct _XMP_nodes_ref_type {
  _XMP_nodes_t *nodes;
  int *ref;
  int shrink_nodes_size;
} _XMP_nodes_ref_t;

// template desciptor
typedef struct _XMP_template_info_type {
  // enable when is_fixed is true
  long long ser_lower;
  long long ser_upper;
  unsigned long long ser_size;
  // ----------------------------
} _XMP_template_info_t;

typedef struct _XMP_template_chunk_type {
  // enable when is_owner is true
  long long par_lower;
  long long par_upper;
  unsigned long long par_width;
  // ----------------------------

  int par_stride;
  unsigned long long par_chunk_width;
  int dist_manner;
  long long *mapping_array;
  _Bool is_regular_chunk;

  // enable when dist_manner is not _XMP_N_DIST_DUPLICATION
  int onto_nodes_index;
  // enable when onto_nodes_index is not _XMP_N_NO_ONTO_NODES
  _XMP_nodes_info_t *onto_nodes_info;
  // --------------------------------------------------------
} _XMP_template_chunk_t;

typedef struct _XMP_template_type {
  unsigned long long on_ref_id;

  _Bool is_fixed;
  _Bool is_distributed;
  _Bool is_owner;
  
  int   dim;

  // enable when is_distributed is true
  _XMP_nodes_t *onto_nodes;
  _XMP_template_chunk_t *chunk;
  // ----------------------------------

  _XMP_template_info_t info[1];
} _XMP_template_t;

// schedule of reflect comm.
typedef struct _XMP_reflect_sched_type {

  int lo_width, hi_width;
  _Bool is_periodic;

  MPI_Datatype datatype_lo;
  MPI_Datatype datatype_hi;

  MPI_Request req[4];

  void *lo_send_buf, *lo_recv_buf;
  void *hi_send_buf, *hi_recv_buf;

  void *lo_send_array, *lo_recv_array;
  void *hi_send_array, *hi_recv_array;

  int count, blocklength;
  long long stride;

  int lo_rank, hi_rank;

#if defined(_XMP_XACC)
  void *lo_send_host_buf, *lo_recv_host_buf;
  void *hi_send_host_buf, *hi_recv_host_buf;
  void *lo_async_id;
  void *hi_async_id;
  void *event;
#endif
  
#if defined(_XMP_TCA)
  off_t lo_src_offset, lo_dst_offset;
  off_t hi_src_offset, hi_dst_offset;
#endif
} _XMP_reflect_sched_t;

// aligned array descriptor
typedef struct _XMP_array_info_type {
  _Bool is_shadow_comm_member;
  _Bool is_regular_chunk;
  int align_manner;

  int ser_lower;
  int ser_upper;
  int ser_size;

  // enable when is_allocated is true
  int par_lower;
  int par_upper;
  int par_stride;
  int par_size;

  int local_lower;
  int local_upper;
  int local_stride;
  int alloc_size;

  int *temp0;
  int temp0_v;

  unsigned long long dim_acc;
  unsigned long long dim_elmts;
  // --------------------------------

  long long align_subscript;

  int shadow_type;
  int shadow_size_lo;
  int shadow_size_hi;

  _XMP_reflect_sched_t *reflect_sched;
  _XMP_reflect_sched_t *reflect_acc_sched;
  // enable when is_shadow_comm_member is true
  _XMP_comm_t *shadow_comm;
  int shadow_comm_size;
  int shadow_comm_rank;
  // -----------------------------------------

  int align_template_index;

  unsigned long long *acc;

} _XMP_array_info_t;

typedef struct _XMP_array_type {
  _Bool is_allocated;
  _Bool is_align_comm_member;
  int dim;
  int type;
  size_t type_size;

  // enable when is_allocated is true
  void *array_addr_p;
#if defined(OMNI_TARGET_CPU_KCOMPUTER) && defined(K_RDMA_REFLECT)
  uint64_t rdma_addr;
  int rdma_memid;
#endif
#if defined(_XMP_TCA)
  void* tca_handle;
  _Bool set_handle;  // If tca_handle has been set, set_handle = true
  int   dma_slot;
  int   wait_slot;
  int   wait_tag;
#endif
  unsigned long long total_elmts;
  // --------------------------------

  // FIXME do not use these members
  // enable when is_align_comm_member is true
  _XMP_comm_t *align_comm;
  int align_comm_size;
  int align_comm_rank;
  // ----------------------------------------

  _Bool is_shrunk_template;
  _XMP_nodes_t *array_nodes;

  _XMP_template_t *align_template;
  _XMP_array_info_t info[1];
} _XMP_array_t;

typedef struct _XMP_task_desc_type {
  _XMP_nodes_t *nodes;
  int execute;

  unsigned long long on_ref_id;

  int ref_lower[_XMP_N_MAX_DIM];
  int ref_upper[_XMP_N_MAX_DIM];
  int ref_stride[_XMP_N_MAX_DIM];
} _XMP_task_desc_t;

// Note: When member is changed, _XMP_coarray_deallocate() may be changed.
typedef struct xmp_coarray{
  char **addr;      // Pointer to each node.
                    // e.g.) xmp_coarray.addr[2] is a pointer of an object on node 2.

  char *real_addr; // Pointer to local node.
                   // Note that xmp_coarray.addr[my_rank] may not be a pointer of an object.

  size_t elmt_size; // Element size of a coarray. A unit of it is Byte.
                    // e.g.) "int a[10]:[*]" is 4.

  int coarray_dims; // Number of dimensions of coarray.
                    // e.g.) "int a[10][20]:[4][2][*]" is 2.

  int *coarray_elmts; // Number of elements of each dimension of a coarray.
                      // e.g.) If "int a[10][20]:[*]", coarray_elmts[0] is 10, coarray_elmts[1] is 20.
                      //       If a coarray is scalar, coarray_elmts[0] is 1.

  int *distance_of_coarray_elmts; // Distance between each dimension of coarray. A unit of the distance is Byte.
                                  // e.g.) If "int a[10][20][30]:[*]", distance_of_coarray_elmts[0] is 2400 (20*30*sizeof(int)),
                                  //       distance_of_coarray_elmts[1] is 120 (30*sizeof(int)),
                                  //       distance_of_coarray_elmts[0] is 4 (sizeof(int)).

  int image_dims; // Number of dimensions of image set.
                  // e.g.) If "int a[10][20]:[4][2][*]" is 3.

  int *distance_of_image_elmts; // Distance between each dimension of image set.
                                // e.g.) If "int a[10][20]:[4][2][*]", distance_of_image_elmts[0] is 1,
                                //       distance_of_image_elmts[1] is 4, distance_of_image_elmts[2] is 8.
}_XMP_coarray_t;

typedef struct _XMP_array_section{
  long long start;
  long long length;
  long long stride;
  long long elmts;    // Number of elements in each dimension
  long long distance; // Distance between each dimension of an array.
                      // e.g.) If "int a[10][20][30]", _XMP_array_section_t[0].distance is 20*30*sizeof(int),
                      //       _XMP_array_section_t[1].distance is 30*sizeof(int), 
                      //       _XMP_array_section_t[0].distance is sizeof(int),
} _XMP_array_section_t;

typedef struct _XMP_gmv_desc_type
{
  _Bool is_global;
  int ndims;

  _XMP_array_t *a_desc;

  void *local_data;
  int *a_lb;
  int *a_ub;

  int *kind;
  int *lb;
  int *ub;
  int *st;

} _XMP_gmv_desc_t;

//
// for asynchronous comms.
//

typedef struct _XMP_async_comm {
  int async_id;
  int nreqs;
  MPI_Request *reqs;
  struct _XMP_async_comm *next;
} _XMP_async_comm_t;

#define _XMP_ASYNC_COMM_SIZE 511

#define _XMP_MAX_ASYNC_REQS (4 * _XMP_N_MAX_DIM * 10)



typedef struct _XMP_gpu_array_type {
  int gtol;
  unsigned long long acc;
} _XMP_gpu_array_t;

typedef struct _XMP_gpu_data_type {
  _Bool is_aligned_array;
  void *host_addr;
  void *device_addr;
  _XMP_array_t *host_array_desc;
  _XMP_gpu_array_t *device_array_desc;
  size_t size;
} _XMP_gpu_data_t;

#endif // _XMP_DATA_STRUCT
