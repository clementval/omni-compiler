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
import xcodeml.c.type.XcType;
import xcodeml.c.util.XmcWriter;

/**
 * Internal object represents built_in operator argument.
 */
public class XcMemberDesignator extends XcObj
{
    private String _member;

    private XcExprObj _expr;

    private XcMemberDesignator _memberDesignator;

    private XcType _type;

    public void setMember(String member)
    {
        _member = member;
    }

    public String getMember()
    {
        return _member;
    }

    public void setType(XcType type)
    {
        _type = type;
    }

    public XcType getType()
    {
        return _type;
    }

    public XcMemberDesignator()
    {
    }

    @Override
    public final void addChild(XcNode child)
    {
        if(child instanceof XcExprObj)
            _expr = (XcExprObj)child;
        else if(child instanceof XcMemberDesignator)
            _memberDesignator = (XcMemberDesignator)child;
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
        return null;
    }

    @Override
    public final void setChild(int index, XcNode child)
    {
    }

    @Override
    public final void appendCode(XmcWriter w) throws XmException
    {
        if(_memberDesignator != null) {
            w.add(_memberDesignator);

        }

        if(_expr != null)
            w.add("[").add(_expr).add("]");

        if(_member != null) {
            if(_memberDesignator != null)
                w.add(".");

            w.add(_member);
        }
    }
}
