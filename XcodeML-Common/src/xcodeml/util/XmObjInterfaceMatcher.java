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

import xcodeml.XmObj;

/**
 * The matcher execute mathing about object's interfaces.
 */
public class XmObjInterfaceMatcher implements XmObjMatcher
{
    private Class<?> cls;

    /**
     * Creates XmObjInterfaceMatcher.
     *
     * @param name class name to match wich.
     */
    public XmObjInterfaceMatcher(String name)
    {
        try {
            cls = Class.forName(name);
        } catch(Exception e) {
            cls = null;
        }
    }

    /**
     * Creates XmObjClassMatcher
     *
     * @param c class to match wich.
     */
    public XmObjInterfaceMatcher(Class<?> c)
    {
        this.cls = c;
    }

    @Override
    public boolean match(XmObj n)
    {
        if(n == null) {
            return false;
        } else {
            Class<?> c = n.getClass();
            do {
                for(Class<?> i : c.getInterfaces()) {
                    if(i.equals(cls)) {
                        return true;
                    }
                }
                c = c.getSuperclass();
            } while(!c.equals(Object.class));
            return false;
        }
    }

}
