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
import exc.block.Block;

/**
 * Represents C-struct / Fortran-type type.
 */
public class StructType extends CompositeType
{
    public StructType(String id, XobjList id_list, int typeQualFlags, Xobject gccAttrs,
                      Xobject[] codimensions)
    {
        super(Xtype.STRUCT, id, id_list, typeQualFlags, gccAttrs, codimensions);
    }

    public StructType(String id, XobjList id_list, int typeQualFlags, Xobject gccAttrs)
    {
        this(id, id_list, typeQualFlags, gccAttrs, null);
    }

    @Override
    public Xobject getTotalArraySizeExpr(Block block)
    {
        return Xcons.IntConstant(1);
    }

    @Override
    public Xobject getElementLengthExpr(Block block)
    {
        throw new UnsupportedOperationException
          ("Restriction: could not get size of a structure");
    }

    @Override
    public int getElementLength(Block block)
    {
        throw new UnsupportedOperationException
          ("Restriction: could not get size of a structure as integer");
    }


    @Override
    public Xtype copy(String id)
    {
        StructType t = new StructType(id, getMemberList(), getTypeQualFlags(),
                                      getGccAttributes(), copyCodimensions());
        t.original = (original != null) ? original : this;
        t.tag = (tag != null) ? tag : ((original != null) ? original.tag : null);
        return t;
    }
}
