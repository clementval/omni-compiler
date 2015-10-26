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

import java.util.List;
import java.util.ArrayList;

import xcodeml.c.obj.XcNode;

/**
 * Internal object represents coarray dimension.
 */
public class XcXmpCoArrayDimList implements XcNode
{
    List<XcExprObj> _exprList = new ArrayList<XcExprObj>();

    /**
     * Adds a coarray dimension. 
     * 
     * @param expr a coarray dimension.
     */
    public void add(XcExprObj expr)
    {
        _exprList.add(expr);
    }

    @Override
    public void addChild(XcNode child)
    {
        if(child instanceof XcExprObj)
            _exprList.add((XcExprObj)child);
        else
            throw new IllegalArgumentException(child.getClass().getName());
    }

    @Override
    public void checkChild()
    {
    }

    @Override
    public XcNode[] getChild()
    {
        return _exprList.toArray(new XcNode[_exprList.size()]);
    }

    @Override
    public void setChild(int index, XcNode child)
    {
        if((child instanceof XcExprObj) == false)
            throw new IllegalArgumentException(child.getClass().getName());

        if(index >= 0 && index < _exprList.size())
            _exprList.set(index, (XcExprObj)child);
        else
            throw new IllegalArgumentException(index + ":" + child.getClass().getName());
    }
}
