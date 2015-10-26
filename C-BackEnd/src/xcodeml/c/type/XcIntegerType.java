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
package xcodeml.c.type;

/**
 * type of 'char', 'short', 'int', 'long', 'long long'
 */
public abstract class XcIntegerType extends XcNumType
{
    public XcIntegerType(XcBaseTypeEnum basicTypeEnum, String typeId)
    {
        super(basicTypeEnum, typeId);
    }
    
    public static final class Char extends XcIntegerType
    {
        public Char()
        {
            this(null);
        }
        
        public Char(String typeId)
        {
            super(XcBaseTypeEnum.CHAR, typeId);
        }
    }
    
    public static final class Short extends XcIntegerType
    {
        public Short()
        {
            this(null);
        }
        
        public Short(String typeId)
        {
            super(XcBaseTypeEnum.SHORT, typeId);
        }
    }
    
    public static final class Int extends XcIntegerType
    {
        public Int()
        {
            this(null);
        }
        
        public Int(String typeId)
        {
            super(XcBaseTypeEnum.INT, typeId);
        }
    }

    public static final class Long extends XcIntegerType
    {
        public Long()
        {
            this(null);
        }
        
        public Long(String typeId)
        {
            super(XcBaseTypeEnum.LONG, typeId);
        }
    }

    public static final class LongLong extends XcIntegerType
    {
        public LongLong()
        {
            this(null);
        }
        
        public LongLong(String typeId)
        {
            super(XcBaseTypeEnum.LONGLONG, typeId);
        }
    }

    public static final class Bool extends XcIntegerType
    {
        public Bool()
        {
            this(null);
        }
        
        public Bool(String typeId)
        {
            super(XcBaseTypeEnum.BOOL, typeId);
        }
    }

    public static final class Wchar extends XcIntegerType
    {
        public Wchar()
        {
            this(null);
        }
        
        public Wchar(String typeId)
        {
            super(XcBaseTypeEnum.WCHAR, typeId);
        }
    }

    public static final class UChar extends XcIntegerType
    {
        public UChar()
        {
            this(null);
        }
        
        public UChar(String typeId)
        {
            super(XcBaseTypeEnum.UCHAR, typeId);
        }
    }

    public static final class UShort extends XcIntegerType
    {
        public UShort()
        {
            this(null);
        }
        
        public UShort(String typeId)
        {
            super(XcBaseTypeEnum.USHORT, typeId);
        }
    }
    
    public static final class UInt extends XcIntegerType
    {
        public UInt()
        {
            this(null);
        }
        
        public UInt(String typeId)
        {
            super(XcBaseTypeEnum.UINT, typeId);
        }
    }

    public static final class ULong extends XcIntegerType
    {
        public ULong()
        {
            this(null);
        }
        
        public ULong(String typeId)
        {
            super(XcBaseTypeEnum.ULONG, typeId);
        }
    }

    public static final class ULongLong extends XcIntegerType
    {
        public ULongLong()
        {
            this(null);
        }
        
        public ULongLong(String typeId)
        {
            super(XcBaseTypeEnum.ULONGLONG, typeId);
        }
    }
}
