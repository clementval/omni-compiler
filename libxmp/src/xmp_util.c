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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "xmp_internal.h"

static unsigned long long _XMP_on_ref_id_count = 0;

unsigned long long _XMP_get_on_ref_id(void) {
  if (_XMP_on_ref_id_count == ULLONG_MAX) {
    _XMP_fatal("cannot create a new nodes/template: too many");
  }

  return _XMP_on_ref_id_count++;
}

void *_XMP_alloc(size_t size) {
  void *addr;

  addr = malloc(size);
  if (addr == NULL) {
    _XMP_fatal("cannot allocate memory");
  }

  return addr;
}

void _XMP_free(void *p) {
  free(p);
}

void _XMP_fatal(char *msg) {
  fprintf(stderr, "[RANK:%d] XcalableMP runtime error: %s\n", _XMP_world_rank, msg);
  MPI_Abort(MPI_COMM_WORLD, 1);
}

void _XMP_fatal_nomsg(){
  MPI_Abort(MPI_COMM_WORLD, 1);
}

void _XMP_unexpected_error(void) {
  _XMP_fatal("unexpected error in runtime");
}
