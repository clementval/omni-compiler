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
 * type of 'coarray'
 */
public final class XcXmpCoArrayType extends XcArrayLikeType
{
    public XcXmpCoArrayType(String typeId)
    {
        super(XcTypeEnum.COARRAY, typeId);
    }

    @Override
    public String toString()
    {
        StringBuilder b = new StringBuilder(128);
        b.append("[");
        commonToString(b);
        b.append("coArraySize=").append(getArraySize()).append("]");
        return b.toString();
    }

    public XcType getElementType()
    {
        XcType refType = getRefType();

        if(refType.getTypeEnum() == XcTypeEnum.COARRAY)
            return ((XcXmpCoArrayType)refType).getElementType();
        else
            return refType;
    }
}
