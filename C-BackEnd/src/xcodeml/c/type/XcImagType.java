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
 * type of '_Imaginary'
 */
public abstract class XcImagType extends XcNumType
{
    public XcImagType(XcBaseTypeEnum basicTypeEnum, String typeId)
    {
        super(basicTypeEnum, typeId);
    }

    public static final class FloatImag extends XcImagType
    {
        public FloatImag()
        {
            this(null);
        }
        
        public FloatImag(String typeId)
        {
            super(XcBaseTypeEnum.FLOAT_IMAG, typeId);
        }
    }

    public static final class DoubleImag extends XcImagType
    {
        public DoubleImag()
        {
            this(null);
        }
        
        public DoubleImag(String typeId)
        {
            super(XcBaseTypeEnum.DOUBLE_IMAG, typeId);
        }
    }

    public static final class LongDoubleImag extends XcImagType
    {
        public LongDoubleImag()
        {
            this(null);
        }
        
        public LongDoubleImag(String typeId)
        {
            super(XcBaseTypeEnum.LONGDOUBLE_IMAG, typeId);
        }
    }
}
