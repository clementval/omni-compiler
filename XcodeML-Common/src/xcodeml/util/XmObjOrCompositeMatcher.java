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

import java.util.ArrayList;

import xcodeml.XmObj;

/**
 * The matcher execute OR matchings.
 */
public class XmObjOrCompositeMatcher implements XmObjMatcher
{
    private ArrayList<XmObjMatcher> list;

    /**
     * Creates XmObjORCompositeMatcher
     */
    public XmObjOrCompositeMatcher()
    {
        list = new ArrayList<XmObjMatcher>();
    }

    @Override
    public boolean match(XmObj n)
    {
        for(XmObjMatcher m : list) {
            if(m.match(n)) {
                return true;
            }
        }

        return false;
    }

    /**
     * Adds matcher be executed by this matcher.
     *
     * @param matcher provides condition.
     */
    public void addMatcher(XmObjMatcher matcher)
    {
        list.add(matcher);
    }
}
