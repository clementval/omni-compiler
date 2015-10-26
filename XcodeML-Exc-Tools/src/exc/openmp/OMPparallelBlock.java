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
package exc.openmp;

import exc.block.*;
import exc.object.*;

/**
 * OpenMP parallel block
 */
public class OMPparallelBlock extends OMPBlock
{
    public OMPparallelBlock(int narg, BasicBlock setup, BlockList body, Xobject cond)
    {
        super(Xcode.OMP_PARALLEL, setup);
        setNarg(narg);
        setup.setExpr(cond); // set cond exp at end of setup bb.
        setBody(body);
    }

    public BasicBlock setupBasicBlock()
    {
        return getBasicBlock();
    }

    public Xobject getIfExpr()
    {
        return beginBasicBlock().getExpr();
    }
}
