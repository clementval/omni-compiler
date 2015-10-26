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

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import xcodeml.XmException;
import xcodeml.c.decompile.XcOperandObj;
import xcodeml.c.obj.XcNode;
import xcodeml.c.util.XmcWriter;

/**
 * Internal object represents following elements:
 *   gccAsmStatement
 */
public class XcGccAsmStmtObj extends XcStmtObj {

    private XcConstObj.StringConst _asmCode;

    private List<XcOperandObj> _inputOperands = null;

    private List<XcOperandObj> _outputOperands = null;

    private List<XcConstObj.StringConst> _clobberList = new ArrayList<XcConstObj.StringConst>();

    private boolean _isVolatile;

    private boolean _isInputOperandsEnd = false;

    /**
     * Sets if is an assembly code volatile.
     * 
     * @param enable true  if an assembly code is volatile.
     */
    public void setIsVolatile(boolean enable)
    {
        _isVolatile = enable;
    }

    /**
     * Sets if is an assembly code volatile.
     * 
     * @return true if an assembly code is volatile.
     */
    public boolean getIsVolatile()
    {
        return _isVolatile;
    }

    /**
     * Sets an assembly code.
     * 
     * @param asmCode an assembly code object.
     */
    public void setAsmCode(XcConstObj.StringConst asmCode)
    {
        _asmCode = asmCode;
    }

    /**
     * Gets an assembly code.
     * 
     * @return an assembly code.
     */
    public XcConstObj.StringConst getAsmCode()
    {
        return _asmCode;
    }

    /**
     * Initialize an input operand list.
     */
    public void initInputOperands()
    {
        _inputOperands = new ArrayList<XcOperandObj>();
    }

    /**
     * Initialize an output operand list.
     */
    public void initOutputOperands()
    {
        _outputOperands = new ArrayList<XcOperandObj>();
    }

    /**
     * Sets if is Adding an operand to an input list end to true.
     */
    public void setInputOperandsEnd()
    {
        _isInputOperandsEnd = true;
    }

    @Override
    public void addChild(XcNode child)
    {
        if (child instanceof XcOperandObj) {
            if (_isInputOperandsEnd) {
                _outputOperands.add((XcOperandObj)child);
            } else {
                _inputOperands.add((XcOperandObj)child);
            }
        } else if (child instanceof XcConstObj.StringConst) {
            _clobberList.add((XcConstObj.StringConst)child);
        } else {
        }
    }

    @Override
    public void checkChild()
    {
        if(_asmCode == null) {
        }
    }

    @Override
    public XcNode[] getChild()
    {
        return null;
    }

    @Override
    public void setChild(int index, XcNode child)
    {
    }

    @Override
    public void appendCode(XmcWriter w) throws XmException
    {
        super.appendCode(w);

        w.add("__asm__");

        if(_isVolatile)
            w.addSpc("volatile");

        w.add("(").add(_asmCode);

        if(_inputOperands != null) {
            w.addSpc(":");
            for(Iterator<XcOperandObj> ite = _inputOperands.iterator(); ite.hasNext();) {
                w.addSpc(ite.next());
                if(ite.hasNext())
                    w.addSpc(",");
            }
        }

        if(_outputOperands != null) {
            w.addSpc(":");
            for(Iterator<XcOperandObj> ite = _outputOperands.iterator(); ite.hasNext();) {
                w.addSpc(ite.next());
                if(ite.hasNext())
                    w.addSpc(",");
            }
        }

        if(_clobberList.size() > 0) {
            w.addSpc(":");
            for(Iterator<XcConstObj.StringConst> ite = _clobberList.iterator(); ite.hasNext();) {
                w.addSpc(ite.next());
                if(ite.hasNext())
                    w.addSpc(",");
            }
        }

        w.add(")").eos();
    }
}
