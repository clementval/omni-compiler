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

/**
 * super class for Block iterator
 */
public abstract class BlockIterator
{
    Block currentBlock;

    /** constructor with block */
    public BlockIterator(Block b)
    {
        currentBlock = b; // set defaults
    }

    public BlockIterator(BlockList body)
    {
        // nothing
    }

    public abstract void init();

    public abstract void init(Block b);

    public abstract void next();

    public abstract boolean end();

    public abstract int size();

    /** Return the current block */
    public Block getBlock()
    {
        return currentBlock;
    }

    /* + replace the current block with Block b */
    public void setBlock(Block b)
    {
        currentBlock.replace(b);
    }
}
