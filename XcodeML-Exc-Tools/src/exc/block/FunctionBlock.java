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

/**
 * A block object to represent the function body.
 */

public class FunctionBlock extends CompoundBlock
{
    private Xobject name;
    private Xobject gcc_attrs;
    XobjectDefEnv env;

    /**
     * contructor with function name "name", id list, decls, body block and env.
     * id_list and decls are for parameters.
     */
  public FunctionBlock(Xobject name, Xobject id_list, 
		       Xobject decls, Block body_block,
		       Xobject gcc_attrs, XobjectDefEnv env)
    {
        super(Xcode.FUNCTION_DEFINITION, new BlockList(id_list, decls));
        this.env = env;
        this.name = name;
        this.gcc_attrs = gcc_attrs;
        body.add(body_block);
    }

  public FunctionBlock(Xcode opcode, Xobject name, Xobject id_list, 
		       Xobject decls, Block body_block,
		       Xobject gcc_attrs, XobjectDefEnv env)
    {
        super(opcode, new BlockList(id_list, decls));
        this.env = env;
        this.name = name;
        this.gcc_attrs = gcc_attrs;
        body.add(body_block);
    }

    /** returns Function name */
    public String getName()
    {
        return name.getName();
    }
    
    public Xobject getNameObj()
    {
        return name;
    }

    /** return associated XobjectFile env */
    public XobjectDefEnv getEnv()
    {
        return env;
    }

    /** contert to Xobject */
    @Override
    public Xobject toXobject()
    {
        Xobject x = new XobjList(Opcode(),
				 name, body.id_list,
				 body.decls, body.head.toXobject(), 
				 gcc_attrs);
        x.setLineNo(getLineNo());
        return x;
    }

    @Override
    public String toString()
    {
        StringBuilder s = new StringBuilder(256);
        s.append("(FunctionBlock ");
        s.append(name);
        s.append(" ");
        s.append(body);
        s.append(" ");
        s.append(getBasicBlock());
        s.append(")");
        return s.toString();
    }
}
