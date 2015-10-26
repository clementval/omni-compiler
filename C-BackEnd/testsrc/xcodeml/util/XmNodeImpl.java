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
package xcodeml.util;

import java.util.Iterator;
import java.util.ArrayList;

import xcodeml.XmNode;

public class XmNodeImpl implements XmNode
{
    private String name;
    private ArrayList<XmNodeImpl> children;
    private XmNodeImpl parent;

    public XmNodeImpl(String name)
    {
        this.name = name;
        children = new ArrayList<XmNodeImpl>();
        parent = null;
    }

    public String getName()
    {
        return name;
    }

    public void addChild(XmNode n)
    {
        n.setParent(this);
        children.add((XmNodeImpl)n);
    }

    @Override
    public XmNode[] getChildren()
    {
        XmNode[] a = new XmNode[children.size()];
        return (XmNode[])children.toArray(a);
    }

    @Override
    public XmNode getParent()
    {
        return parent;
    }

    @Override
    public void setParent(XmNode n)
    {
        this.parent = (XmNodeImpl)n;
    }

    @Override
    public Iterator<XmNode> iterator()
    {
        return new XmNodePreOrderIterator(this);
    }

}
