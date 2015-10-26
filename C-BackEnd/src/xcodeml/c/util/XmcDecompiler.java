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

import java.io.Reader;
import java.io.Writer;
import java.util.List;
import java.util.ArrayList;
import org.w3c.dom.Document;

import xcodeml.XmException;
// import xcodeml.binding.XmXcodeProgram;
// import xcodeml.c.binding.gen.XbcXcodeProgram;
// import xcodeml.c.binding.gen.XcodeML_CFactory;
// import xcodeml.c.decompile.XcBindingVisitor;
import xcodeml.c.decompile.XcProgramObj;
import xcodeml.util.XmDecompiler;
import xcodeml.util.XmDecompilerContext;
import xcodeml.util.XmLog;

/**
 * XcodeML decompiler for C language.
 */
public class XmcDecompiler implements XmDecompiler
{
    /**
     * Creates XmcDecompiler.
     */
    public XmcDecompiler()
    {
    }

    // @Override
    // public boolean decompile(XmDecompilerContext context, Reader reader, Writer writer) throws XmException
    // {
    //     XbcXcodeProgram xmprog = XcodeML_CFactory.getFactory().createXbcXcodeProgram();
    //     List<String> errorList = new ArrayList<String>();
    //     XmcValidator validator = new XmcValidator();

    //     if(!validator.read(reader, xmprog, errorList)) {
    //         for (String error : errorList) {
    //             XmLog.error(error);
    //         }
    //         return false;
    //     }
        
    //     decompile(context, xmprog, writer);
    //     return true;
    // }

    // @Override
    // public void decompile(XmDecompilerContext context, XmXcodeProgram xmprog, Writer writer) throws XmException
    // {
    //     XcProgramObj prog = XcBindingVisitor.createXcProgramObj((XbcXcodeProgram)xmprog);
    //     XmcWriter xmcWriter = new XmcWriter(writer);
    //     prog.writeTo(xmcWriter);
    //     xmcWriter.flush();
    // }

    @Override
    public void decompile(XmDecompilerContext context, Document xcode, Writer writer) throws XmException {
        XcProgramObj prog = new XmcXcodeToXcTranslator().trans(xcode);
        XmcWriter xmcWriter = new XmcWriter(writer);
        prog.writeTo(xmcWriter);
        xmcWriter.flush();
    }
}
