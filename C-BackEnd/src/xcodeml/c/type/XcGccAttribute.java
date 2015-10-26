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
package xcodeml.c.type;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

import xcodeml.XmException;
import xcodeml.c.decompile.XcExprObj;
import xcodeml.c.decompile.XcObj;
import xcodeml.c.obj.XcNode;
import xcodeml.c.util.XmcWriter;

/**
 * represent gccAttribute.
 */
public class XcGccAttribute extends XcObj
{
    private String _name;

    private List<XcExprObj> _exprList = new ArrayList<XcExprObj>();

    public XcGccAttribute()
    {
    }

    public XcGccAttribute(String name)
    {
         _name = name;
    }

    @Override
    public void appendCode(XmcWriter w) throws XmException
    {
        w.add(_name);

        if(_exprList.isEmpty() == false) {
            Iterator<XcExprObj> iter = _exprList.iterator();

            w.add("(");
            while(iter.hasNext()) {
                w.add(iter.next());
                if(iter.hasNext())
                    w.add(", ");
            }
            w.add(")");
        }
    }

    @Override
    public void addChild(XcNode child)
    {
        if(child instanceof XcExprObj) {
            _exprList.add((XcExprObj)child);
        } else {
            throw new IllegalArgumentException();
        }
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
    }

    public boolean containsAttrAlias()
    {
        if(_name.startsWith("alias") || _name.startsWith("__alias__"))
            return true;

        return false;
    }

    public void setName(String name)
    {
        _name = name;
    }
}
