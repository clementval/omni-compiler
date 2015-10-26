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
package xcodeml.f.decompile;

import java.util.Deque;
import java.util.LinkedList;

import org.w3c.dom.Node;

/**
 * Decompile utility, using DOM node.
 */
public class XfUtilForDom {
    public static void errorPrint(String message) {
        System.err.println(message);
    }

    public static String[] getNodePath(Node node) {
        Deque<String> list = new LinkedList<String>();
        list.addFirst(node.getNodeName());
        node = node.getParentNode();
        while (node != null) {
            list.addFirst(node.getNodeName());
            node = node.getParentNode();
        }
        return list.toArray(new String[0]);
    }

    public static String formatError(Node errorNode,
                                     XfError errorCode,
                                     Object... args) {
        StringBuilder sb = new StringBuilder();
        sb.append("Error(");
        sb.append(errorCode.ordinal());
        sb.append("): ");
        sb.append(errorCode.format(args));

        if (errorNode == null) {
            return sb.toString();
        }

        sb.append("\n<Element Tree>\n");

        String[] nodeArray = getNodePath(errorNode);
        if (nodeArray.length > 0) {
            sb.append(nodeArray[0]);
            sb.append("\n");
        }

        for (int i = 1; i < nodeArray.length; i++) {
            for (int j = 0; j < i; j++) {
                sb.append("  ");
            }
            sb.append("+");
            sb.append(nodeArray[i]);
            sb.append("\n");
        }
        return sb.toString();
    }

    public static boolean isNullOrEmpty(String s) {
        return ((s == null) || (s.isEmpty() != false));
    }
}
