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
package xcodeml.c.binding;

import static org.junit.Assert.*;

import java.io.StringReader;
import java.util.List;

import org.junit.Test;

import xcodeml.c.binding.gen.XbcXcodeProgram;
import xcodeml.c.decompile.XcBindingVisitor;
import xcodeml.c.decompile.XcDecAndDefObj;
import xcodeml.c.decompile.XcDeclObj;
import xcodeml.c.decompile.XcProgramObj;
import xcodeml.c.util.XmcWriter;

public class XbcBindingVisitorTest
{
    private XbcXcodeProgram _createProgram(String xml) throws Exception
    {
        XbcXcodeProgram xprog =new XbcXcodeProgram(new StringReader(xml));
        return xprog;
    }
    
    @Test
    public void test_XbStartXcodeProgram() throws Exception
    {
        String xml =
            "<XcodeProgram>" +
            "  <typeTable>" +
            "  </typeTable>" +
            "  <globalSymbols>" +
            "    <id><name type=\"long_long\">a</name></id>" +
            "    <id><name type=\"double\">b</name></id>" +
            "  </globalSymbols>" +
            "  <globalDeclarations>" +
            "    <varDecl>" +
            "      <name>a</name>" +
            "      <value><intConstant>1</intConstant></value>" +
            "    </varDecl>" +
            "    <varDecl>" +
            "      <name>b</name>" +
            "      <value><floatConstant>0x3FF00000 0x0</floatConstant></value>" +
            "    </varDecl>" +
            "  </globalDeclarations>" +
            "</XcodeProgram>" +
            "";

        XbcXcodeProgram xprog = _createProgram(xml);
        
        XcProgramObj prog = XcBindingVisitor.createXcProgramObj(xprog);
        assertNotNull(prog);
        List<XcDecAndDefObj> declAndDefs = prog.getDeclAndDefList();
        assertEquals(2, declAndDefs.size());
        XcDecAndDefObj declAndDef = declAndDefs.get(0);
        assertTrue(declAndDef instanceof XcDeclObj);

        XmcWriter w = new XmcWriter();
        prog.appendCode(w);
        System.out.println(w.toString());
    }
}
