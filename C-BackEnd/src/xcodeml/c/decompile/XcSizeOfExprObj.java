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

import xcodeml.c.obj.XcNode;
import xcodeml.c.type.XcType;


/**
 * Internal object represents following elements:
 * sizeOfExpr, gccAlignOfExpr
 */
public class XcSizeOfExprObj extends XcOperatorObj
{
    private XcType _typeName;

    /**
     * Gets a term of sizeof/__alignof__ if the term is type.
     * 
     * @return a term of sizeof/__alignof__
     */
    public XcType getTypeName()
    {
        return _typeName;
    }

    /**
     * Sets a single term of sizeof/__alignof__ if the term is type.
     * 
     * @param type a term of sizeof/__alignof__.
     */
    public void setTypeName(XcType type)
    {
        _typeName = type;
    }

    /**
     * Creates a XcSizeOfExprObj.
     * 
     * @param opeEnum an operator code enumerator.
     * @param typeName  a term of sizeof/__alignof__.
     */
    public XcSizeOfExprObj(XcOperatorEnum opeEnum, XcType typeName)
    {
        super(opeEnum);
        _typeName = typeName;
    }

    /**
     * Creates a XcSizeOfExprObj.
     * 
     * @param opeEnum an operator code enumerator.
     * @param expr  a term of sizeof/__alignof__.
     */
    public XcSizeOfExprObj(XcOperatorEnum opeEnum, XcExprObj expr)
    {
        super(opeEnum);
        addChild(expr);
    }

    @Override
    public void checkChild()
    {
        if(super.getExprObjs() == null && _typeName == null)
            throw new IllegalArgumentException("number of expression for the operator is invalid : 0");
    }

    @Override
    public XcNode[] getChild()
    {
        XcExprObj[] exprs = super.getExprObjs();

        if(exprs == null) {
            if(_typeName == null)
                return null;
            else
                return toNodeArray(_typeName);
        } else {
            if(_typeName == null)
                return toNodeArray(exprs[0]);
            else
                return toNodeArray(exprs[0], _typeName);
        }
    }
}
