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

/**
 * represents Fortran Logical Constant.
 */
public class XobjBool extends XobjConst
{
    private boolean value;
    
    public XobjBool(Xcode code, Xtype type, boolean value, String fkind)
    {
        super(code, type, fkind);
        this.value = value;
    }
    
    public XobjBool(boolean value)
    {
        this(Xcode.F_LOGICAL_CONSTATNT, null, value, null);
    }
    
    public boolean getBoolValue()
    {
        return value;
    }

    @Override
    public Xobject copy()
    {
        return copyTo(new XobjBool(code, type, value, getFkind()));
    }

    @Override
    public String toString()
    {
        return "(" + OpcodeName() + " " + value + ")";
    }
}
