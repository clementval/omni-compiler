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

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import xcodeml.XmException;
//import xcodeml.c.binding.gen.IRVisitable;
//import xcodeml.c.binding.gen.XbcGccAttributes;
import xcodeml.c.decompile.XcObj;
import xcodeml.c.obj.XcNode;
import xcodeml.c.util.XmcWriter;

/**
 * gcc attribute list.
 */
public class XcGccAttributeList extends XcObj implements XcLazyEvalType
{
    private List<XcGccAttribute> _attrs = new ArrayList<XcGccAttribute>();

    private final String attrDelim = ", ";

    // private IRVisitable[] _bindings;

    private org.w3c.dom.Node[] _bindingNodes;

    private boolean _isLazyEvalType;

    private Set<String>           _dependVariables = new HashSet<String>();

    public XcGccAttributeList()
    {
        _isLazyEvalType = false;
    }

    // public XcGccAttributeList(XbcGccAttributes xbcAttrs)
    // {
    //     _bindings = xbcAttrs.getGccAttribute();
    //     _isLazyEvalType = true;
    // }

    public XcGccAttributeList(org.w3c.dom.Node attrsNode)
    {
        _bindingNodes = xcodeml.util.XmDomUtil.collectElementsAsArray(attrsNode, "gccAttribute");
        _isLazyEvalType = true;
    }

    public void addAttr(XcGccAttribute attr)
    {
        _attrs.add(attr);
    }

    @Override
    public void appendCode(XmcWriter w) throws XmException
    {
        Iterator<XcGccAttribute> iter = _attrs.iterator();

        if((iter.hasNext()) == false)
            return;

        w.addSpc("__attribute__((");

        while (iter.hasNext()) {
            w.add(iter.next());

            if(iter.hasNext())
                w.add(attrDelim);
        }

        w.add("))");
    }

    @Override
    public void addChild(XcNode child)
    {
        if(child instanceof XcGccAttribute) {
            _attrs.add((XcGccAttribute)child);
        } else {
            throw new IllegalArgumentException(child.getClass().getName());
        }
    }

    @Override
    public void checkChild()
    {
    }

    @Override
    public XcNode[] getChild()
    {
        return _attrs.toArray(new XcNode[_attrs.size()]);
    }

    @Override
    public void setChild(int index, XcNode child)
    {
        if((child instanceof XcGccAttribute) == false) 
            throw new IllegalArgumentException(child.getClass().getName());

        if(index >= 0 && index < _attrs.size())
            _attrs.set(index, (XcGccAttribute)child);
        else
            throw new IllegalArgumentException(index + ":" + child.getClass().getName());
    }

    public boolean containsAttrAlias()
    {
        if(_attrs == null)
            return false;

        for(XcGccAttribute attr : _attrs) {
            if(attr.containsAttrAlias())
                return true;
        }

        return false;
    }

    public boolean isEmpty()
    {
        return _attrs.isEmpty();
    }

    @Override
    public Set<String> getDependVar()
    {
        return _dependVariables;
    }

    // @Override
    // public IRVisitable[] getLazyBindings()
    // {
    //     return _bindings;
    // }

    @Override
    public org.w3c.dom.Node[] getLazyBindingNodes() {
        return _bindingNodes;
    }

    @Override
    public boolean isLazyEvalType()
    {
        return _isLazyEvalType;
    }

    @Override
    public void setIsLazyEvalType(boolean enable)
    {
        _isLazyEvalType = enable;
    }

    // @Override
    // public void setLazyBindings(IRVisitable[] bindings)
    // {
    //     _bindings = bindings;
    // }

    @Override
    public void setLazyBindings(org.w3c.dom.Node[] nodes) {
        _bindingNodes = nodes;
    }

    public void addAttr(String name)
    {
        XcGccAttribute attr = new XcGccAttribute(name);
        _attrs.add(attr);
    }
}
