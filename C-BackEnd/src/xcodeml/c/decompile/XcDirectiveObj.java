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
import xcodeml.c.obj.XcNode;
import xcodeml.c.type.XcIdent;
import xcodeml.c.util.XmcWriter;

/**
 * Internal object represents following elements:
 *   pragma, text
 */
public class XcDirectiveObj extends XcStmtObj implements XcDecAndDefObj
{
    private String _line;

    /**
     * Creates XcDirectiveObj.
     */
    public XcDirectiveObj()
    {
    }

    /**
     * Creates XcDirectiveObj.
     * 
     * @param line a content of the directive.
     */
    public XcDirectiveObj(String line)
    {
        _line = line;
    }

    /**
     * Sets a content of the directive.
     * 
     * @param line a content of the directive.
     */
    public final void setLine(String line)
    {
        _line = line;
    }

    public final void addToken(String line)
    {
	_line += " " + line;
    }

    @Override
    public void addChild(XcNode child)
    {
       if(child instanceof XcExprObj){
           XmcWriter w = new XmcWriter();
           try{
               ((XcExprObj)child).appendCode(w);
               _line += " " + w.toString();
           }catch(XmException xme){
               throw new RuntimeException(xme.getMessage());
           }
	}else {
	    throw new IllegalArgumentException(child.getClass().getName());
	}
    }

    @Override
    public void checkChild()
    {
    }

    @Override
    public XcNode[] getChild()
    {
        return null;
    }

    @Override
    public final void setChild(int index, XcNode child)
    {
        throw new IllegalArgumentException(index + ":" + child.getClass().getName());
    }
    
    @Override
    public void appendCode(XmcWriter w) throws XmException
    {
        super.appendCode(w);
        w.add(_line).lf();
    }
}
