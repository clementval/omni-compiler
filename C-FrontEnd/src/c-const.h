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
 * \file c-const.h
 */

#ifndef _C_CONST_H_
#define _C_CONST_H_

#include "c-expr.h"

extern int              getConstNumValue(CExpr *expr, CNumValueWithType *result);
extern CNumValueKind    getNumValueKind(CBasicTypeEnum bt);
extern long             getCastedLongValue(CNumValueWithType *n);
extern long long        getCastedLongLongValue(CNumValueWithType *n);
extern int              getCastedLongValueOfExpr(CExpr *expr, long *n);
extern int              castNumValue(CNumValueWithType *n, CBasicTypeEnum bt);
extern void             constToNumValueWithType(CExprOfNumberConst *numConst, CNumValueWithType *nvt);
extern int              isConstNumEquals(CExpr *e1, CExpr *e2);
extern int              isConstNumEqualsWithMutable(CExpr *e1, CExpr *e2);
extern long             getNumberConstAsLong(CExpr *expr);
extern int              isConstExpr(CExpr *e, int allowSymbolAddr);
extern int              isConstZero(CExpr *e);

#endif // _C_CONST_H_

