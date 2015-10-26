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
 * \file c-xcodeml.h
 * - declare functions for xcodeml output.
 */

#ifndef _C_XCODEML_H_
#define _C_XCODEML_H_

/* prototypes */
void outxTagOnly(FILE *fp, int indent, const char *tag, int xattrFlag);
void outxTag(FILE *fp, int indent, CExpr *expr, const char *tag, int xattrFlag,
                        const char *attrFmt, ...);
void outxTag1(FILE *fp, int indent, CExpr *expr, const char *tag,
                        int xattrFlag);
void outxTagClose(FILE *fp, int indent, const char *tag);
void outxTagCloseNoIndent(FILE *fp, const char *tag);
void outxContext(FILE *fp, int indent, CExpr *expr);
void outxContextWithTag(FILE *fp, int indent, CExpr *expr, const char *tag);
void outxContext(FILE *fp, int indent, CExpr *expr);
void outxChildren(FILE *fp, int indent, CExpr *expr);
void outxChildrenWithTag(FILE *fp, int indent, CExpr *expr, const char *tag);
void outxSymbols(FILE *fp, int indent, CSymbolTable *symTab, int symbolsFlags);
void outxSymbolsAndDecls(FILE *fp, int indent, CExpr *expr, int symbolsFlags);
void outxTypeTable(FILE *fp, int indent);
void outxBody(FILE *fp, int indent, CExpr *stmtsAndDecls);
const char* getScope(CExprOfSymbol *sym);

void outx_CHAR_CONST(FILE *fp, int indent, CExprOfCharConst *expr);
void outx_STRING_CONST(FILE *fp, int indent, CExprOfStringConst *expr);
void outx_NUMBER_CONST(FILE *fp, int indent, CExprOfNumberConst *expr);
void outx_IDENT(FILE *fp, int indent, CExprOfSymbol *expr);
void outx_EXT_DEFS(FILE *fp, int indent, CExpr *expr);
void outx_FUNC_DEF(FILE *fp, int indent, CExpr *expr);
void outx_DIRECTIVE(FILE *fp, int indent, CExprOfDirective *expr);
void outx_INIT_DECL(FILE *fp, int indent, CExpr *expr);
void outx_COMPOUND_LITERAL(FILE *fp, int indent, CExpr *expr);
void outx_ASSIGN(FILE *fp, int indent, CExpr *expr);
void outx_EXPRS(FILE *fp, int indent, CExpr *expr);
void outx_COMP_STMT(FILE *fp, int indent, CExpr *expr);
void outx_IF_STMT(FILE *fp, int indent, CExpr *expr);
void outx_WHILE_STMT(FILE *fp, int indent, CExprOfBinaryNode *expr);
void outx_DO_STMT(FILE *fp, int indent, CExprOfBinaryNode *expr);
void outx_FOR_STMT(FILE *fp, int indent, CExpr *expr);
void outx_SWITCH_STMT(FILE *fp, int indent, CExprOfBinaryNode *expr);
void outx_CASE_LABEL(FILE *fp, int indent, CExprOfBinaryNode *expr);
void outx_FUNCTION_CALL(FILE *fp, int indent, CExprOfBinaryNode *expr);
void outxBuiltinOpCall(FILE *fp, int indent, const char *name, CExpr *typeExpr, CExpr *args);
void outx_TYPE_DESC(FILE *fp, int indent, CExprOfTypeDesc *expr);
void outx_INITIALIZERS(FILE *fp, int indent, CExpr *expr);
void outx_CAST(FILE *fp, int indent, CExprOfBinaryNode *expr);
void outx_POINTS_AT(FILE *fp, int indent, CExprOfBinaryNode *expr);
void outx_ARRAY_REF(FILE *fp, int indent, CExprOfBinaryNode *expr);
void outx_SUBARRAY_REF(FILE*, int, CExprOfBinaryNode*);

void
outxTagForStmt(FILE *fp, int indent, CExpr *expr, const char *tag, 
	       int addXattrFlag,const char *attrFmt, ...);
void outxPrint(FILE *fp, int indent, const char *fmt, ...);

#endif /*  _C_XCODEML_H_ */
