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
 * Represents function type.
 */
public class FunctionType extends Xtype
{
    Xtype ref; // return type
    Xobject param_list;
    boolean is_function_proto;
    private String fresult_name;

    public FunctionType(String id, Xtype ref, Xobject param_list, int typeQualFlags,
        boolean is_func_proto, Xobject gccAttrs, String fresult_name)
    {
        super(Xtype.FUNCTION, id, typeQualFlags, gccAttrs);
        this.ref = ref;
        this.param_list = param_list;
        this.is_function_proto = is_func_proto;
        this.fresult_name = fresult_name;
    }

    public FunctionType(Xtype ref, int typeQualFlags)
    {
        this(null, ref, null, typeQualFlags, false, null, null);
    }

    public FunctionType(Xtype ref)
    {
        this(ref, 0);
    }
    
    @Override
    public Xtype getRef()
    {
        return ref;
    }

    @Override
    public Xobject getFuncParam()
    {
        return param_list;
    }
    
    @Override
    public boolean isFuncProto()
    {
        return is_function_proto;
    }

    @Override
    public String getFuncResultName()
    {
        return fresult_name;
    }

    public void setFuncResultName(String fresult_name)
    {
        this.fresult_name = fresult_name;
    }

    public void setFuncParam(Xobject param_list)
    {
        this.param_list = param_list;
        this.is_function_proto = true;
    }

    public void setFuncParamIdList(Xobject id_list)
    {
        Xobject param_list = Xcons.List();
        for(Xobject a : (XobjList)id_list) {
            Ident id = (Ident)a;
            param_list.add(Xcons.Symbol(Xcode.IDENT, id.Type(), id.getName()));
        }
        setFuncParam(param_list);
    }
    
    @Override
    public Xtype copy(String id)
    {
        return new FunctionType(id, ref, param_list != null ? param_list.copy() : null,
            getTypeQualFlags(), is_function_proto, getGccAttributes(), fresult_name);
    }

    @Override
    public Xtype getBaseRefType()
    {
        return ref.getBaseRefType();
    }
}
