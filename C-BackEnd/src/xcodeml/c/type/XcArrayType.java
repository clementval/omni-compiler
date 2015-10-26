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

import xcodeml.XmException;
import xcodeml.c.util.XmcWriter;

/**
 * type of array
 */
public final class XcArrayType extends XcArrayLikeType
{
    /* type qualifier: static */
    private boolean _isStatic;

    public final boolean isStatic()
    {
        return _isStatic;
    }

    public final void setIsStatic(boolean enable)
    {
        _isStatic = enable;
    }

    public XcArrayType(String typeId)
    {
        super(XcTypeEnum.ARRAY, typeId);
    }

    public final void appendArraySpecCode(
        XmcWriter w, boolean isPreDecl, boolean isFirstIndex)
        throws XmException
    {
        w.add("[");

        this.appendTypeQualCode(w);

        if(_isStatic)
            w.addSpc("static");

        if(isArraySizeExpr() && (getArraySizeExpr() != null)) {
            if(isPreDecl) {
                if(isFirstIndex)
                    w.addSpc("*");
            } else {
                w.addSpc(getArraySizeExpr());
            }
        } else if(isArraySize()){
            w.addSpc(getArraySize());
        }

        w.add("]");
    }

    @Override
    public String toString()
    {
        StringBuilder b = new StringBuilder(128);
        b.append("[");
        commonToString(b);
        b.append("arraySize=").append(getArraySize()).append("]");
        return b.toString();
    }
}
