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

public class XobjString extends XobjConst
{
    String value;

    public XobjString(Xcode code, Xtype type, String value, String fkind)
    {
        super(code, type, fkind);
        this.value = value.intern();
    }

    public XobjString(Xcode code, Xtype type, String value)
    {
        this(code, type, value, null);
    }

    public XobjString(Xcode code, String value)
    {
        this(code, null, value);
    }

    @Override
    public String getString()
    {
        return value;
    }

    @Override
    public String getSym()
    {
        return value;
    }

    // used by xcalablemp package
    public void setSym(String newValue)
    {
        value = newValue;
    }

    @Override
    public String getName()
    {
        return value;
    }
    
    public void setName(String newValue)
    {
        value = newValue;
    }

    @Override
    public Xobject cfold(Block block)
    {
      if (value == null) 
        return this.copy();

      Xobject id_list = block.getBody().getIdentList();
      if (id_list == null)
        return this.copy();

      Ident ident = id_list.findVarIdent(value);
      if (ident == null)
        return this.copy();

      return ident.cfold(block);
    }

    @Override
    public Xobject copy()
    {
        return copyTo(new XobjString(code, type, value, getFkind()));
    }

    @Override
    public boolean equals(Xobject x)
    {
        return super.equals(x) && value.equals(x.getString());
    }

    @Override
    public String toString()
    {
        return "(" + OpcodeName() + " " + value + ")";
    }
}
