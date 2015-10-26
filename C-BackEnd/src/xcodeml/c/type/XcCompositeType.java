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

import xcodeml.XmException;
import xcodeml.c.obj.XcNode;

/**
 * type of 'struct' or 'union'
 */
public abstract class XcCompositeType extends XcType implements XcTaggedType
{
    /* tag name */
    private String _tagName;

    /* member list */
    private XcMemberList _memberList = new XcMemberList(this);

    public XcCompositeType(XcTypeEnum typeEnum, String typeId)
    {
        super(typeEnum, typeId);
    }

    public XcCompositeType(XcTypeEnum typeEnum, String typeId, String tagName)
    {
        super(typeEnum, typeId);
        _tagName = tagName;
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

    public final XcMemberList getMemberList()
    {
        return _memberList;
    }

    public final void addMember(XcIdent member)
    {
        _memberList.add(member);
    }

    public final XcIdent getMember(String symbol)
    {
        if(_memberList == null)
            return null;

        return _memberList.getBySymbol(symbol);
    }

    public final void setMemberList(XcMemberList memberList)
    {
        _memberList = memberList;
    }

    @Override
    public final void addChild(XcNode child)
    {
        if(child instanceof XcIdent) {
            if(_memberList == null)
                _memberList = new XcMemberList(this);
            addMember((XcIdent)child);
        } else
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

        if(_memberList == null || _memberList.isEmpty()) {
            if(_gccAttrs == null)
                return null;
            else
                return toNodeArray(_gccAttrs);
        } else {
            if(_gccAttrs == null) {
                return _memberList.toArray(new XcNode[_memberList.size()]);
            } else {
                XcNode[] nodelist = _memberList.toArray(new XcNode[_memberList.size() + 1]);
                nodelist[_memberList.size()] = _gccAttrs;
                return nodelist;
            }
        }
    }

    @Override
    public final void setChild(int index, XcNode child)
    {
        if(_memberList != null && index < _memberList.size())
            _memberList.set(index, (XcIdent)child);
        else
            throw new IllegalArgumentException(index + ":" + child.getClass().getName());
    }

    @Override
    protected final void resolveOverride(XcIdentTableStack itStack) throws XmException
    {
        if(_memberList != null)
            _memberList.resolve(itStack);
    }
}
