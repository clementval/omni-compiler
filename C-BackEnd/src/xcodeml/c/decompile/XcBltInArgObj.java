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
 * Internal object represents built_in operator argument {type, memberDesignator, expression}.
 */
public class XcBltInArgObj implements XcAppendable, XcNode
{
    private XcExprObj                _expr;

    private XcType                   _type;

    private XcMemberDesignator _designator;

    /**
     * Creates a XcBltInArgObj and Sets its content to an expression object.
     * 
     * @param expr a content of the object.
     */
    public XcBltInArgObj(XcExprObj expr)
    {
        _expr = expr;
        _type = null;
        _designator = null;
    }

    /**
     * Creates a XcBltInArgObj and Sets its content to a type object.
     * 
     * @param type a content of the object.
     */
    public XcBltInArgObj(XcType type)
    {
        _expr = null;
        _type = type;
        _designator = null;
    }

    /**
     * Creates a XcBltInArgObj and Sets its content to a memberDesignator object.
     * 
     * @param designator a content of the object.
     */
    public XcBltInArgObj(XcMemberDesignator designator)
    {
        _expr = null;
        _type = null;
        _designator = designator;
    }

    @Override
    public final void addChild(XcNode child)
    {
        throw new IllegalArgumentException();
    }

    @Override
    public final void checkChild()
    {
        if((_expr == null && _type == null && _designator == null) ||
           (_expr != null && _type != null) ||
           (_type != null && _designator != null) ||
           (_expr != null &&  _designator != null))
            throw new IllegalArgumentException("content is empty");
    }

    @Override
    public final XcNode[] getChild()
    {
        if(_expr != null)
            return new XcNode[] { _expr };
        else if(_type != null)
            return new XcNode[] { _type };
        else if(_designator != null)
            return new XcNode[] { _designator };
        else
            return null;
    }

    @Override
    public final void setChild(int index, XcNode child)
    {
        if(index != 0)
            throw new IllegalArgumentException(index + ":" + child.getClass().getName());

        if(child instanceof XcExprObj) {
            _expr = (XcExprObj)child;
            return;
        }

        if(child instanceof XcType) {
            _type = (XcType)child;
            return;
        }

        if(child instanceof XcMemberDesignator) {
            _designator = (XcMemberDesignator)child;
            return;
        }

        throw new IllegalArgumentException(index + ":" + child.getClass().getName());
    }

    @Override
    public final void appendCode(XmcWriter w) throws XmException
    {
        w.add(_expr);
        w.add(_type);
        w.add(_designator);
    }
}
