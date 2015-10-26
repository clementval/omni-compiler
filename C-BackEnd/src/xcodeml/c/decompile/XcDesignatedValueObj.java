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

import xcodeml.XmException;
import xcodeml.c.obj.XcNode;
import xcodeml.c.util.XmcWriter;

/**
 * Internal object represents designatedValue.
 */
public class XcDesignatedValueObj extends XcObj implements XcExprObj
{
    private String    _member;

    private XcExprObj _expr;

    /**
     * Sets a name of member.
     *  
     * @param member a name of member.
     */
    public void setMember(String member)
    {
        _member = member;
    }

    @Override
    public final void addChild(XcNode child)
    {
        if(child instanceof XcExprObj)
            _expr = (XcExprObj)child;
        else
            throw new IllegalArgumentException(child.getClass().getName());
    }

    @Override
    public final void checkChild()
    {
    }

    @Override
    public XcNode[] getChild()
    {
        return toNodeArray(_expr);
    }

    @Override
    public final void setChild(int index, XcNode child)
    {
    	if(index == 0)
    		_expr = (XcExprObj)child;
    }

    @Override
    public final void appendCode(XmcWriter w) throws XmException
    {
        w.add("{").add(".").add(_member).add(" =").add(_expr).add("}");
    }
}
