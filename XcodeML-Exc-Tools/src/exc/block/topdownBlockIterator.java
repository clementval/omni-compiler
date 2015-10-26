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

public class topdownBlockIterator extends BlockIterator
{
    Vector<Block> blocks;
    int index;

    public topdownBlockIterator(Block b)
    {
        super(b);
        init(b);
    }

    public topdownBlockIterator(BlockList body)
    {
        super(body);
        init(body);
    }

    @Override
    public void init()
    {
        index = 0;
        if(blocks.size() > 0)
            currentBlock = blocks.elementAt(0);
    }

    @Override
    public void init(Block b)
    {
        blocks = new Vector<Block>();
        topdownTraverse(b);
        index = 0;
        if(blocks.size() > 0)
            currentBlock = blocks.elementAt(0);
    }

    public void init(BlockList body)
    {
        blocks = new Vector<Block>();
        topdownTraverse(body);
        index = 0;
        if(blocks.size() > 0)
            currentBlock = blocks.elementAt(0);
    }

    void topdownTraverse(Block b)
    {
        if(b == null)
            return;
        blocks.addElement(b);
        if(b instanceof IfBlock) {
            topdownTraverse(b.getThenBody());
            topdownTraverse(b.getElseBody());
        } else if(b instanceof FmoduleBlock){
            topdownTraverse(b.getBody());
            topdownTraverse(((FmoduleBlock)b).getFunctionBlocks());
        } else {
            topdownTraverse(b.getBody());
        }
    }

    void topdownTraverse(BlockList b_list)
    {
        if(b_list == null)
            return;
        for(Block b = b_list.getHead(); b != null; b = b.getNext()) {
            topdownTraverse(b);
        }
    }

    @Override
    public void next()
    {
        if(++index >= blocks.size())
            currentBlock = null;
        else
            currentBlock = blocks.elementAt(index);
    }

    @Override
    public boolean end()
    {
        return index >= blocks.size();
    }

    @Override
    public int size()
    {
        return blocks.size();
    }
}
