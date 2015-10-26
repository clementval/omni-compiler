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
package exc.block;

import exc.object.*;

public class LabelBlock extends Block
{
    Xobject label, value, params;

    public LabelBlock(Xcode code, Xobject label)
    {
        this(code, label, null, null);
    }
    
    public LabelBlock(Xcode code, Xobject label, Xobject value, Xobject params)
    {
        super(code, new BasicBlock(), null);
        this.label = label;
        this.value = value;
        this.params = params;
    }

    @Override
    public Xobject getLabel()
    {
        return label;
    }

    @Override
    public void setLabel(Xobject x)
    {
        label = x;
    }

    @Override
    public Xobject toXobject()
    {
        Xobject x = new XobjList(Opcode(), label);
        x.setLineNo(getLineNo());
        if(value != null)
            x.add(value);
        if(params != null)
            x.add(params);
        
        return x;
    }

    @Override
    public String toString()
    {
        StringBuilder s = new StringBuilder(256);
        s.append("(LabelBlock ");
        s.append(Opcode());
        s.append(" ");
        s.append(label);
        if(value != null) {
            s.append(value);
            s.append(" ");
        }
        if(params != null) {
            s.append(params);
            s.append(" ");
        }
        s.append(" ");
        s.append(getBasicBlock());
        s.append(")");
        return s.toString();
    }
    
    @Override
    public LabelBlock copy()
    {
      return new LabelBlock(this.code, this.label, this.value, this.params);
    }
}
