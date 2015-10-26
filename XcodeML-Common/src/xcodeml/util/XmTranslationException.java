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

import org.w3c.dom.Node;

/**
 * Exception about XcodeML translation.
 */
public class XmTranslationException extends RuntimeException {
    private static final long serialVersionUID = 1L;

    /**
     * Creates XmTranslationException.
     *
     * @param node    a XcodeML node object which has fault description.
     * @param case    the cause
     */
    public XmTranslationException(Node node, String msg, Throwable cause) {
        super(String.format("<%s> %s", node.getNodeName(), msg), cause);
    }

    /**
     * Creates XmTranslationException.
     *
     * @param node    a XcodeML node object which has fault description.
     */
    public XmTranslationException(Node node, String msg) {
        super(String.format("<%s> %s", node.getNodeName(), msg));
    }

    /**
     * Creates XmTranslationException.
     *
     * @param node    a XcodeML node object which has fault description.
     * @param case    the cause
     */
    public XmTranslationException(Node node, Throwable cause) {
        super(String.format("<%s>", node.getNodeName()), cause);
    }

    /**
     * Creates XmTranslationException.
     *
     * @param case    the cause
     */
    public XmTranslationException(Throwable cause) {
        super(cause);
    }
}
