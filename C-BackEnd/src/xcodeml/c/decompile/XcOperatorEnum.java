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
package xcodeml.c.decompile;

public enum XcOperatorEnum
{
    /**
     *  (prefix unary operators)
     *      unaryMinusExpr, bitNotExpr, logNotExpr
     *      [++, --]
     *  (post unary operators)
     *      postIncrExpr, postDecrExpr
     *  (assign operators)
     *      assignExpr,
     *      asgPlusExpr, asgMinusExpr, asgMulExpr, asgDivExpr, asgModExpr,
     *      asgLshiftExpr, asgRshiftExpr, asgBitAndExpr, asgBitOrExpr, asgBitXorExpr,
     *  (calculation operators)
     *      plusExpr, minusExpr, mulExpr, divExpr, modExpr,
     *      LshiftExpr, RshiftExpr, bitAndExpr, bitOrExpr, bitXorExpr
     *  (comparison operators)
     *      logEQExpr, logNEQExpr, logGEExpr, logGTExpr, logLEExpr, logLTExpr,
     *      logAndExpr, logOrExpr
     *  (ternary operators)
     *      condExpr
     *  (comma operator)
     *      commaExpr
     *  (sizeof, alignof operators)
     *      sizeOfExpr, addrOfExpr, gccAlignOfExpr, xmpDescOf
     *  (label operator)
     *      labelAddr
     */

    UNARY_MINUS     (XcOperatorTypeEnum.UNARY_PRE, "-"),
    BIT_NOT         (XcOperatorTypeEnum.UNARY_PRE, "~"),
    LOG_NOT         (XcOperatorTypeEnum.UNARY_PRE, "!"),
    PRE_INCR        (XcOperatorTypeEnum.UNARY_PRE, "++"),
    PRE_DECR        (XcOperatorTypeEnum.UNARY_PRE, "--"),
    POST_INCR       (XcOperatorTypeEnum.UNARY_POST, "++"),
    POST_DECR       (XcOperatorTypeEnum.UNARY_POST, "--"),
    ASSIGN          (XcOperatorTypeEnum.ASSIGN, "="),
    ASSIGN_PLUS     (XcOperatorTypeEnum.ASSIGN, "+="),
    ASSIGN_MINUS    (XcOperatorTypeEnum.ASSIGN, "-="),
    ASSIGN_MUL      (XcOperatorTypeEnum.ASSIGN, "*="),
    ASSIGN_DIV      (XcOperatorTypeEnum.ASSIGN, "/="),
    ASSIGN_MOD      (XcOperatorTypeEnum.ASSIGN, "%="),
    ASSIGN_LSHIFT   (XcOperatorTypeEnum.ASSIGN, "<<="),
    ASSIGN_RSHIFT   (XcOperatorTypeEnum.ASSIGN, ">>="),
    ASSIGN_BIT_AND  (XcOperatorTypeEnum.ASSIGN, "&="),
    ASSIGN_BIT_OR   (XcOperatorTypeEnum.ASSIGN, "|="),
    ASSIGN_BIT_XOR  (XcOperatorTypeEnum.ASSIGN, "^="),
    PLUS            (XcOperatorTypeEnum.BINARY, "+"),
    MINUS           (XcOperatorTypeEnum.BINARY, "-"),
    MUL             (XcOperatorTypeEnum.BINARY, "*"),
    DIV             (XcOperatorTypeEnum.BINARY, "/"),
    MOD             (XcOperatorTypeEnum.BINARY, "%"),
    LSHIFT          (XcOperatorTypeEnum.BINARY, "<<"),
    RSHIFT          (XcOperatorTypeEnum.BINARY, ">>"),
    BIT_AND         (XcOperatorTypeEnum.BINARY, "&"),
    BIT_OR          (XcOperatorTypeEnum.BINARY, "|"),
    BIT_XOR         (XcOperatorTypeEnum.BINARY, "^"),
    LOG_EQ          (XcOperatorTypeEnum.LOG, "=="),
    LOG_NEQ         (XcOperatorTypeEnum.LOG, "!="),
    LOG_GE          (XcOperatorTypeEnum.LOG, ">="),
    LOG_GT          (XcOperatorTypeEnum.LOG, ">"),
    LOG_LE          (XcOperatorTypeEnum.LOG, "<="),
    LOG_LT          (XcOperatorTypeEnum.LOG, "<"),
    LOG_AND         (XcOperatorTypeEnum.LOG, "&&"),
    LOG_OR          (XcOperatorTypeEnum.LOG, "||"),
    COND            (XcOperatorTypeEnum.COND, "?"),
    COMMA           (XcOperatorTypeEnum.COMMA, ","),
    SIZEOF          (XcOperatorTypeEnum.SIZEOF, "sizeof"),
    ADDROF          (XcOperatorTypeEnum.SIZEOF, "&"),
    ALIGNOF         (XcOperatorTypeEnum.SIZEOF, "__alignof__"),
    XMPDESCOF       (XcOperatorTypeEnum.SIZEOF, "xmp_desc_of"),
    LABELADDR       (XcOperatorTypeEnum.LABELADDR, "&&"),
    ;
    
    private XcOperatorTypeEnum _opeType;
    
    private String _code;
    
    private XcOperatorEnum(XcOperatorTypeEnum opeType, String code)
    {
        _opeType = opeType;
        _code = code;
    }
    
    public final XcOperatorTypeEnum getOperatorType()
    {
        return _opeType;
    }
    
    public final String getCode()
    {
        return _code;
    }
}
