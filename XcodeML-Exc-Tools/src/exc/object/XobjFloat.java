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

import java.math.BigDecimal;

import xcodeml.XmException;

/**
 * Represents float/double/long double constant.
 */
public class XobjFloat extends XobjConst
{
    private BigDecimal value;
    
    private String float_str;
    
    public XobjFloat(Xcode code, Xtype type, String float_str, BigDecimal value, String fkind)
    {
        super(code, type, fkind);
        this.float_str = float_str;
        this.value = value;
    }
    
    public XobjFloat(Xcode code, Xtype type, String float_str, String fkind)
    {
        this(code, type, float_str, null, fkind);
    }

    public XobjFloat(Xcode code, Xtype type, String float_str)
    {
        this(code, type, float_str, null);
    }
    
    public XobjFloat(Xcode code, Xtype type, double d)
    {
        this(code, type, null, new BigDecimal(d), null);
    }
    
    public XobjFloat(double d) throws XmException
    {
        this(Xcode.FLOAT_CONSTANT, Xtype.doubleType, d);
    }
    
    @Override
    public double getFloat()
    {
        return value.doubleValue();
    }
    
    @Override
    public String getFloatString()
    {
        if(float_str == null)
            return value.toEngineeringString();
        return float_str;
    }
    
    @Override
    public Xobject copy()
    {
        return copyTo(new XobjFloat(code, type, float_str, value, getFkind()));
    }

    @Override
    public String toString()
    {
        return "(" + OpcodeName() + " " + getFloatString() + ")";
    }
}
