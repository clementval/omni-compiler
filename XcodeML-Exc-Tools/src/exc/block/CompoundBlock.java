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
 * Compound block with code COMPOUND_STATEMENT.
 */
public class CompoundBlock extends Block
{
    BlockList body;

    /** constructor with BlockList */
    public CompoundBlock(BlockList body)
    {
        this(Xcode.COMPOUND_STATEMENT, body, null);
    }

    /** constructor with code and BlockList */
    public CompoundBlock(Xcode code, BlockList body)
    {
        this(code, body, null);
    }
    
    /** constructor with code and BlockList */
    public CompoundBlock(Xcode code, BlockList body, String construct_name)
    {
        super(code, null, construct_name);
        this.body = body;
        if(body != null) {
            body.parent = this;
            setLineNo(body.getHeadLineNo());
        }
    }

    /** make clone */
    public CompoundBlock(CompoundBlock b)
    {
        super(b);
        if(b.body != null)
            this.body = b.body.copy();
    }

    /** make clone */
    @Override
    public Block copy()
    {
        return new CompoundBlock(this);
    }

    /** return body */
    @Override
    public BlockList getBody()
    {
        return body;
    }

    /** set body */
    @Override
    public void setBody(BlockList s)
    {
        body = s;
        s.parent = this;
    }

    /** convert to Xobject representation */
    @Override
    public Xobject toXobject()
    {
        if(body == null)
            return null;
        Xobject x = body.toXobject();
        if(x != null)
            x.setLineNo(getLineNo());
        return x;
    }

    @Override
    public String toString()
    {
        StringBuilder s = new StringBuilder(256);
        s.append("(CompoundBlock ");
        s.append(Opcode());
        s.append(" ");
        s.append(body);
        s.append(" ");
        s.append(getBasicBlock());
        s.append(")");
        return s.toString();
    }
}
