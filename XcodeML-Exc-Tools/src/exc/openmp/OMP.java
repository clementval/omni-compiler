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
package exc.openmp;

import xcodeml.util.XmLog;
import exc.object.*;

/**
 * for OMP, all static member defined here
 */
public class OMP
{
    final static String prop = "OMPprop";
    public static boolean debugFlag = false;

    final static String thdprv_prop = "ThreadPrivate";

    /*
     * mode control variables in this OMP package
     */
    static boolean leaveThreadPrivateFlag;
    static boolean moveAutoFlag;

    private static boolean errorFlag;
    private static boolean errorFlags;
    
    static public void setMoveAutoFlag(boolean f)
    {
        moveAutoFlag = f;
    }

    static public void leaveThreadPrivate(boolean f)
    {
        leaveThreadPrivateFlag = f;
    }

    public static void setThreadPrivate(Ident id)
    {
        id.setProp(thdprv_prop, thdprv_prop);
    }

    public static boolean isThreadPrivate(Ident id)
    {
        if(id == null)
            return false;
        return (id.getProp(thdprv_prop) != null);
    }
    
    static boolean hasError()
    {
        return errorFlag;
    }
    
    public static boolean hasErrors()
    {
        return errorFlags;
    }
    
    public static void resetError()
    {
        errorFlag = false;
    }

    public static void error(LineNo l, String msg)
    {
        errorFlag = true;
        errorFlags = true;
        XmLog.error(l, "[OpenMP] " + msg);
    }

    public static void warning(LineNo l, String msg)
    {
        XmLog.warning("[OpenMP] " + msg);
    }

    public static void fatal(String msg)
    {
        XmLog.fatal("[OpenMP] " + msg);
    }
    
    public static void debug(String msg)
    {
        if(debugFlag)
            XmLog.debugAlways(msg);
    }
}
