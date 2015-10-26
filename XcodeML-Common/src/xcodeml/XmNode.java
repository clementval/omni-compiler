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
package xcodeml;

/**
 * The tree interface for XcodeML binding object.
 * Implementing this interface allows an object the tree operation.
 */
public interface XmNode extends Iterable<XmNode>
{
    /**
     * Gets children of the node.
     *
     * @return children of the node.
     */
    public XmNode[] getChildren();

    /**
     * Sets parent of the node.
     *
     * @param n parent of the node.
     */
    public void setParent(XmNode n);


    /**
     * Gets parent of the node.
     *
     * @return parent of the node.
     */
    public XmNode getParent();
}
