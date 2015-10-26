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
#ifndef MPI_PORTABLE_PLATFORM_H
#define MPI_PORTABLE_PLATFORM_H
#endif 

#include "mpi.h"
#include "xmp_internal.h"

int _XMP_world_size;
int _XMP_world_rank;
void *_XMP_world_nodes;

void _XMP_init_world(int *argc, char ***argv) {
  int flag = 0;
  MPI_Initialized(&flag);
  if (!flag) MPI_Init(argc, argv);
  
  MPI_Comm *comm = _XMP_alloc(sizeof(MPI_Comm));
  MPI_Comm_dup(MPI_COMM_WORLD, comm);
  _XMP_nodes_t *n = _XMP_create_nodes_by_comm(_XMP_N_INT_TRUE, comm);
  _XMP_world_size = n->comm_size;
  _XMP_world_rank = n->comm_rank;
  _XMP_world_nodes = n;
  _XMP_push_nodes(n);

  MPI_Barrier(MPI_COMM_WORLD);
}

void _XMP_finalize_world(void) {
  MPI_Barrier(MPI_COMM_WORLD);

  int flag = 0;
  MPI_Finalized(&flag);
  if (!flag) {
    MPI_Finalize();
  }
}

int _XMP_split_world_by_color(int color) {
  int new_comm_rank;
  MPI_Comm new_comm;
  MPI_Comm_split(MPI_COMM_WORLD, color, _XMP_world_rank, &new_comm);
  MPI_Comm_rank(new_comm, &new_comm_rank);
  MPI_Comm_free(&new_comm);

  return new_comm_rank;
}
