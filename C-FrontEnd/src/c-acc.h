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
#ifndef _C_ACC_H
#define _C_ACC_H

enum ACC_pragma {
    ACC_PARALLEL 	= 200,
    ACC_KERNELS 	= 201,
    ACC_DATA 		= 202,
    ACC_HOST_DATA	= 203,
    ACC_LOOP		= 204,
    ACC_CACHE		= 205,
    ACC_DECLARE		= 206,
    ACC_UPDATE		= 207,
    ACC_WAIT		= 208,

    ACC_PARALLEL_LOOP	= 209,
    ACC_KERNELS_LOOP	= 210,

    ACC_ENTER_DATA  = 211,
    ACC_EXIT_DATA   = 212,

    ACC_DIR_END
};

#define IS_ACC_PRAGMA_CODE(code) (((int)(code)) >= 200 && ((int)(code)) < 300)

enum ACC_pragma_clause {
    ACC_IF,
    ACC_ASYNC,
    ACC_NUM_GANGS,
    ACC_NUM_WORKERS,
    ACC_VECT_LEN,

    ACC_COPY,
    ACC_COPYIN,
    ACC_COPYOUT,
    ACC_CREATE,
    ACC_DELETE,
    ACC_PRESENT,
    ACC_PRESENT_OR_COPY,
    ACC_PRESENT_OR_COPYIN,
    ACC_PRESENT_OR_COPYOUT,
    ACC_PRESENT_OR_CREATE,
    ACC_DEVICEPTR,
    ACC_PRIVATE,
    ACC_FIRSTPRIVATE,
    ACC_LASTPRIVATE,

    ACC_REDUCTION_PLUS,
    ACC_REDUCTION_MINUS,
    ACC_REDUCTION_MUL,
    ACC_REDUCTION_BITAND,
    ACC_REDUCTION_BITOR,
    ACC_REDUCTION_BITXOR,
    ACC_REDUCTION_LOGAND,
    ACC_REDUCTION_LOGOR,
    ACC_REDUCTION_MIN,
    ACC_REDUCTION_MAX,

    ACC_USE_DEVICE,
    ACC_DEV_RESIDENT,

    ACC_COLLAPSE,
    ACC_GANG,
    ACC_WORKER,
    ACC_VECTOR,
    ACC_SEQ,
    ACC_INDEPENDENT,

    ACC_HOST,
    ACC_DEVICE,
};

void out_ACC_PRAGMA(FILE *fp, int indent, int pragma_code, CExpr* expr);
CExpr* lexParsePragmaACC(char *p, int *token);

#endif
