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

#ifndef _XMP_COMM_MACRO
#define _XMP_COMM_MACRO

// reduce
#define _XMP_M_REDUCE_EXEC(addr, count, datatype, op) \
_XMP_reduce_NODES_ENTIRE(_XMP_get_execution_nodes(), addr, count, datatype, op)

#define _XMP_M_REDUCE_FLMM_EXEC(addr, count, datatype, op, num_locs, ...) \
_XMP_reduce_FLMM_NODES_ENTIRE(_XMP_get_execution_nodes(), addr, count, datatype, op, num_locs, __VA_ARGS__)

#define _XMP_M_REDUCE_ACC_EXEC(addr, count, datatype, op) \
_XMP_reduce_acc_NODES_ENTIRE(_XMP_get_execution_nodes(), addr, count, datatype, op)

#define _XMP_M_REDUCE_ACC_FLMM_EXEC(addr, count, datatype, op, num_locs, ...) \
_XMP_reduce_acc_FLMM_NODES_ENTIRE(_XMP_get_execution_nodes(), addr, count, datatype, op, num_locs, __VA_ARGS__)

// bcast
#define _XMP_M_BCAST_EXEC_OMITTED(addr, count, datatype_size) \
_XMP_bcast_NODES_ENTIRE_OMITTED(_XMP_get_execution_nodes(), addr, count, datatype_size)

#define _XMP_M_BCAST_EXEC_GLOBAL(addr, count, datatype_size, from_l, from_u, from_s) \
_XMP_bcast_NODES_ENTIRE_GLOBAL(_XMP_get_execution_nodes(), addr, count, datatype_size, from_l, from_u, from_s)

#define _XMP_M_BCAST_EXEC_NODES(addr, count, datatype_size, from_nodes, ...) \
_XMP_bcast_NODES_ENTIRE_NODES(_XMP_get_execution_nodes(), addr, count, datatype_size, from_nodes, __VA_ARGS__)

#endif // _XMP_COMM_MACRO
