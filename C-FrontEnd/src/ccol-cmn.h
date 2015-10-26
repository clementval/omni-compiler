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
/**
 * \file ccol-cmn.h
 */

#ifndef _CCOL_CMN_H_
#define _CCOL_CMN_H_

typedef void* CCOL_Data;

#ifdef CCOL_DEBUG_MEM
#   define ccol_Free(x) { printf("@ccol-free:0x%08x@\n", (unsigned int)(x)); fflush(stdout); free(x); } 
#else
#   define ccol_Free(x) free(x)
#endif

#ifdef MTRACE
#define ccol_MallocNoInit(sz) malloc((sz))
#define ccol_Malloc(sz) memset(malloc((sz)), 0, (sz))
#else
extern void* ccol_MallocNoInit(unsigned int sz);
extern void* ccol_Malloc(unsigned int sz);
#endif
extern void ccol_outOfMemoryHandler(void (*handler)(void));
extern char* ccol_strdup(const char *s, unsigned int maxlen);
extern int ccol_strstarts(const char *s, const char *token);

#endif /* _CCOL_CMN_H_ */
