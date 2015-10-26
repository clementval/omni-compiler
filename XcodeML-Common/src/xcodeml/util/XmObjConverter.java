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
import xcodeml.XmObj;

/**
 * XmObj converter.
 */
public class XmObjConverter
{
    private XmNodeIteratorFactory factory;
    private XmObjMatcher matcher;
    private XmObjMatchAction action;

    /**
     * Traverses XmObj tree and convert a node if the node match the condition.
     *
     * @param n original XmObj tree.
     * @return XmObj tree converted from n.
     */
    public XmObj convert(XmObj n)
    {
        XmNodeIteratorFactory.setFactory(factory);
        XmObj result = n;
        Iterator<XmNode> it = n.iterator();
        while(it.hasNext()) {
            XmNode current = it.next();
            if(matcher.match((XmObj)current)) {
                result = action.execute((XmObj)current);
            }
        }
        return result;
    }

    /**
     * Sets iterator used with XmObj tree traverse.
     *
     * @param factory provides XmNode iterator.
     */
    public void setFactory(XmNodeIteratorFactory factory)
    {
        this.factory = factory;
    }

    /**
     * Sets XmObj matcher which arise convert action.
     *
     * @param matcher provides condition.
     */
    public void setMatcher(XmObjMatcher matcher)
    {
        this.matcher = matcher;
    }

    /**
     * Sets action convert XmObj.
     *
     * @param action provides action.
     */
    public void setAction(XmObjMatchAction action)
    {
        this.action = action;
    }
}
