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
 * \file c-pragma.h
 */

#ifndef _C_PRAGMA_H_
#define _C_PRAGMA_H_

#include <strings.h>
#include "c-expr.h"
#include "c-lexyacc.h"

#define MAX_TOKEN_LEN 65536

#define PG_CONST 'N'
#define PG_ERR 'E'
#define PG_IDENT 'I'
#define PG_ANDAND 'A'
#define PG_OROR 'O'
#define PG_EQEQ  'P'
#define PG_NEQ 'Q'
#define PG_LTEQ 'T'
#define PG_GTEQ 'U'
#define PG_LTLT 'V'
#define PG_GTGT 'W'
#define PG_STREF 'S'
#define PG_COL2 'C'

/**
 * \brief
 * pragma kinds
 */
typedef enum {
    PK_NOT_PARSABLE,
    PK_PACK,
    PK_OMP,  // OpenMP
    PK_XMP,  // XcalableMP
    PK_ACC,  // OpenACC
} CPragmaKind;

extern CExpr*  pg_parse_expr();
extern void    pg_get_token();

extern char    *pg_cp;
extern char    pg_tok;
extern char    pg_tok_buf[];
extern CExpr*  pg_tok_val;

#define PG_IS_IDENT(name) (pg_tok == 'I' && strcasecmp(name,pg_tok_buf)==0)

extern CExpr*           lexParsePragma(char *p, int *token);
extern CExpr*           lexAllocDirective(const char *name, CDirectiveTypeEnum type);

extern void lexPragmaInfo(CExpr *,CExpr *);

extern char* lexSkipWordP(char *p);
extern char* lexSkipWord(char *p);
extern char* lexSkipSpaceP(char *p);
extern char* lexSkipSpace(char *p);
extern char* lexSkipSharp(char *p);
extern char* lexConvertUnderscorePragma(char *p);

#endif // _C_PRAGMA_H_

