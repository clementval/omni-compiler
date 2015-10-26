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
    XMP_NODES 		= 101,
    XMP_TEMPLATE 	= 102,
    XMP_DISTRIBUTE 	= 103,
    XMP_ALIGN 		= 104,
    XMP_SHADOW 		= 105,
    XMP_TASK 		= 106,
    XMP_TASKS 		= 107,
    XMP_LOOP 		= 108,
    XMP_REFLECT 	= 109,
    XMP_GMOVE 		= 110,	
    XMP_BARRIER		= 111,
    XMP_REDUCTION	= 112,
    XMP_BCAST		= 113,
    XMP_COARRAY		= 114,
    XMP_TEMPLATE_FIX	= 115,
    XMP_POST            = 116,
    XMP_WAIT            = 117,
    XMP_WAIT_ASYNC      = 118,
    XMP_ARRAY		= 119,

    XMP_END_TASK	= 120,
    XMP_END_TASKS	= 121,

    XMP_REFLECT_INIT    = 122,
    XMP_REFLECT_DO      = 123,

    XMP_MASTER_IO	= 130,
    XMP_MASTER_IO_BEGIN	= 131,
    XMP_END_MASTER_IO	= 132,
    XMP_GLOBAL_IO	= 134,
    XMP_GLOBAL_IO_BEGIN	= 135,
    XMP_END_GLOBAL_IO	= 136,

    XMP_DIR_END
};

#define IS_XMP_PRAGMA_CODE(code) (((int)(code)) >= 100 && ((int)(code)) < 200)

enum XMP_pragma_clause {
    XMP_NODES_INHERIT_GLOBAL = 10,
    XMP_NODES_INHERIT_EXEC = 11,
    XMP_NODES_INHERIT_NODES = 12,

    XMP_DIST_DUPLICATION = 201,
    XMP_DIST_BLOCK = 202,
    XMP_DIST_CYCLIC = 203,
    XMP_DIST_GBLOCK = 204,
    XMP_DIST_BLOCK_CYCLIC = 205,

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
    XMP_DATA_REDUCE_NEQV	= 315,
    XMP_DATA_REDUCE_MINUS	= 316,

    XMP_GLOBAL_IO_DIRECT		= 800,
    XMP_GLOBAL_IO_ATOMIC		= 801,
    XMP_GLOBAL_IO_COLLECTIVE	= 802,
};

void out_XMP_PRAGMA(FILE *fp, int indent, int pragma_code, CExpr* expr);
CExpr* lexParsePragmaXMP(char *p, int *token);

#endif
