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
import java.util.Iterator;

import xcodeml.XmException;


/**
 * list of XmType
 */
public class XcTypeList implements Iterable<XcType>
{
    private ArrayList<XcType> _list = new ArrayList<XcType>();
    
    public XcTypeList()
    {
    }

    public boolean add(XcType e)
    {
        return _list.add(e);
    }

    public final void clear()
    {
        _list.clear();
    }

    public final boolean contains(XcType type)
    {
        return _list.contains(type);
    }

    public final XcType get(int index)
    {
        return _list.get(index);
    }

    public final boolean isEmpty()
    {
        return _list.isEmpty();
    }

    @Override
    public final Iterator<XcType> iterator()
    {
        return _list.iterator();
    }

    public final int size()
    {
        return _list.size();
    }

    public final <T> T[] toArray(T[] a)
    {
        return _list.toArray(a);
    }
    
    public final void resolve(XcIdentTableStack itStack) throws XmException
    {
        for(XcType type : _list)
            type.resolve(itStack);
    }
    
    @Override
    public String toString()
    {
        return _list.toString();
    }
}
