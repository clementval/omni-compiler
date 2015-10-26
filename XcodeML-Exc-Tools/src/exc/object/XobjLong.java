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

import java.math.BigInteger;

public class XobjLong extends XobjConst
{
    long high;
    long low;

    private static final BigInteger _long64mask = new BigInteger("FFFFFFFFFFFFFFFF", 16);
    
    public XobjLong(Xcode code, Xtype type, long high, long low, String fkind)
    {
        super(code, type, fkind);
        init(high, low);
    }
    
    private void init(long high, long low)
    {
        this.high = high;
        this.low = low;
    }
    
    public XobjLong(Xcode code, Xtype type, BigInteger bi, String fkind)
    {
        this(code, type, 0, 0, fkind);
        int sign = bi.signum();
        long high = ((sign < 0) ? bi.negate() : bi).shiftRight(64).longValue();
        long low  = bi.and(_long64mask).longValue();
        init(high * sign, low);
    }

    public XobjLong(Xcode code, Xtype type, long high, long low)
    {
        this(code, type, high, low, null);
    }
    
    public XobjLong(long high, long low)
    {
        this(Xcode.LONGLONG_CONSTANT, Xtype.longlongType, high, low);
    }
    
    @Override
    public long getLongHigh()
    {
        return high;
    }

    @Override
    public long getLongLow()
    {
        return low;
    }
    
    public BigInteger getBigInteger()
    {
        BigInteger l = BigInteger.valueOf(low);
        if(high == 0)
            return l;
        BigInteger i = BigInteger.valueOf(high > 0 ? high : -high)
            .shiftLeft(64).and(l);
        if(high < 0)
            i = i.negate();
        return i;
    }

    @Override
    public Xobject copy()
    {
        return copyTo(new XobjLong(code, type, high, low, getFkind()));
    }

    @Override
    public boolean equals(Xobject x)
    {
        return x.getLongHigh() == high && x.getLongLow() == low;
    }

    @Override
    public String toString()
    {
        return "(" + OpcodeName() + " 0x" + Long.toHexString(high) + " 0x" + Long.toHexString(low) + ")";
    }

    @Override
    public boolean isZeroConstant() {
      if ((high == 0) && (low == 0)) {
        return true;
      } else {
        return false;
      }
    }

    @Override
    public boolean isOneConstant() {
      if ((high == 0) && (low == 1)) {
        return true;
      } else {
        return false;
      }
    }
}
