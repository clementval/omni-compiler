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
import xcodeml.c.type.XcIdent;
import xcodeml.c.util.XmcWriter;

/**
 * Internal object represents following elements:
 *   Var, Param
 */
public final class XcVarObj extends XcObj implements XcExprObj
{
    private XcIdent _ident;
    
    /**
     * Creates a XcVarObj.
     */
    public XcVarObj()
    {
    }
    
    /**
     * Creates a XcVarObj.
     * 
     * @param a identifier of variable referred by the operator object.
     */
    public XcVarObj(XcIdent ident)
    {
        _ident = ident;
    }
    
    /**
     * Sets a identifier of variable referred by the operator object.
     * 
     * @param ident a identifier of variable.
     */
    public final void setIdent(XcIdent ident)
    {
        _ident = ident;
    }
    
    /**
     * Gets a identifier of variable referred by the operator object.
     * 
     * @return a identifier of variable referred by the operator object.
     */
    public final XcIdent getIdent()
    {
        return _ident;
    }

    @Override
    public void addChild(XcNode child)
    {
        if(child instanceof XcIdent)
            _ident = (XcIdent)child;
        else
            throw new IllegalArgumentException(child.getClass().getName());
    }

    @Override
    public void checkChild()
    {
        if(_ident == null)
            throw new IllegalArgumentException("no identifier");
    }

    @Override
    public XcNode[] getChild()
    {
        return toNodeArray(_ident);
    }

    @Override
    public final void setChild(int index, XcNode child)
    {
        switch(index) {
        case 0:
            _ident = (XcIdent)child;
            break;
        default:
            throw new IllegalArgumentException(index + ":" + child.getClass().getName());
        }
    }
    
    @Override
    public final void appendCode(XmcWriter w) throws XmException
    {
        w.addSpc(_ident);
    }
}
