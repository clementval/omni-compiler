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
import java.util.List;

import xcodeml.XmException;
import xcodeml.c.obj.XcNode;
import xcodeml.c.util.XmcWriter;

/**
 * Internal object represents following elements:
 *   globalDeclarations, declarations
 */
public final class XcDeclsObj extends XcObj implements XcStAndDeclObj, XcDecAndDefObj
{
    private List<XcDecAndDefObj> _declList = new ArrayList<XcDecAndDefObj>();
    
    private XcSourcePosObj _srcPos;
    
    /**
     * Creates XcDeclsObj.
     */
    public XcDeclsObj()
    {
    }
    
    @Override
    public final XcSourcePosObj getSourcePos()
    {
        return _srcPos;
    }

    @Override
    public final void setSourcePos(XcSourcePosObj srcPos)
    {
        _srcPos = srcPos;
    }
    
    /**
     * Gets a list of declaration.
     * 
     * @return a list of declaration.
     */
    public final List<XcDecAndDefObj> getDeclList()
    {
        return _declList;
    }

    /**
     * Adds a declaration to the list.
     * 
     * @param obj a declaration.
     */
    public void add(XcDeclObj obj)
    {
        _declList.add(obj);
    }

    /**
     * Tests is the list empty.
     * 
     * @return true if the list is empty.
     */
    public boolean isEmpty()
    {
        return _declList.isEmpty();
    }
    
    @Override
    public void addChild(XcNode child)
    {
        if(child instanceof XcDeclObj)
            _declList.add((XcDeclObj)child);
        else if(child instanceof XcFuncDefObj)
            _declList.add((XcFuncDefObj)child);
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
        if(_declList.isEmpty())
            return null;
        
        return _declList.toArray(new XcNode[_declList.size()]);
    }
    
    @Override
    public final void setChild(int index, XcNode child)
    {
        if(index < _declList.size())
            _declList.set(index, (XcDecAndDefObj)child);
        else
            throw new IllegalArgumentException(index + ":" + child.getClass().getName());
    }

    @Override
    public void appendCode(XmcWriter w) throws XmException
    {
        if(_declList.isEmpty())
            return;

        if(_srcPos != null)
            _srcPos.appendCode(w);

        for(XcDecAndDefObj decl : _declList)
            w.add(decl);
    }
}
