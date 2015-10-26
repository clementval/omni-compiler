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

import java.util.Vector;

//
// BasicBlock iterator, traverse in toplogical sort order
//
public class BasicBlockIterator implements BasicBlockVisitor
{
    Vector<BasicBlock> bblocks;
    BasicBlock currentBlock;
    int index;

    public BasicBlockIterator(Block b)
    {
        init(b);
    }

    public BasicBlockIterator(BlockList body)
    {
        init(body);
    }

    public void init()
    {
        index = 0;
        if(bblocks.size() > 0)
            currentBlock = bblocks.elementAt(0);
    }

    public void init(Block b)
    {
        bblocks = new Vector<BasicBlock>();
        visit(b);
        index = 0;
        if(bblocks.size() > 0)
            currentBlock = bblocks.elementAt(0);
    }

    public void init(BlockList body)
    {
        bblocks = new Vector<BasicBlock>();
        visit(body);
        index = 0;
        if(bblocks.size() > 0)
            currentBlock = bblocks.elementAt(0);
    }

    public void visit(Block b)
    {
        if(b == null)
            return;
        b.visitBasicBlock(this);
        b.visitBody(this);
    }

    public void visit(BasicBlock bb)
    {
        if(bb != null)
            bblocks.addElement(bb);
    }

    public void visit(BlockList b_list)
    {
        if(b_list == null)
            return;
        for(Block b = b_list.getHead(); b != null; b = b.getNext()) {
            visit(b);
        }
    }

    public void next()
    {
        if(++index >= bblocks.size())
            currentBlock = null;
        else
            currentBlock = bblocks.elementAt(index);
    }

    public boolean end()
    {
        return index == bblocks.size();
    }

    public int size()
    {
        return bblocks.size();
    }

    // return current block
    public BasicBlock getBasicBlock()
    {
        return currentBlock;
    }
}
