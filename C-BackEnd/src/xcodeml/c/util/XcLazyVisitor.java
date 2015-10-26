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
package xcodeml.c.util;

import xcodeml.c.type.XcLazyEvalType;
import xcodeml.c.type.XcParamList;

/**
 * An interface provides 'lazyEnter.
 */
public interface XcLazyVisitor {
    /**
     * Sets the argument to a parent and enters his children which is <br>
     * XcodeML binding object not yet visited by a XcBindingVisitor.<br>
     * A lazyEnter function is used to lazy evaluate XcodeML binding objects<br>
     * those are not able to be evaluate at some timig but another timing<br>
     * such as the timing after evaluating while variables.
     * 
     * @param lazyType has XcodeML binding objects or DOM nodes these are not visited.
     */
    public void lazyEnter(XcLazyEvalType lazyType);

    public void pushParamListIdentTable(XcParamList paramList);

    public void popIdentTable();
}
