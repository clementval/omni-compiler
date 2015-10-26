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

import xcodeml.util.XmNodeImpl;
import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class XmNodePostOrderIteratorTest
{
    XmNodeImpl tree_one;
    XmNodeImpl tree_five;
    

    @Before
    public void setUp() throws Exception
    {
        tree_one = new XmNodeImpl("a");
        tree_five = new XmNodeImpl("a");
        XmNodeImpl b = new XmNodeImpl("b");
        b.addChild(new XmNodeImpl("c"));
        b.addChild(new XmNodeImpl("d"));
        tree_five.addChild(b);
        tree_five.addChild(new XmNodeImpl("e"));
    }

    @Test
    public void testXmNodePostOrderIterator_null()
    {
        @SuppressWarnings("unused")
        XmNodePostOrderIterator it = new XmNodePostOrderIterator(null);
    }
    
    @Test
    public void testXmNodePostOrderIterator_one()
    {
        @SuppressWarnings("unused")
        XmNodePostOrderIterator it = new XmNodePostOrderIterator(tree_one);
    }    

    @Test
    public void testHasNext_null()
    {
        XmNodePostOrderIterator it = new XmNodePostOrderIterator(null);
        assertFalse(it.hasNext());
    }

    @Test
    public void testHasNext_one()
    {
        XmNodePostOrderIterator it = new XmNodePostOrderIterator(tree_one);
        assertTrue(it.hasNext());
        it.next();
        assertFalse(it.hasNext());
    }
    
    @Test
    public void testHasNext_five()
    {
        XmNodePostOrderIterator it = new XmNodePostOrderIterator(tree_five);
        for (int i = 0; i < 4; ++i) {
            assertTrue(it.hasNext());
            it.next();
        }
        it.next();
        assertFalse(it.hasNext());
    }
    
    @Test
    public void testNext_null()
    {
        XmNodePostOrderIterator it = new XmNodePostOrderIterator(null);
        assertNull(it.next());
    }

    @Test
    public void testNext_one()
    {
        XmNodePostOrderIterator it = new XmNodePostOrderIterator(tree_one);
        XmNodeImpl result = (XmNodeImpl)it.next();
        assertEquals("a", result.getName());
    }

    @Test
    public void testNext_five()
    {
        XmNodePostOrderIterator it = new XmNodePostOrderIterator(tree_five);
        XmNodeImpl result = (XmNodeImpl)it.next();
        assertEquals("c", result.getName());
        result = (XmNodeImpl)it.next();
        assertEquals("d", result.getName());
        result = (XmNodeImpl)it.next();
        assertEquals("b", result.getName());
        result = (XmNodeImpl)it.next();
        assertEquals("e", result.getName());
        result = (XmNodeImpl)it.next();
        assertEquals("a", result.getName());        
    }
    
    @Test
    public void testRemove()
    {
        try {
            XmNodePostOrderIterator it = new XmNodePostOrderIterator(tree_one);
            it.remove();
            fail();
        } catch (UnsupportedOperationException e) {
        }
    }

}
