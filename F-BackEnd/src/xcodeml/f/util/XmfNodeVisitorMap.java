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
package xcodeml.f.util;

import java.util.HashMap;

/**
 * XcodeML node name to node processing object (visitor) map.
 */
public class XmfNodeVisitorMap<T> {
    public static class Pair<T> {
        public String nodeName;
        public T visitor;
        public Pair(String nodeName, T visitor) {
            this.nodeName = nodeName;
            this.visitor = visitor;
        }
    }

    public XmfNodeVisitorMap(Pair<T>[] pairs) {
        visitorMap = new HashMap<String, T>();
        for (Pair<T> p : pairs) {
            visitorMap.put(p.nodeName, p.visitor);
        }
    }

    public T getVisitor(String nodeName) {
        return visitorMap.get(nodeName);
    }

    private HashMap<String, T> visitorMap;
}
