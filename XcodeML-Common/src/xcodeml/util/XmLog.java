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

import xcodeml.ILineNo;
import xcodeml.IXobject;
import xcodeml.XmObj;
import xcodeml.binding.IXbLineNo;

public class XmLog
{
    private static void printlnToOut(String s)
    {
        System.out.println(s);
        System.out.flush();
    }
    
    private static void printlnToErr(String s)
    {
        System.err.println(s);
        System.err.flush();
    }
    
    public static void info(String s)
    {
        printlnToOut(s);
    }
    
    public static void warning(String s)
    {
        printlnToErr("warn: " + s);
    }
    
    public static void warning(XmObj xmobj, String s)
    {
        warning(wrapLocation(xmobj, s));
    }
    
    public static void warning(ILineNo lineNo, String s)
    {
        warning(wrapLocation(lineNo, s));
    }
    
    public static void error(String s)
    {
        printlnToErr("error: " + s);
    }
    
    public static void error(ILineNo lineNo, String s)
    {
        error(wrapLocation(lineNo, s));
    }
    
    private static String getExceptionMessage(Exception e)
    {
        if(e.getCause() != null)
            return e.getCause().getMessage();
        return e.getMessage();
    }
    
    public static void error(ILineNo lineNo, Exception e)
    {
        error(wrapLocation(lineNo, getExceptionMessage(e)));
        if(XmOption.isDebugOutput())
            e.printStackTrace();
    }
    
    public static void error(XmObj xmobj, String s)
    {
        error(wrapLocation(xmobj, s));
    }
    
    public static void error(XmObj xmobj, Exception e)
    {
        error(wrapLocation(xmobj, getExceptionMessage(e)));
        if(XmOption.isDebugOutput())
            e.printStackTrace();
    }
    
    public static void fatal(String s)
    {
        System.out.flush();
        System.err.flush();
        printlnToErr("fatal: " + s);
        Thread.dumpStack();
        System.exit(1);
    }
    
    public static void fatal_dump(String s, IXobject x)
    {
        System.out.flush();
        System.err.flush();
        printlnToErr("fatal: " + s);
        printlnToErr("Xcode = " + x.toString());
        Thread.dumpStack();
        System.exit(1);
    }
    
    public static void fatal(Throwable e)
    {
        printlnToErr("fatal:");
        e.printStackTrace();
        Thread.dumpStack();
    }
    
    public static void fatal(XmObj xmobj, String s)
    {
        fatal(wrapLocation(xmobj, s));
    }
    
    public static void fatal(ILineNo lineNo, String s)
    {
        fatal(wrapLocation(lineNo, s));
    }
    
    public static void debug(String s)
    {
        if(XmOption.isDebugOutput())
            printlnToOut(s);
    }
    
    public static void debugAlways(String s)
    {
        printlnToOut(s);
    }
    
    private static String getLeadText(XmObj xmobj)
    {
        if(xmobj == null)
            return "";
        
        StringBuffer buf = new StringBuffer();
        xmobj.makeTextElement(buf);
        String s = buf.toString();
        buf = null;
        final int maxlen = 20;
        int len = (s.length() < maxlen) ? s.length() : maxlen;
        return s.substring(0, len);
    }
    
    private static String wrapLocation(XmObj xmobj, String s)
    {
        if(xmobj instanceof IXbLineNo) {
            IXbLineNo lineno = (IXbLineNo)xmobj;
            return ((lineno.getFile() != null ? lineno.getFile() : "") + ":" +
                lineno.getLineno() + ": " + s);
        } else {
            return (s + "at " + getLeadText(xmobj));
        }
    }

    private static String wrapLocation(ILineNo lineno, String s)
    {
        if(lineno == null)
            return s;
        return ((lineno.fileName() != null) ? lineno.fileName() : "") + ":" +
            lineno.lineNo() + ": " + s;
    }
}
