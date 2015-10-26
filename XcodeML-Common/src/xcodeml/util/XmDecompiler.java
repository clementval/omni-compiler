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

import java.io.Reader;
import java.io.Writer;
import org.w3c.dom.Document;

import xcodeml.XmException;
import xcodeml.binding.XmXcodeProgram;

/**
 * The interface for XcodeML decompiler.
 */
public interface XmDecompiler
{
    // /**
    //  * Decompile XcodeProgram document from specified reader.
    //  * 
    //  * @param context
    //  *      decompiler context (optional).
    //  * @param reader
    //  *      reader of XcodeProgram document.
    //  * @param writer
    //  *      writer of decompiled code.
    //  * @returns
    //  *      false if xml validating failed, otherwise true.
    //  */
    // public boolean decompile(XmDecompilerContext context, Reader reader, Writer writer) throws XmException;

    // /**
    //  * Decompile XcodeProgram document from specified XmXcodeProgram object.
    //  * 
    //  * @param xmprog
    //  *      XcodeProgram document object.
    //  * @param writer
    //  *      writer of decompiled code.
    //  */
    // public void decompile(XmDecompilerContext context, XmXcodeProgram xmprog, Writer writer) throws XmException;

    /**
     * Decompile XcodeProgram document from specified DOM document object.
     * 
     * @param xcode
     *      XcodeML document object.
     * @param writer
     *      writer of decompiled code.
     */
    public void decompile(XmDecompilerContext context, Document xcode, Writer writer) throws XmException;
}
