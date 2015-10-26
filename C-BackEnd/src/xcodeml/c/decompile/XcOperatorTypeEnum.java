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

public enum XcOperatorTypeEnum
{
    UNARY_POST  (1),
    UNARY_PRE   (1),
    BINARY      (2),
    ASSIGN      (2),
    LOG         (2),
    COND        (3),
    SIZEOF      (1),
    LABELADDR   (1),
    COMMA       (-1),
    ;

    /* number of XmExprObj as arguments. -1 means any. */
    private int _numOfExprs;
    
    private XcOperatorTypeEnum(int numOfExprs)
    {
        _numOfExprs = numOfExprs;
    }
    
    public final int getNumOfExprs()
    {
        return _numOfExprs;
    }
}
