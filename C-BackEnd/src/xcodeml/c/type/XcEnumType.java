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

import xcodeml.c.obj.XcNode;

/**
 * type of 'enum'
 */
public final class XcEnumType extends XcType implements XcTaggedType
{
    /* tag name */
    private String              _tagName;

    /* enumerators */
    private XcEnumeratorList    _enumeratorList = new XcEnumeratorList(this);

    public XcEnumType(String typeId)
    {
        super(XcTypeEnum.ENUM, typeId);
    }

    @Override
    public String getTagName()
    {
        return _tagName;
    }

    @Override
    public void setTagName(String tagName)
    {
        _tagName = tagName;
    }

    public final void addEnumerator(XcIdent enumerator)
    {
        enumerator.setType(XcBaseTypeEnum.INT.getSingletonConstType());
        _enumeratorList.add(enumerator);
    }

    public final XcEnumeratorList getEnumeratorList()
    {
        return _enumeratorList;
    }

    @Override
    public final String getTypeNameHeader()
    {
        return "enum";
    }

    public final XcIdent getEnumerator(String symbol)
    {
        return _enumeratorList.getBySymbol(symbol);
    }

    @Override
    public final void addChild(XcNode child)
    {
        if(child instanceof XcIdent)
            addEnumerator((XcIdent)child);
        else
            throw new IllegalArgumentException(child.getClass().getName());
    }

    @Override
    public final void checkChild()
    {
    }

    @Override
    public final XcNode[] getChild()
    {
        XcGccAttributeList _gccAttrs = getGccAttribute();

        if(_enumeratorList.isEmpty()) {
            if(_gccAttrs == null)
                return null;
            else
                return toNodeArray(_gccAttrs);
        } else {
            if(_gccAttrs == null) {
                return _enumeratorList.toArray(new XcNode[_enumeratorList.size()]);
            } else {
                XcNode[] nodelist = _enumeratorList.toArray(new XcNode[_enumeratorList.size() + 1]);
                nodelist[_enumeratorList.size()] = _gccAttrs;
                return nodelist;
            }
        }
    }

    @Override
    public final void setChild(int index, XcNode child)
    {
        if(index < _enumeratorList.size())
            _enumeratorList.setChild(index, child);
        else
            throw new IllegalArgumentException(index + ":" + child.getClass().getName());
    }

    @Override
    protected final void resolveOverride(XcIdentTableStack itStack)
    {
    }
}
