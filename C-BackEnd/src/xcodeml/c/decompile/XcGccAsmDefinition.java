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
import xcodeml.c.util.XmcWriter;

/**
 * Internal object represents following elements:
 *   gccAsmDefinition
 */
public final class XcGccAsmDefinition extends XcObj implements XcDecAndDefObj
{
    private XcConstObj.StringConst _asmCode;

    private boolean _isGccExtension;

    /**
     * Creates XcGccAsmDefinition.
     */
    public XcGccAsmDefinition()
    {
    }

    /**
     * Sets if is the asm code used with __extension__.
     *  
     * @param isGccExtension true if the asm code is used with __extension__.
     */
    public void setIsGccExtension(boolean isGccExtension)
    {
        _isGccExtension = isGccExtension;
    }

    /**
     * Tests if is the asm code used with __extension__.
     * 
     * @return true if the asm code is used with __extension__.
     */
    public boolean isGccExtension()
    {
        return _isGccExtension;
    }

    @Override
    public void addChild(XcNode child)
    {
        if(child instanceof XcConstObj.StringConst)
            _asmCode = (XcConstObj.StringConst)child;
        else
            throw new IllegalArgumentException(child.getClass().getName());
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
        if(_isGccExtension)
            w.addSpc("__extension__");

        w.addSpc("__asm__(").add(_asmCode).add(")").eos();
    }
}
