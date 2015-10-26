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
#ifndef _C_OMP_H
#define _C_OMP_H

enum OMP_pragma {
    OMP_PARALLEL = 0, 		/* parallel <clause_list> */
    OMP_FOR = 1,		/* loop <clause_list> */
    OMP_SECTIONS = 2,		/* sections <clause_list> */
    OMP_SECTION = 3,		/* section */
    OMP_SINGLE = 4,		/* single <clause list> */
    OMP_MASTER = 5,		/* master */
    OMP_CRITICAL = 6,		/* critical <name> */
    OMP_BARRIER = 7,		/* barrier */
    OMP_ATOMIC = 8,		/* atomic */
    OMP_FLUSH = 9,		/* flush <namelist> */
    OMP_ORDERED = 10,		/* ordered */
    OMP_THREADPRIVATE = 11,	/* threadprivate <namelist> */

    OMP_PARALLEL_FOR = 12, 	/* parallel <clause_list> */
    OMP_PARALLEL_SECTIONS = 13, 	/* parallel <clause_list> */

    /*
     * Fortran entry
     */
    OMP_F_PARALLEL = 100,
    OMP_F_END_PARALLEL = 101,
    OMP_F_DO = 102,    
    OMP_F_END_DO = 103,	
    OMP_F_SECTIONS = 104,	
    OMP_F_END_SECTIONS = 105,	
    OMP_F_SECTION = 106,	
    OMP_F_SINGLE = 107,	
    OMP_F_END_SINGLE = 108,	
    OMP_F_MASTER = 110,	
    OMP_F_END_MASTER = 111,	
    OMP_F_CRITICAL = 112,	
    OMP_F_END_CRITICAL = 113,	
    OMP_F_BARRIER = 114,	
    OMP_F_ATOMIC = 115,	
    OMP_F_FLUSH = 116,	
    OMP_F_ORDERED = 117,		
    OMP_F_END_ORDERED = 118,		
    OMP_F_THREADPRIVATE = 119,	

    OMP_F_PARALLEL_DO = 120, 	
    OMP_F_END_PARALLEL_DO = 121, 	
    OMP_F_PARALLEL_SECTIONS = 122, 	
    OMP_F_END_PARALLEL_SECTIONS = 123,

    OMP_F_WORKSHARE = 130,
    OMP_F_END_WORKSHARE = 131,
    OMP_F_PARALLEL_WORKSHARE = 132,
    OMP_F_END_PARALLEL_WORKSHARE = 133,
};

enum OMP_pragma_clause {
    OMP_DATA_DEFAULT = 0,
    OMP_DATA_PRIVATE = 1,	/* private <namelist> */
    OMP_DATA_SHARED = 2,	/* shared <namelist> */
    OMP_DATA_FIRSTPRIVATE=3,
    OMP_DATA_LASTPRIVATE=4,
    OMP_DATA_COPYIN =5,

    OMP_DATA_REDUCTION_PLUS=6,
    OMP_DATA_REDUCTION_MINUS=7,
    OMP_DATA_REDUCTION_MUL=8,
    OMP_DATA_REDUCTION_BITAND=9,
    OMP_DATA_REDUCTION_BITOR=10,
    OMP_DATA_REDUCTION_BITXOR=11,
    OMP_DATA_REDUCTION_LOGAND=12,
    OMP_DATA_REDUCTION_LOGOR=13,
    OMP_DATA_REDUCTION_MIN=14,
    OMP_DATA_REDUCTION_MAX=15,
    OMP_DATA_REDUCTION_EQV=16,
    OMP_DATA_REDUCTION_NEQV=17,

    OMP_DATA_COPYPRIVATE=18,

    OMP_DIR_ORDERED=20,
    OMP_DIR_IF=21,
    OMP_DIR_NOWAIT=22,
    OMP_DIR_SCHEDULE=23
};

#define IS_OMP_DATA_CLAUSE(c) \
(((int)OMP_DATA_PRIVATE) <= ((int)c) && \
 ((int)c) <= ((int)OMP_DATA_REDUCTION_NEQV))

#define IS_OMP_REDUCTION_DATA_CLAUSE(c) \
(((int)OMP_DATA_REDUCTION_PLUS) <= ((int)c) && \
 ((int)c) <= ((int)OMP_DATA_REDUCTION_NEQV))

enum OMP_sched_clause {
    OMP_SCHED_NONE = 0,
    OMP_SCHED_STATIC = 1,
    OMP_SCHED_DYNAMIC = 2,
    OMP_SCHED_GUIDED = 3,
    OMP_SCHED_RUNTIME = 4,
    OMP_SCHED_AFFINITY = 5
};

enum OMP_data_default {
    OMP_DEFAULT_NONE = 1,
    OMP_DEFAULT_SHARED = 0,
    OMP_DEFAULT_PRIVATE = 2
};
#endif
