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

#ifndef _XMP_MATH_FUNCTION
#define _XMP_MATH_FUNCTION

// --- integer functions
// calculate ceil(a/b) for positive integers
#define _XMP_M_CEILi(a_, b_) (((a_) % (b_)) == 0 ? ((a_) / (b_)) : ((a_) / (b_)) + 1)
// calculate floor(a/b) for positive integers
#define _XMP_M_FLOORi(a_, b_) ((a_) / (b_))
#define _XMP_M_COUNTi(a_, b_) ((b_) - (a_) + 1)
#define _XMP_M_COUNT_TRIPLETi(l_, u_, s_) (_XMP_M_FLOORi(((u_) - (l_)), s_) + 1)

// --- generic functions
#define _XMP_M_MAX(a_, b_) ((a_) > (b_) ? (a_) : (b_))
#define _XMP_M_MIN(a_, b_) ((a_) > (b_) ? (b_) : (a_))

// defined in xmp_math_function.c
extern int _XMP_modi_ll_i(long long value, int cycle);
extern int _XMP_modi_i_i(int value, int cycle);
extern int _XMP_ceili(int a, int b);
extern int _XMP_floori(int a, int b);
extern int _XMP_gcd(int a, int b);
extern int _XMP_lcm(int a, int b);

#endif //_XMP_MATH_FUNCTION
