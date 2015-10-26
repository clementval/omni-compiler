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
 * Block object to express If statement.
 */
public class IfBlock extends Block
{
    BlockList then_part;
    BlockList else_part;

    public IfBlock(BasicBlock cond, BlockList then_part, BlockList else_part)
    {
        this(Xcode.IF_STATEMENT, cond, then_part, else_part, null);
    }
    
    /** constructor */
    public IfBlock(Xcode code, BasicBlock cond, BlockList then_part, BlockList else_part, String construct_name)
    {
        super(code, cond, construct_name);
        this.then_part = then_part;
        if(then_part != null)
            then_part.parent = this;
        this.else_part = else_part;
        if(else_part != null)
            else_part.parent = this;
    }
    
    /** constructor to make copy of b */
    public IfBlock(IfBlock b)
    {
        super(b);
        if(b.then_part != null)
            this.then_part = b.then_part.copy();
        if(b.else_part != null)
            this.else_part = b.else_part.copy();
    }

    /** return copy of this block */
    @Override
    public Block copy()
    {
        return new IfBlock(this);
    }

    /** return BasicBlock in condition part */
    @Override
    public BasicBlock getCondBBlock()
    {
        return bblock;
    }

    /** set BasicBlock in condition part */
    public void setCondBBlock(BasicBlock bb)
    {
        bblock = bb;
        bb.parent = this;
    }

    /** get the BlockList of "then" part */
    @Override
    public BlockList getThenBody()
    {
        return then_part;
    }

    /** get the BlockList of "else" part */
    @Override
    public BlockList getElseBody()
    {
        return else_part;
    }

    /** set the BlockList of "then" part */
    @Override
    public void setThenBody(BlockList s)
    {
        then_part = s;
        s.parent = this;
    }

    /** set the BlockList of "else" part */
    @Override
    public void setElseBody(BlockList s)
    {
        else_part = s;
        s.parent = this;
    }

    /** apply visitor recursively */
    @Override
    public void visitBody(BasicBlockVisitor v)
    {
        v.visit(then_part);
        v.visit(else_part);
    }

    /** convert to Xobject */
    @Override
    public Xobject toXobject()
    {
        Xobject then_x = null;
        Xobject else_x = null;
        if(getThenBody() != null)
            then_x = getThenBody().toXobject();
        if(getElseBody() != null)
            else_x = getElseBody().toXobject();
        
        Xobject x;
        
        switch(Opcode()) {
        case IF_STATEMENT:
            x = new XobjList(Opcode(), getCondBBlock().toXobject(), then_x, else_x);
            break;
        case F_IF_STATEMENT:
        case F_WHERE_STATEMENT:
            x = new XobjList(Opcode(), getConstructNameObj(), getCondBBlock().toXobject(), then_x, else_x);
            break;
        default:
            throw new IllegalStateException(Opcode().toString());
        }

        x.setLineNo(getLineNo());
        return x;
    }

    @Override
    public String toString()
    {
        StringBuilder s = new StringBuilder(256);
        s.append("(IfBlock ");
        s.append(Opcode());
        s.append(" ");
        s.append(then_part);
        s.append(" ");
        s.append(else_part);
        s.append(" ");
        s.append(getBasicBlock());
        s.append(")");
        return s.toString();
    }
}
