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

import xcodeml.XmNode;

/**
 * The factory interface creates iterator of XmNode.
 */
public abstract class XmNodeIteratorFactory
{
    private static XmNodeIteratorFactory factory = null;

    /**
     * create a XmNode iterator.
     * 
     * @return an iterator
     * @param n node
     */
    public abstract Iterator<XmNode> createXmNodeIterator(XmNode n);

    /**
     * Gets an iterator factory.
     * 
     * @return an iterator factory
     */
    public static XmNodeIteratorFactory getFactory()
    {
        return factory;
    }

    /**
     * Sets an iterator factory.
     * 
     * @param factory a node iterator factory
     */
    public static void setFactory(XmNodeIteratorFactory factory)
    {
        XmNodeIteratorFactory.factory = factory;
    }
}
