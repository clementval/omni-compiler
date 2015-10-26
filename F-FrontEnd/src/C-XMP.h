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
#ifndef _C_XMP_H
#define _C_XMP_H

enum XMP_pragma {
  XMP_NODES,
  XMP_TEMPLATE,
  XMP_DISTRIBUTE,
  XMP_ALIGN,
  XMP_SHADOW,
  XMP_TASK,
  XMP_TASKS,
  XMP_LOOP,
  XMP_REFLECT,
  XMP_GMOVE,
  XMP_BARRIER,
  XMP_REDUCTION,
  XMP_BCAST,
  XMP_WAIT_ASYNC,
  XMP_COARRAY,
  XMP_TEMPLATE_FIX,
  XMP_ARRAY,
  XMP_LOCAL_ALIAS,

  XMP_END_TASK,
  XMP_END_TASKS,

  XMP_MASTER_IO,
  XMP_MASTER_IO_BEGIN,
  XMP_END_MASTER_IO,

  XMP_GLOBAL_IO,
  XMP_GLOBAL_IO_BEGIN,
  XMP_END_GLOBAL_IO,

  XMP_DIR_END
};

enum XMP_pragma_clause {
  XMP_NODES_INHERIT_GLOBAL = 10,
  XMP_NODES_INHERIT_EXEC = 11,
  XMP_NODES_INHERIT_NODES = 12,

  XMP_MAP_UNDEF = 20,
  XMP_MAP_REGULAR = 21,

  XMP_DIST_BLOCK = 202,
  XMP_DIST_CYCLIC = 203,
  XMP_DIST_GBLOCK = 204,

  XMP_OPT_NOWAIT = 100,
  XMP_OPT_ASYNC = 101,

  XMP_GMOVE_NORMAL  = 400,
  XMP_GMOVE_IN      = 401,
  XMP_GMOVE_OUT     = 402,
  
  XMP_DATA_REDUCE_SUM		= 300,
  XMP_DATA_REDUCE_PROD		= 301,
  XMP_DATA_REDUCE_BAND		= 302,
  XMP_DATA_REDUCE_LAND		= 303,
  XMP_DATA_REDUCE_BOR		= 304,
  XMP_DATA_REDUCE_LOR		= 305,
  XMP_DATA_REDUCE_BXOR		= 306,
  XMP_DATA_REDUCE_LXOR		= 307,
  XMP_DATA_REDUCE_MAX		= 308,
  XMP_DATA_REDUCE_MIN		= 309,
  XMP_DATA_REDUCE_FIRSTMAX	= 310,
  XMP_DATA_REDUCE_FIRSTMIN	= 311,
  XMP_DATA_REDUCE_LASTMAX	= 312,
  XMP_DATA_REDUCE_LASTMIN	= 313,
  XMP_DATA_REDUCE_EQV		= 314,
  XMP_DATA_REDUCE_NEQV		= 315,
  XMP_DATA_REDUCE_SUB		= 316,

  XMP_GLOBAL_IO_DIRECT		= 800,
  XMP_GLOBAL_IO_ATOMIC		= 801,
  XMP_GLOBAL_IO_COLLECTIVE	= 802,
};

#endif

  // defined in xmp_constant.h                                                          
