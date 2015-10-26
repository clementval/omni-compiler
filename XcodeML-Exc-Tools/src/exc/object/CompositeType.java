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
 * Represents struct/union or Fortran 'type' type.
 */
public abstract class CompositeType extends Xtype
{
    /** member id list */
    private XobjList id_list;
    /** original type (to suppress output same type) */
    protected CompositeType original;

    protected CompositeType(int type_kind, String id, XobjList id_list, int typeQualFlags,
                            Xobject gccAttrs, Xobject[] codimensions)
    {
        super(type_kind, id, typeQualFlags, gccAttrs, codimensions);
        if(id_list == null)
            id_list = Xcons.List();
        this.id_list = id_list;
    }

    protected CompositeType(int type_kind, String id, XobjList id_list, int typeQualFlags,
                            Xobject gccAttrs)
    {
        this(type_kind, id, id_list, typeQualFlags, gccAttrs, null);
    }


    @Override
    public final XobjList getMemberList()
    {
        return id_list;
    }

    @Override
    public Xtype getMemberType(String member)
    {
        for(Xobject a : id_list) {
            Ident ident = (Ident)a;
            if(member.equals(ident.getName())) {
                return ident.Type();
            }
        }
        
        return null;
    }

    @Override
    public Xtype getBaseRefType()
    {
    	if(original != null)
        	return original.getBaseRefType();
    	if(copied != null)
    		return copied.getBaseRefType();
    	return this;
    }
    
    @Override
    public Xtype getOriginal()
    {
    	return original;
    }
}
