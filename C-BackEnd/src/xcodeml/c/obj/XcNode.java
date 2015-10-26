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
package xcodeml.c.obj;

/**
 * Implements this interface allows an object to operated by XcodeML API.
 */
public interface XcNode
{
    /**
     * Adds child to the node.
     *
     * @param child set to the child of the node.
     */
    public void addChild(XcNode child);

    /**
     * Gets children of the node.
     *
     * @return childen of the node.
     */
    public XcNode[] getChild();

    /**
     * Replaces the child of the node.
     *
     * @param index The index of a child be to be replaced.
     * @param child A node replaced to index'th child.
     */
    public void setChild(int index, XcNode child);

    /**
     * Checks is node valid.
     */
    public void checkChild();
}
