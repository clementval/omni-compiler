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
 * \file c-main.c
 * C_Front main
 */

#include "c-expr.h"
#include "c-comp.h"
#include "c-lexyacc.h"
#include "c-option.h"
#include "c-ptree.h"

extern unsigned int s_dispParseTree;


/**
 * C_Front main.
 */


/**
 * \brief
 * C_Front main function
 */
int
main(int argc, char** argv)
{
    if(procOptions(argc, argv) == 0)
        return CEXIT_CODE_ERR;

    setTimestamp();
    initStaticData();
    FILE *fpIn, *fpOut;

    if(s_inFile) {
        fpIn = fopen(s_inFile, "r");
        if(fpIn == NULL) {
            perror(CERR_501);
            return CEXIT_CODE_ERR;
        }
    } else {
        fpIn = stdin;
    }

    int convertedFileId = 0;

    CExpr *expr = execParse(fpIn);
    if (s_dispParseTree & 0x1)
        dispParseTree(stderr, expr, "execParse");

    if(s_inFile)
        fclose(fpIn);

    if(s_hasError || expr == NULL)
        goto end;

    reduceExpr(expr);
    //dispParseTree(stderr, expr, "reduceExpr");

    if(s_hasError)
        goto end;

    if(s_verbose)
        printf("compiling ...\n");

    compile(expr);
    if (s_dispParseTree & 0x1)
      dispParseTree(stderr, expr, "compile");

    if(s_hasError)
        goto end;

    convertSyntax(expr);
    //dispParseTree(stderr, expr, "convertSyntax");

    collectTypeDesc(expr);
    if (s_dispParseTree & 0x1)
        dispParseTree(stderr, expr, "collectTypeDesc");

    if(s_hasError)
        goto end;

    if(s_outFile) {
        fpOut = fopen(s_outFile, "w");
        if(fpOut == NULL) {
            perror(CERR_502);
            return CEXIT_CODE_ERR;
        }
    } else {
        fpOut = stdout;
    }

    convertFileIdToNameTab();
    convertedFileId = 1;
    outputXcodeML(fpOut, expr);

    if(s_outFile)
        fclose(fpOut);

  end:

    if(s_hasError || s_hasWarn) {
        CCOL_SL_REVERSE(&s_errorList);
        if(convertedFileId == 0)
            convertFileIdToNameTab();
        printErrors(stderr);
    }

    fflush(stdout);
    fflush(stderr);

    if(s_verbose)
        printf("completed\n");

    return s_hasError ? CEXIT_CODE_ERR : CEXIT_CODE_OK;
}

