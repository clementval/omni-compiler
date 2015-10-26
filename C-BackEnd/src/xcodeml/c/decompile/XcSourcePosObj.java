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
package xcodeml.c.decompile;

import xcodeml.XmException;
import xcodeml.c.util.XmcWriter;
import xcodeml.util.XmOption;
import xcodeml.util.XmStringUtil;

/**
 * Internal object represents following elements:
 *   attribute of file, lineno
 */
public final class XcSourcePosObj implements XcAppendable
{
    /* source file path */
    private String _filePath;

    /* line number of original source code.*/
    private int _lineNum;

    /* line number of input file*/
    private int _rawLineNum;

    /**
     * Creates a XcSourcePosObj.
     * 
     * @param filePath the file path of the source code.
     * @param lineNum the line number in the source code.
     * @param rawLineNum the raw line number in the source code.
     */
    public XcSourcePosObj(String filePath,
                          int lineNum,
                          int rawLineNum)
    {
        _filePath = XmStringUtil.trim(filePath);
        _lineNum = lineNum;
        _rawLineNum = rawLineNum;
    }

    /**
     * Creates a XcSourcePosObj.
     * 
     * @param filePath the file path of the source code.
     * @param lineNumStr the line number in the source code.
     * @param rawLineNumStr the raw line number in the source code.
     */
    public XcSourcePosObj(String filePath,
                          String lineNumStr,
                          String rawLineNumStr)
    {
        _filePath = XmStringUtil.trim(filePath);

        if(lineNumStr != null) {
            try {
                _lineNum = Integer.parseInt(lineNumStr);
            } catch(NumberFormatException e) {
                throw new IllegalArgumentException("invalid line number");
            }
        }

        if(rawLineNumStr != null) {
            try {
                _rawLineNum = Integer.parseInt(rawLineNumStr);
            } catch(NumberFormatException e) {
                throw new IllegalArgumentException("invalid raw line number");
            }
        }
    }

    /**
     * Gets the file path of the source code.
     * 
     * @return the file path of the source code.
     */
    public final String getFilePath()
    {
        return _filePath;
    }

    /**
     * Gets the line number in the source code.
     * 
     * @return the line number in the source code.
     */
    public final int getLineNum()
    {
        return _lineNum;
    }

    @Override
    public void appendCode(XmcWriter w) throws XmException
    {
        if(XmOption.isSuppressLineDirective())
            return;

        if(_lineNum <= 0 || _filePath == null)
            return;

        w.noLfOrLf().add("# ").add(_lineNum);

        if(_filePath != null) {
            w.add(" \"").add(_filePath);

            if(w.getIsDebugMode() &&
               _rawLineNum > 0)
                w.addSpc("(raw line = ").addSpc(_rawLineNum).add(")");

            w.add("\"");
        }

        w.lf();
    }
}
