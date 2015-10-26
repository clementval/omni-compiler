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
 * base types
 */
public abstract class XcBaseType extends XcType
{
    private XcBaseTypeEnum _baseTypeEnum;
    
    public XcBaseType()
    {
    }
    
    public XcBaseType(XcBaseTypeEnum baseTypeEnum, String typeId)
    {
        super(XcTypeEnum.BASETYPE, typeId);
        _baseTypeEnum = baseTypeEnum;
    }
    
    public XcBaseTypeEnum getBaseTypeEnum()
    {
        return _baseTypeEnum;
    }

    @Override
    public final void addChild(XcNode child)
    {
        throw new IllegalArgumentException(child.getClass().getName());
    }

    @Override
    public final void checkChild()
    {
    }

    @Override
    public final XcNode[] getChild()
    {
        return null;
    }
    
    @Override
    public final void setChild(int index, XcNode child)
    {
        throw new IllegalArgumentException(index + ":" + child.getClass().getName());
    }

    @Override
    protected final void resolveOverride(XcIdentTableStack itStack)
    {
    }

    @Override
    public String toString()
    {
        StringBuilder b = new StringBuilder(128);
        b.append("[");
        commonToString(b);
        b.append(",bt=").append(_baseTypeEnum);
        b.append("]");
        
        return b.toString();
    }
}
