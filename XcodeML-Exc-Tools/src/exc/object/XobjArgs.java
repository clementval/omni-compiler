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
package exc.object;
import exc.block.Block;

/**
 * Iterator for the list of Xobject, which is used to represent the argment
 * list.
 */
public class XobjArgs
{
    Xobject arg;
    XobjArgs next;

    public XobjArgs(Xobject a, XobjArgs next)
    {
        this.arg = a;
        this.next = next;
    }

    public Xobject getArg()
    {
        return arg;
    }

    public void setArg(Xobject x)
    { // rewrite
        arg = x;
    }

    public XobjArgs nextArgs()
    {
        return next;
    }

    public void setNext(XobjArgs n)
    {
        next = n;
    }

    public static XobjArgs cons(Xobject x, XobjArgs a)
    {
        return new XobjArgs(x, a);
    }
    
    public XobjArgs cfold(Block block)
    {
        Xobject arg2 = (arg == null) ? null : arg.cfold(block);
        XobjArgs next2 = (next == null) ? null : next.cfold(block);
        return new XobjArgs(arg2, next2);
    }

    @Override
    public String toString()
    {
        return arg != null ? arg.toString() : "()";
    }
}
