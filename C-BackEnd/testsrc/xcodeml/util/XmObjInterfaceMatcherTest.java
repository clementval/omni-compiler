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

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import xcodeml.c.obj.XmcForStatement;

public class XmObjInterfaceMatcherTest
{
    XmcForStatement forStmt;

    @Before
    public void setUp() throws Exception
    {
        forStmt = new XmcForStatement();
    }

    @Test
    public void testMatch_e1()
    {
        XmObjInterfaceMatcher m = new XmObjInterfaceMatcher((String)null);
        assertFalse(m.match(forStmt));
    }
    
    @Test
    public void testMatch_e2()
    {
        XmObjInterfaceMatcher m = new XmObjInterfaceMatcher("");
        assertFalse(m.match(forStmt));
    }

    @Test
    public void testMatch_e3()
    {
        XmObjInterfaceMatcher m = new XmObjInterfaceMatcher("Hoge");
        assertFalse(m.match(forStmt));
    }
    
    @Test
    public void testMatch_s1()
    {
        XmObjInterfaceMatcher m = 
            new XmObjInterfaceMatcher("xcodeml.util.XmNode");
        assertTrue(m.match(forStmt));
    }
    
    @Test
    public void testMatch_s2()
    {
        XmObjInterfaceMatcher m = 
            new XmObjInterfaceMatcher("xcodeml.c.binding.gen.IXbcStatementsChoice");
        assertTrue(m.match(forStmt));
    }

    @Test
    public void testMatch_s3()
    {
        XmObjInterfaceMatcher m = 
            new XmObjInterfaceMatcher("java.lang.Cloneable");
        assertTrue(m.match(forStmt));
    }
    
    @Test
    public void testMatch_f1()
    {
        XmObjInterfaceMatcher m = 
            new XmObjInterfaceMatcher("xcodeml.util.XmNode");
        assertFalse(m.match(null));
    }

    @Test
    public void testMatch_f2()
    {
        XmObjInterfaceMatcher m = 
            new XmObjInterfaceMatcher("java.lang.Runnable");
        assertFalse(m.match(forStmt));
    }
    
    @Test
    public void testMatch_f3()
    {
        XmObjInterfaceMatcher m = 
            new XmObjInterfaceMatcher("xcodeml.c.obj.XmcForStatement");
        assertFalse(m.match(forStmt));
    }

}
