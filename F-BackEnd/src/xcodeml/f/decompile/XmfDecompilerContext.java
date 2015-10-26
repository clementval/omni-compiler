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
package xcodeml.f.decompile;

import xcodeml.f.util.XmfWriter;
import xcodeml.util.XmDecompilerContext;
import xcodeml.util.XmOption;

/**
 * Decompile context.
 */
public class XmfDecompilerContext implements XmDecompilerContext
{
    private int _maxColumnCount = XmfWriter.DEFAULT_MAX_COLUMN_COUNT;
    private String _lastErrorMessage = null;

    private XmfWriter  _writer;
    //private XfTypeManager _typeManager;
    private XfTypeManagerForDom _typeManagerForDom;

    private Exception _lastCause;

    public XmfDecompilerContext()
    {
        //_typeManager = new XfTypeManager();
        _typeManagerForDom = new XfTypeManagerForDom();
    }

    @Override
    public void setProperty(String key, Object value)
    {
        if(key.equals(KEY_MAX_COLUMNS)) {
            setMaxColumnCount(Integer.parseInt(value.toString()));
        }
    }

    /**
     * Judge debug mode.
     * @return true/false.
     */
    public boolean isDebugMode()
    {
        return XmOption.isDebugOutput();
    }
    
    /**
     * Return cause of last error.
     */
    public Exception getLastCause()
    {
        return _lastCause;
    }

    /**
     * Judge output line directive.
     * @return true/false.
     */
    public boolean isOutputLineDirective()
    {
        return !XmOption.isSuppressLineDirective();
    }

    /**
     * Set output line directive flag.
     * @param outputLineDirective Output line directive flag.
     */
    public void setOutputLineDirective(boolean outputLineDirective)
    {
        XmOption.setIsSuppressLineDirective(!outputLineDirective);
    }

    /**
     * Get mumber of max columns.
     * @return Number of max columns.
     */
    public int getMaxColumnCount()
    {
        return _maxColumnCount;
    }

    /**
     * Set mumber of max columns.
     * @param maxColumnCount Number of max columns.
     */
    public void setMaxColumnCount(int maxColumnCount)
    {
        _maxColumnCount = maxColumnCount;
    }

    /**
     * Get writer for Fortran.
     * @return Instance of XmfWriter.
     */
     public XmfWriter getWriter()
    {
        return _writer;
    }

    /**
     * Set writer for Fortran.
     * @param writer XfTypeManager.
     */
    public void setWriter(XmfWriter writer)
    {
        _writer = writer;
    }

    // /**
    //  * Get type manager.
    //  * @return Instance of XfTypeManager.
    //  */
    // public XfTypeManager getTypeManager()
    // {
    //     return _typeManager;
    // }

    /**
     * Get type manager.
     * @return Instance of XfTypeManager.
     */
    public XfTypeManagerForDom getTypeManagerForDom()
    {
        return _typeManagerForDom;
    }

    public boolean hasError()
    {
        if (_lastErrorMessage != null) {
            return true;
        }
        return false;
    }

    public void setLastErrorMessage(String message)
    {
        _lastErrorMessage = message;
        _lastCause = new Exception();
    }

    public String getLastErrorMessage()
    {
        if (hasError() == false) {
            return XfError.SUCCESS.message();
        }
        return _lastErrorMessage;
    }

    public void debugPrint(String message)
    {
        if (isDebugMode() != false) {
            System.out.print("Debug: ");
            System.out.print(message);
        }
    }

    public void debugPrint(String format, Object... args)
    {
        if (isDebugMode() != false) {
            System.out.print("Debug: ");
            System.out.format(format, args);
        }
    }

    public void debugPrintLine(String message)
    {
        if (isDebugMode() != false) {
            System.out.print("Debug: ");
            System.out.println(message);
        }
    }
}
