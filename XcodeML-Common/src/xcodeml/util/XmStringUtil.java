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

import xcodeml.XmObj;

/**
 * Utility of String for XcodeML decompiler.
 */
public final class XmStringUtil
{
    public enum Radix
    {
        ALL,
        HEX,
        DEC,
    }
    
    private XmStringUtil()
    {
    }

    /**
     * Wrapper method of String's trim method.
     *
     * @param s string.
     */
    public static final String trim(String s)
    {
        if(s == null)
            return null;
        s = s.trim();
        if(s.length() == 0)
            return null;
        return s;
    }

    /**
     * Gets integer from string represents decimal/hex number.
     *
     * @param xobj object binding to XcodeML element include str.
     * @param str represents decimal/hex number.
     * @return integer repereseted by the string
     */
    public static int getAsCInt(XmObj xobj, String str)
    {
        return (int)getAsCLong(xobj, str, Radix.ALL);
    }

    /**
     * Gets long integer from string represents some radix number.
     *
     * @param xobj object binding to XcodeML element include str.
     * @param str represents decimal/hex number.
     * @return long integer repereseted by the string.
     */
    public static long getAsCLong(XmObj xobj, String str)
    {
        return getAsCLong(xobj, str, Radix.ALL);
    }
    
    /**
     * Gets long integer from string represents some radix number.
     *
     * @param str represents decimal/hex number.
     * @param radix indicates a number base.
     * @return long integer repereseted by the string.
     */
    public static long getAsCLong(String str, Radix radix)
    {
        return (int)getAsCLong(null, str, radix);
    }
    
    /**
     * Gets long integer from string represents some radix number.
     *
     * @param xobj object binding to XcodeML element include str.
     * @param str represents decimal/hex number.
     * @param radix indicates a number base.
     * @return long integer repereseted by the string.
     */
    public static long getAsCLong(XmObj xobj, String str, Radix radix)
    {
        str = trim(str);
        if(str == null)
            throw new XmBindingException(xobj, "not integer value '" + str + "'");

        do {
            if(str.startsWith("0x") && radix == Radix.ALL || radix == Radix.HEX) {
                
                if(str.length() <= 2)
                    break;
                
                try {
                    return Long.parseLong(str.substring(2, str.length()), 16);
                } catch(Exception e) {
                    break;
                }
                
            }
            
            if(radix == Radix.ALL || radix == Radix.DEC) {
                try {
                    return Long.parseLong(str);
                } catch(Exception e) {
                    break;
                }
            }
        } while(false);
        
        switch(radix) {
        case HEX:
            throw new XmBindingException(xobj, "invalid hex integer value '" + str + "'");
        case DEC:
            throw new XmBindingException(xobj, "invalid integer value '" + str + "'");
        default:
            /* not reachable */
            throw new IllegalArgumentException();
        }
    }

    /**
     * Gets boolean from string represents boolean.
     *
     * @param xobj object binding to XcodeML element include str.
     * @param str represents boolean.
     * @return boolean repereseted by str.
     */
    public static boolean getAsBool(XmObj xobj, String str)
    {
        if(str == null)

        str = trim(str);
        if(str == null)
            throw new XmBindingException(xobj, "invalid bool value");
        if(str.equals("1") || str.equals("true"))
            return true;
        if(str.equals("0") || str.equals("false"))
            return false;
        throw new XmBindingException(xobj, "invalid bool value '" + str + "'");
    }
}
