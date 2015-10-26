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
import xcodeml.util.XmStringUtil;

/**
 * Internal object represents gccAsmOperand.
 */
public class XcOperandObj extends XcObj {

    private XcExprObj _expression;

    private String _match;

    private String _constraint;

    public void setMatch(String match)
    {
        _match = XmStringUtil.trim(match);
    }

    public String getMatch()
    {
        return _match;
    }

    public void setConstraint(String constraint)
    {
        _constraint = XmStringUtil.trim(constraint);
    }

    public String getConstraint()
    {
        return _constraint;
    }

    @Override
    public void addChild(XcNode child)
    {
        if(child instanceof XcExprObj) {
            _expression = (XcExprObj)child;
        } else
            throw new IllegalArgumentException(child.getClass().getName());
    }

    @Override
    public void checkChild()
    {
        if(_constraint == null || _expression == null)
            throw new IllegalArgumentException();
    }

    @Override
    public XcNode[] getChild()
    {
        return toNodeArray(_expression);
    }

    @Override
    public void setChild(int index, XcNode child)
    {
        if(index != 0)
            throw new IllegalArgumentException(index + ":" + child.getClass().getName());

        if((child instanceof XcExprObj) == false)
            throw new IllegalArgumentException(child.getClass().getName());

        _expression = (XcExprObj)child;
    }

    @Override
    public void appendCode(XmcWriter w) throws XmException
    {
        if (_match != null)
            w.add("[").add(_match).addSpc("]");

        w.add("\"").add(_constraint).add("\"").
            add("(").add(_expression).add(")");
    }
}
