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

import org.w3c.dom.*;
import java.util.ArrayList;
import java.util.HashSet;

public class XmDomUtil {
    public static Node getElement(Node n, String name) {
        if (n == null)
            return null;

        NodeList list = n.getChildNodes();
        for (int i = 0; i < list.getLength(); i++) {
            Node thisNode = list.item(i);
            if (thisNode.getNodeType() != Node.ELEMENT_NODE)
                continue;
            if (thisNode.getNodeName() == name)
                return thisNode;
        }
        return null;
    }

    public static Node getContent(Node n) {
        if (n == null)
            return null;

        NodeList list = n.getChildNodes();
        for (int i = 0; i < list.getLength(); i++) {
            Node thisNode = list.item(i);
            if (thisNode.getNodeType() != Node.ELEMENT_NODE)
                continue;
            return thisNode;
        }
        return null;
    }

    public static String getContentText(Node n) {
        if (n == null)
            return null;
        if (n.getFirstChild() == null) {
            return "";
        }

        return n.getFirstChild().getNodeValue();
    }

    public static String getAttr(Node n, String name) {
        if (n == null)
            return null;

        Node nn = n.getAttributes().getNamedItem(name);
        if (nn != null)
            return nn.getNodeValue();
        return null;
    }

    public static boolean getAttrBool(Node n, String name) {
        if (n == null)
            return false;

        Node nn = n.getAttributes().getNamedItem(name);
        if (nn != null)
            return true;
        return false;
    }

    public static Node[] collectElementsAsArray(Node n, String name) {
        if (n == null) {
            return new Node[0];
        }

        return collectElements(n, name).toArray(new Node[0]);
    }

    public static ArrayList<Node> collectElements(Node n, String ... names) {
        if (n == null) {
            return null;
        }

        NodeList list = n.getChildNodes();
        ArrayList<Node> nodes = new ArrayList<Node>();
        for (int i = 0; i < list.getLength(); i++) {
            Node childNode = list.item(i);
            if (childNode.getNodeType() != Node.ELEMENT_NODE)
                continue;
            for (String name : names) {
                if (childNode.getNodeName().equals(name)) {
                    nodes.add(childNode);
                }
            }
        }
        return nodes;
    }

    public static ArrayList<Node> collectElementsExclude(Node n,
                                                         String ... names) {
        if (n == null) {
            return null;
        }

        HashSet<String> excludes = new HashSet<String>();
        for (String name : names) {
            excludes.add(name);
        }

        NodeList list = n.getChildNodes();
        ArrayList<Node> nodes = new ArrayList<Node>();
        for (int i = 0; i < list.getLength(); i++) {
            Node childNode = list.item(i);
            if (childNode.getNodeType() != Node.ELEMENT_NODE)
                continue;
            if (!excludes.contains(childNode.getNodeName())) {
                nodes.add(childNode);
            }
        }
        return nodes;
    }

    public static ArrayList<Node> collectChildNodes(Node n) {
        if (n == null) {
            return null;
        }

        NodeList list = n.getChildNodes();
        ArrayList<Node> nodes = new ArrayList<Node>();
        for (int i = 0; i < list.getLength(); i++) {
            Node childNode = list.item(i);
            if (childNode.getNodeType() != Node.ELEMENT_NODE)
                continue;
            nodes.add(childNode);
        }
        return nodes;
    }
}
