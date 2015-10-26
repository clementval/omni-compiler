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
import java.util.Stack;

import xcodeml.XmNode;


/**
 * XmNode iterator traverse XmNode tree in pre order.
 */
public class XmNodePreOrderIterator implements Iterator<XmNode>
{
    Stack<XmNode> stack;

    /**
     * Creates an iterator.
     *
     * @param n tree traverse start from this node
     */
    public XmNodePreOrderIterator(XmNode n)
    {
        stack = new Stack<XmNode>();
        if(n != null) {
            stack.push(n);
        }
    }

    @Override
    public boolean hasNext()
    {
        return !stack.empty();
    }

    @Override
    public XmNode next()
    {
        if(stack.empty()) {
            return null;
        } else {
            XmNode n = stack.pop();
            XmNode child[] = n.getChildren();
            for(int i = child.length - 1; i >= 0; --i) {
                stack.push(child[i]);
            }
            return n;
        }
    }

    @Override
    public void remove()
    {
        throw new UnsupportedOperationException();
    }
}
