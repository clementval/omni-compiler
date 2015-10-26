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

#ifndef _XMP_INDEX_MACRO
#define _XMP_INDEX_MACRO

// ------------------------------------------------------------------------------------------------------------------------------
#define _XMP_M_CEILi(a_, b_) (((a_) % (b_)) == 0 ? ((a_) / (b_)) : ((a_) / (b_)) + 1)

// ------------------------------------------------------------------------------------------------------------------------------
#define _XMP_M_LTOG_TEMPLATE_BLOCK(_l, _m, _N, _P, _p) \
(((_p) * _XMP_M_CEILi(_N, _P)) + (_l) + (_m))

#define _XMP_M_LTOG_TEMPLATE_CYCLIC(_l, _m, _P, _p) \
(((_l) * (_P)) + (_p) + (_m))

#define _XMP_M_LTOG_TEMPLATE_BLOCK_CYCLIC(_l, _b, _m, _P, _p) \
((((_l) / (_b)) * (_b) * (_P)) + ((_b) * (_p)) + ((_l) % (_b)) + (_m))

#define _XMP_M_LTOG_TEMPLATE_GBLOCK(_l, _x)	\
((_l) + (_x))

// ------------------------------------------------------------------------------------------------------------------------------
#define _XMP_M_CALC_INDEX_BLOCK(_i, _x) \
((_i) - (_x))

#define _XMP_M_CALC_INDEX_CYCLIC(_i, _p) \
((_i) / (_p))

#define _XMP_M_CALC_INDEX_BLOCK_CYCLIC(_i, _p, _w) \
(((_w) * ((_i) / ((_p) * (_w)))) + ((_i) % (_w)))

#define _XMP_M_CALC_INDEX_GBLOCK(_i, _x) \
((_i) - (_x))
// ------------------------------------------------------------------------------------------------------------------------------
#define _XMP_M_GET_INDEX_1(_i1) \
(_i1)

#define _XMP_M_GET_INDEX_2(_i1, _i2, _acc1) \
((_i1) * (_acc1) + (_i2))

#define _XMP_M_GET_INDEX_3(_i1, _i2, _i3, _acc1, _acc2) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3))

#define _XMP_M_GET_INDEX_4(_i1, _i2, _i3, _i4, _acc1, _acc2, _acc3) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3) * (_acc3) + (_i4))

#define _XMP_M_GET_INDEX_5(_i1, _i2, _i3, _i4, _i5, _acc1, _acc2, _acc3, _acc4) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3) * (_acc3) + (_i4) * (_acc4) + (_i5))

#define _XMP_M_GET_INDEX_6(_i1, _i2, _i3, _i4, _i5, _i6, _acc1, _acc2, _acc3, _acc4, _acc5) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3) * (_acc3) + (_i4) * (_acc4) + (_i5) * (_acc5) + (_i6))

#define _XMP_M_GET_INDEX_7(_i1, _i2, _i3, _i4, _i5, _i6, _i7, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3) * (_acc3) + (_i4) * (_acc4) + (_i5) * (_acc5) + (_i6) * (_acc6) + (_i7))

// ------------------------------------------------------------------------------------------------------------------------------
#define _XMP_M_GET_INDEX_1_N(_i1, _acc1) \
((_i1) * (_acc1))

#define _XMP_M_GET_INDEX_2_N(_i1, _i2, _acc1, _acc2) \
((_i1) * (_acc1) + (_i2) * (_acc2))

#define _XMP_M_GET_INDEX_3_N(_i1, _i2, _i3, _acc1, _acc2, _acc3) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3) * (_acc3))

#define _XMP_M_GET_INDEX_4_N(_i1, _i2, _i3, _i4, _acc1, _acc2, _acc3, _acc4) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3) * (_acc3) + (_i4) * (_acc4))

#define _XMP_M_GET_INDEX_5_N(_i1, _i2, _i3, _i4, _i5, _acc1, _acc2, _acc3, _acc4, _acc5) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3) * (_acc3) + (_i4) * (_acc4) + (_i5) * (_acc5))

#define _XMP_M_GET_INDEX_6_N(_i1, _i2, _i3, _i4, _i5, _i6, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3) * (_acc3) + (_i4) * (_acc4) + (_i5) * (_acc5) + (_i6) * (_acc6))

#define _XMP_M_GET_INDEX_7_N(_i1, _i2, _i3, _i4, _i5, _i6, _i7, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6, _acc7) \
((_i1) * (_acc1) + (_i2) * (_acc2) + (_i3) * (_acc3) + (_i4) * (_acc4) + (_i5) * (_acc5) + (_i6) * (_acc6) + (_i7) * (_acc7))

// ------------------------------------------------------------------------------------------------------------------------------
#define _XMP_M_GET_ELMT_1(_addr, _i1) \
(*((_addr) + _XMP_M_GET_INDEX_1(_i1)))

#define _XMP_M_GET_ELMT_2(_addr, _i1, _i2, _acc1) \
(*((_addr) + _XMP_M_GET_INDEX_2(_i1, _i2, _acc1)))

#define _XMP_M_GET_ELMT_3(_addr, _i1, _i2, _i3, _acc1, _acc2) \
(*((_addr) + _XMP_M_GET_INDEX_3(_i1, _i2, _i3, _acc1, _acc2)))

#define _XMP_M_GET_ELMT_4(_addr, _i1, _i2, _i3, _i4, _acc1, _acc2, _acc3) \
(*((_addr) + _XMP_M_GET_INDEX_4(_i1, _i2, _i3, _i4, _acc1, _acc2, _acc3)))

#define _XMP_M_GET_ELMT_5(_addr, _i1, _i2, _i3, _i4, _i5, _acc1, _acc2, _acc3, _acc4) \
(*((_addr) + _XMP_M_GET_INDEX_5(_i1, _i2, _i3, _i4, _i5, _acc1, _acc2, _acc3, _acc4)))

#define _XMP_M_GET_ELMT_6(_addr, _i1, _i2, _i3, _i4, _i5, _i6, _acc1, _acc2, _acc3, _acc4, _acc5) \
(*((_addr) + _XMP_M_GET_INDEX_6(_i1, _i2, _i3, _i4, _i5, _i6, _acc1, _acc2, _acc3, _acc4, _acc5)))

#define _XMP_M_GET_ELMT_7(_addr, _i1, _i2, _i3, _i4, _i5, _i6, _i7, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6) \
(*((_addr) + _XMP_M_GET_INDEX_7(_i1, _i2, _i3, _i4, _i5, _i6, _i7, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6)))

// ------------------------------------------------------------------------------------------------------------------------------
#define _XMP_M_GET_ADDR_E_1(_addr, _i1) \
((_addr) + _XMP_M_GET_INDEX_1(_i1))

#define _XMP_M_GET_ADDR_E_2(_addr, _i1, _i2, _acc1) \
((_addr) + _XMP_M_GET_INDEX_2(_i1, _i2, _acc1))

#define _XMP_M_GET_ADDR_E_3(_addr, _i1, _i2, _i3, _acc1, _acc2) \
((_addr) + _XMP_M_GET_INDEX_3(_i1, _i2, _i3, _acc1, _acc2))

#define _XMP_M_GET_ADDR_E_4(_addr, _i1, _i2, _i3, _i4, _acc1, _acc2, _acc3) \
((_addr) + _XMP_M_GET_INDEX_4(_i1, _i2, _i3, _i4, _acc1, _acc2, _acc3))

#define _XMP_M_GET_ADDR_E_5(_addr, _i1, _i2, _i3, _i4, _i5, _acc1, _acc2, _acc3, _acc4) \
((_addr) + _XMP_M_GET_INDEX_5(_i1, _i2, _i3, _i4, _i5, _acc1, _acc2, _acc3, _acc4))

#define _XMP_M_GET_ADDR_E_6(_addr, _i1, _i2, _i3, _i4, _i5, _i6, _acc1, _acc2, _acc3, _acc4, _acc5) \
((_addr) + _XMP_M_GET_INDEX_6(_i1, _i2, _i3, _i4, _i5, _i6, _acc1, _acc2, _acc3, _acc4, _acc5))

#define _XMP_M_GET_ADDR_E_7(_addr, _i1, _i2, _i3, _i4, _i5, _i6, _i7, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6) \
((_addr) + _XMP_M_GET_INDEX_7(_i1, _i2, _i3, _i4, _i5, _i6, _i7, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6))

// ------------------------------------------------------------------------------------------------------------------------------
#define _XMP_M_GET_ADDR_0(_addr) \
(_addr)

#define _XMP_M_GET_ADDR_1(_addr, _i1, _acc1) \
((_addr) + _XMP_M_GET_INDEX_1_N(_i1, _acc1))

#define _XMP_M_GET_ADDR_2(_addr, _i1, _i2, _acc1, _acc2) \
((_addr) + _XMP_M_GET_INDEX_2_N(_i1, _i2, _acc1, _acc2))

#define _XMP_M_GET_ADDR_3(_addr, _i1, _i2, _i3, _acc1, _acc2, _acc3) \
((_addr) + _XMP_M_GET_INDEX_3_N(_i1, _i2, _i3, _acc1, _acc2, _acc3))

#define _XMP_M_GET_ADDR_4(_addr, _i1, _i2, _i3, _i4, _acc1, _acc2, _acc3, _acc4) \
((_addr) + _XMP_M_GET_INDEX_4_N(_i1, _i2, _i3, _i4, _acc1, _acc2, _acc3, _acc4))

#define _XMP_M_GET_ADDR_5(_addr, _i1, _i2, _i3, _i4, _i5, _acc1, _acc2, _acc3, _acc4, _acc5) \
((_addr) + _XMP_M_GET_INDEX_5_N(_i1, _i2, _i3, _i4, _i5, _acc1, _acc2, _acc3, _acc4, _acc5))

#define _XMP_M_GET_ADDR_6(_addr, _i1, _i2, _i3, _i4, _i5, _i6, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6) \
((_addr) + _XMP_M_GET_INDEX_6_N(_i1, _i2, _i3, _i4, _i5, _i6, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6))

#define _XMP_M_GET_ADDR_7(_addr, _i1, _i2, _i3, _i4, _i5, _i6, _i7, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6, _acc7) \
((_addr) + _XMP_M_GET_INDEX_7_N(_i1, _i2, _i3, _i4, _i5, _i6, _i7, _acc1, _acc2, _acc3, _acc4, _acc5, _acc6, _acc7))

// ------------------------------------------------------------------------------------------------------------------------------
#define _XMP_M_TEMPLATE_INFO(_desc, _dim) \
(((struct _XMP_template_type *)(_desc))->info[(_dim)])

#define _XMP_M_ARRAY_INFO(_desc, _dim) \
(((struct _XMP_array_type *)(_desc))->info[(_dim)])

#endif // _XMP_INDEX_MACRO
