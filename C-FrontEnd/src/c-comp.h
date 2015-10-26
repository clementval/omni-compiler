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
 * \file c-comp.h
 */

#ifndef _C_COMP_H
#define _C_COMP_H

#include "c-expr.h"
#include "c-const.h"

extern void reduceExpr(CExpr *expr);
extern void compile(CExpr *expr);
extern void compile1(CExpr *expr, CExpr *parent);
extern void convertSyntax(CExpr *expr);
extern void collectTypeDesc(CExpr *expr);
extern void outputXcodeML(FILE *fp, CExpr *expr);
extern void addTypeDesc(CExprOfTypeDesc *td);

#endif /* _C_COMP_H_ */

