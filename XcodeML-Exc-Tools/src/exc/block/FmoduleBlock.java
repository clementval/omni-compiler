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

import exc.object.Xcode;
import exc.object.Xcons;
import exc.object.XobjString;
import exc.object.Xobject;
import exc.object.XobjectDef;
import exc.object.XobjectFile;

public class FmoduleBlock extends CompoundBlock
{
    private Xobject name;
    
    private BlockList func_blocks;
    
    private XobjectFile env;

    public FmoduleBlock(String name, XobjectFile env)
    {
        super(Xcode.F_MODULE_DEFINITION, new BlockList(Xcons.IDList(), Xcons.List()));
        this.name = new XobjString(Xcode.IDENT, name);
        this.env = env;
        this.func_blocks = new BlockList();
    }
    
    public void addFunctionBlock(FunctionBlock func_block)
    {
        func_blocks.add(func_block);
    }
    
    public Xobject getName()
    {
        return name;
    }
    
    public BlockList getFunctionBlocks()
    {
        return func_blocks;
    }
    
    public FunctionBlock getFunctionBlock(String name)
    {
        for(Block b = func_blocks.getHead(); b != null; b = b.getNext()) {
            if(((FunctionBlock)b).getName().equals(name))
                return (FunctionBlock)b;
        }
        
        return null;
    }
    
    public boolean hasVar(String name)
    {
        Xobject idList = getBody().getIdentList();
        return (idList.findVarIdent(name) != null);
    }
    
    public XobjectDef toXobjectDef()
    {
        Xobject xcontains = Xcons.List(Xcode.F_CONTAINS_STATEMENT);
        for(Block b = func_blocks.getHead(); b != null; b = b.next) {
            xcontains.add(b.toXobject());
        }
        
        return new XobjectDef(Xcons.List(Xcode.F_MODULE_DEFINITION,
            name, getBody().getIdentList(), getBody().getDecls(), xcontains), env);
    }
}
