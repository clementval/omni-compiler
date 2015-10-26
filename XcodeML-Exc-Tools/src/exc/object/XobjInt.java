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

public class XobjInt extends XobjConst
{
    int value;

    public XobjInt(Xcode code, Xtype type, int value, String fkind)
    {
        super(code, type, fkind);
        this.value = value;
    }

    public XobjInt(Xcode code, int value)
    {
        this(code, Xtype.intType, value, null);
    }

    @Override
    public int getInt()
    {
        return value;
    }

    @Override
    public Xobject copy()
    {
        return copyTo(new XobjInt(code, type, value, getFkind()));
    }

    @Override
    public boolean equals(Xobject x)
    {
        return super.equals(x) && value == x.getInt();
    }

    @Override
    public String getName()
    {
        if(code == Xcode.REG)
            return "r_" + Long.toHexString(value);
        else
            return Long.toString(value);
    }
    
    @Override
    public String toString()
    {
        return "(" + OpcodeName() + " 0x" + Long.toHexString(value) + ")";
    }

    @Override
    public boolean isZeroConstant() {
      if (value == 0) {
        return true;
      } else {
        return false;
      }
    }

    @Override
    public boolean isOneConstant() {
      if (value == 1) {
        return true;
      } else {
        return false;
      }
    }
}
