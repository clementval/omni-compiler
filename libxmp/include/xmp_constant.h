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

#ifndef _XMP_CONSTANT
#define _XMP_CONSTANT

#define _XMP_N_INT_TRUE				1
#define _XMP_N_INT_FALSE			0
#define _XMP_N_MAX_DIM				7
#define _XMP_N_MAX_LOC_VAR                      16

// constants for mpi tag
#define _XMP_N_MPI_TAG_GMOVE			10
#define _XMP_N_MPI_TAG_REFLECT_LO		11
#define _XMP_N_MPI_TAG_REFLECT_HI		12

// used by task
#define _XMP_N_NODES_REF			20
#define _XMP_N_TEMPLATE_REF			21

// constants used in runtime functions
#define _XMP_N_INVALID_RANK			-1
#define _XMP_N_UNSPECIFIED_RANK			-2
#define _XMP_N_NO_ALIGN_TEMPLATE		-1
#define _XMP_N_NO_ONTO_NODES			-1
#define _XMP_N_DEFAULT_ROOT_RANK		0

// defined in exc.xcalablemp.XMPtemplate
#define _XMP_N_DIST_DUPLICATION			100
#define _XMP_N_DIST_BLOCK			101
#define _XMP_N_DIST_CYCLIC			102
#define _XMP_N_DIST_BLOCK_CYCLIC		103
#define _XMP_N_DIST_GBLOCK		        104

// FIXME defined in exc.xcalablemp.XMP???
#define _XMP_N_ALIGN_NOT_ALIGNED		200
#define _XMP_N_ALIGN_DUPLICATION		201
#define _XMP_N_ALIGN_BLOCK			202
#define _XMP_N_ALIGN_CYCLIC			203
#define _XMP_N_ALIGN_BLOCK_CYCLIC		204
#define _XMP_N_ALIGN_GBLOCK		        205

// defined in exc.xcalablemp.XMPcollective
#define _XMP_N_REDUCE_SUM			300
#define _XMP_N_REDUCE_PROD			301
#define _XMP_N_REDUCE_BAND			302
#define _XMP_N_REDUCE_LAND			303
#define _XMP_N_REDUCE_BOR			304
#define _XMP_N_REDUCE_LOR			305
#define _XMP_N_REDUCE_BXOR			306
#define _XMP_N_REDUCE_LXOR			307
#define _XMP_N_REDUCE_MAX			308
#define _XMP_N_REDUCE_MIN			309
#define _XMP_N_REDUCE_FIRSTMAX			310
#define _XMP_N_REDUCE_FIRSTMIN			311
#define _XMP_N_REDUCE_LASTMAX			312
#define _XMP_N_REDUCE_LASTMIN			313
#define _XMP_N_REDUCE_EQV                       314
#define _XMP_N_REDUCE_NEQV                      315
#define _XMP_N_REDUCE_MINUS                     316

// defined in exc.xcalablemp.XMPshadow
#define _XMP_N_SHADOW_NONE			400
#define _XMP_N_SHADOW_NORMAL			401
#define _XMP_N_SHADOW_FULL			402

// defined in exc.object.BasicType + 500
#define _XMP_N_TYPE_BOOL			502
#define _XMP_N_TYPE_CHAR			503
#define _XMP_N_TYPE_UNSIGNED_CHAR		504
#define _XMP_N_TYPE_SHORT			505
#define _XMP_N_TYPE_UNSIGNED_SHORT		506
#define _XMP_N_TYPE_INT				507
#define _XMP_N_TYPE_UNSIGNED_INT		508
#define _XMP_N_TYPE_LONG			509
#define _XMP_N_TYPE_UNSIGNED_LONG		510
#define _XMP_N_TYPE_LONGLONG			511
#define _XMP_N_TYPE_UNSIGNED_LONGLONG		512
#define _XMP_N_TYPE_FLOAT			513
#define _XMP_N_TYPE_DOUBLE			514
#define _XMP_N_TYPE_LONG_DOUBLE			515
#define _XMP_N_TYPE_FLOAT_IMAGINARY		516
#define _XMP_N_TYPE_DOUBLE_IMAGINARY		517
#define _XMP_N_TYPE_LONG_DOUBLE_IMAGINARY	518
#define _XMP_N_TYPE_FLOAT_COMPLEX		519
#define _XMP_N_TYPE_DOUBLE_COMPLEX		520
#define _XMP_N_TYPE_LONG_DOUBLE_COMPLEX		521
#define _XMP_N_TYPE_NONBASIC			599

// defined in exc.xcalablemp.XMPgpuData
#define _XMP_N_GPUSYNC_IN			600
#define _XMP_N_GPUSYNC_OUT			601

// defined in exc.xcalablemp.XMP
#define _XMP_N_COARRAY_GET			700
#define _XMP_N_COARRAY_PUT			701

/*
 * defined in F-FrontEnd/src/C-XMP.h
 */
#define _XMP_GLOBAL_IO_DIRECT			800
#define _XMP_GLOBAL_IO_ATOMIC			801
#define _XMP_GLOBAL_IO_COLLECTIVE		802

#endif // _XMP_CONSTANT
