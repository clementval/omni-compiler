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

#ifndef _XMP_TLOG_H_
#define _XMP_TLOG_H_

#include "tlog_mpi.h"

#define _XMP_M_TLOG_TASK_IN(dummy)      tlog_log(TLOG_EVENT_1_IN)
#define _XMP_M_TLOG_TASK_OUT(dummy)     tlog_log(TLOG_EVENT_1_OUT)

#define _XMP_M_TLOG_LOOP_IN(dummy)      tlog_log(TLOG_EVENT_2_IN)
#define _XMP_M_TLOG_LOOP_OUT(dummy)     tlog_log(TLOG_EVENT_2_OUT)

#define _XMP_M_TLOG_REFLECT_IN(dummy)   tlog_log(TLOG_EVENT_3_IN)
#define _XMP_M_TLOG_REFLECT_OUT(dummy)  tlog_log(TLOG_EVENT_3_OUT)

#define _XMP_M_TLOG_BARRIER_IN(dummy)   tlog_log(TLOG_EVENT_4_IN)
#define _XMP_M_TLOG_BARRIER_OUT(dummy)  tlog_log(TLOG_EVENT_4_OUT)

#define _XMP_M_TLOG_REDUCTION_IN(dummy)         tlog_log(TLOG_EVENT_5_IN)
#define _XMP_M_TLOG_REDUCTION_OUT(dummy)        tlog_log(TLOG_EVENT_5_OUT)

#define _XMP_M_TLOG_BCAST_IN(dummy)     tlog_log(TLOG_EVENT_6_IN)
#define _XMP_M_TLOG_BCAST_OUT(dummy)    tlog_log(TLOG_EVENT_6_OUT)

#define _XMP_M_TLOG_GMOVE_IN(dummy)     tlog_log(TLOG_EVENT_7_IN)
#define _XMP_M_TLOG_GMOVE_OUT(dummy)    tlog_log(TLOG_EVENT_7_OUT)

extern void _XMP_tlog_init(void);
extern void _XMP_tlog_finalize(void);

#endif /* _XMP_TLOG_H_ */
