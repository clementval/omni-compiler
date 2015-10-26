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

import xcodeml.XmException;
import xcodeml.c.obj.XcNode;
import xcodeml.c.type.XcIdent;
import xcodeml.c.type.XcType;
import xcodeml.c.util.XmcWriter;

/**
 * Internal object represents subArrayRef.
 */
public class XcXmpSubArrayRefObj extends XcObj implements XcExprObj
{
    private XcExprObj _arrayAddr;
    private List<XcExprObj> _dimList = new ArrayList<XcExprObj>();
    private XcType _type;
    private XcType _elementType;

    @Override
    public void appendCode(XmcWriter w) throws XmException
    {
	w.add(_arrayAddr);
	for (XcExprObj i : _dimList){
	    w.add("[").add(i).add("]");
	}
    }

    @Override
    public void addChild(XcNode child)
    {
        if (child instanceof XcExprObj)
            _dimList.add((XcExprObj)child);
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
        XcNode[] nodes = (_dimList.toArray(new XcNode[_dimList.size() + 1]));

        nodes[_dimList.size()] = _arrayAddr;

        return nodes;
    }

    @Override
    public void setChild(int index, XcNode child)
    {
    }

    /**
     * Sets an arrayAddr of the operator.
     * 
     * @param arrayAddr an arrayAddr of the operator.
     */
    public void setArrayAddr(XcExprObj arrayAddr)
    {
        _arrayAddr = arrayAddr;
    }

    /**
     * Gets an arrayAddr of the operator.
     * 
     * @return an arrayAddr of the operator.
     */
    public XcExprObj getArrayAddr()
    {
        return _arrayAddr;
    }

    /**
     * Sets an array type.
     * 
     * @param type a type of array the operator referred.
      */
    public void setType(XcType type)
    {
        _type = type;
    }

    /**
     * Gets an array type.
     * 
     * @return a type of array the operator referred.
     */
    public XcType getType()
    {
        return _type;
    }

    /**
     * Sets a type of array element.
     * 
     * @param elementType a type of array element.
     */
    public void setElementType(XcType elementType)
    {
        _elementType = elementType;
    }

    /**
     * Gets a type of array element.
     * 
     * @return an type of coarray element.
     */
    public XcType getElementType()
    {
        return _elementType;
    }

    /**
     * Gets array dimensions.
     * 
     * @return array dimensions.
     */
    public List<XcExprObj> getDimList()
    {
        return _dimList;
    }

}