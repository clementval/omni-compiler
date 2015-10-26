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

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import xcodeml.XmException;
import xcodeml.c.obj.XcNode;
import xcodeml.c.util.XmcWriter;

/**
 * Internal object represents value.
 */
public class XcValueObj extends XcObj implements XcExprObj
{
    private List<XcExprObj> _exprList = new ArrayList<XcExprObj>();

    @Override
    public final void addChild(XcNode child)
    {
        if(child instanceof XcExprObj)
            _exprList.add((XcExprObj)child);
        else
            throw new IllegalArgumentException(child.getClass().getName());
    }

    @Override
    public final void checkChild()
    {
        if(_exprList == null || _exprList.isEmpty())
            throw new IllegalArgumentException("no expression");
    }

    @Override
    public XcNode[] getChild()
    {
        return null;
    }

    @Override
    public final void setChild(int index, XcNode child)
    {
    }

    @Override
    public final void appendCode(XmcWriter w) throws XmException
    {
        if(_exprList.isEmpty()) {
            throw new IllegalArgumentException("no expression");
        } else if (_exprList.size() == 1) {
            w.add(_exprList.get(0));
        } else {
            w.add("{");
            for(Iterator<XcExprObj> iter = _exprList.iterator();iter.hasNext();) {
                if(iter.hasNext())
                    w.add(iter.next()).add(",").lf();
                else
                    w.add(iter.next()).lf();
            }
            w.add("}");
        }
    }
}
