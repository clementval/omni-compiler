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
#include "exc_platform.h"
#include "tlog.h"

void tlog_parallel_IN(int id);
void tlog_parallel_OUT(int id);
void tlog_barrier_IN(int id);
void tlog_barrier_OUT(int id);
void tlog_loop_init_EVENT(int id);
void tlog_loop_next_EVENT(int id);
void tlog_section_EVENT(int id);
void tlog_single_EVENT(int id);
void tlog_critial_IN(int id);
void tlog_critial_OUT(int id);

void tlog_parallel_IN(int id)
{
    tlog_log(id,TLOG_PARALLEL_IN);
}

void tlog_parallel_OUT(int id)
{
    tlog_log(id,TLOG_PARALLEL_OUT);
}

void tlog_barrier_IN(int id)
{
    tlog_log(id,TLOG_BARRIER_IN);
}

void tlog_barrier_OUT(int id)
{
    tlog_log(id,TLOG_BARRIER_OUT);
}

void tlog_loop_init_EVENT(int id)
{
    tlog_log(id,TLOG_LOOP_INIT_EVENT);
}

void tlog_loop_next_EVENT(int id)
{
    tlog_log(id,TLOG_LOOP_NEXT_EVENT);
}

void tlog_section_EVENT(int id)
{
    tlog_log(id,TLOG_SECTION_EVENT);
}

void tlog_single_EVENT(int id)
{
    tlog_log(id,TLOG_SIGNLE_EVENT);
}

void tlog_critial_IN(int id)
{
    tlog_log(id,TLOG_CRITICAL_IN);
}

void tlog_critial_OUT(int id)
{
    tlog_log(id,TLOG_CRITICAL_OUT);
}

