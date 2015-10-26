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

//
// Block, which has one condition and body
//   WHIILE_STATEMENT, DO_STATEMENT, SWITCH_STATEMENT
//
public class CondBlock extends Block
{
    BlockList body;

    public CondBlock(Xcode code, BasicBlock cond, BlockList body, String constructName)
    {
        super(code, cond, constructName);
        this.body = body;
        body.parent = this;
    }
    
    public CondBlock(CondBlock b)
    {
        super(b);
        body = b.body.copy();
        body.parent = this;
    }

    @Override
    public Block copy()
    {
        return new CondBlock(this);
    }

    @Override
    public BlockList getBody()
    {
        return body;
    }

    @Override
    public void setBody(BlockList s)
    {
        body = s;
        s.parent = this;
    }

    @Override
    public BasicBlock getCondBBlock()
    {
        return bblock;
    }

    public void setCondBBlock(BasicBlock bb)
    {
        bblock = bb;
        bb.parent = this;
    }

    @Override
    public Xobject toXobject()
    {
        Xobject x;
        Xobject cond_x = null;
        if(bblock != null)
            cond_x = bblock.toXobject();

        switch(code) {
        case DO_STATEMENT:
            x = new XobjList(code, body.toXobject(), cond_x);
            break;
        case SWITCH_STATEMENT:
        case WHILE_STATEMENT:
        case FOR_STATEMENT:
            x = new XobjList(code, cond_x, body.toXobject());
            break;
        case F_DO_WHILE_STATEMENT:
        case F_SELECT_CASE_STATEMENT:
            x = new XobjList(code, getConstructNameObj(), cond_x, body.toXobject());
            break;
        default:
            throw new IllegalStateException(code.toString());
        }
        
        x.setLineNo(getLineNo());
        return x;
    }
    
    @Override
    public String toString()
    {
        StringBuilder s = new StringBuilder(256);
        s.append("(CondBlock ");
        s.append(Opcode());
        s.append(" ");
        s.append(body);
        s.append(" ");
        s.append(getBasicBlock());
        s.append(")");
        return s.toString();
    }
}
