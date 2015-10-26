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
// for pragma
//
public class PragmaBlock extends CompoundBlock
{
    String pragma;
    Xobject args;

    // statement block with null BasicBlock
    public PragmaBlock(Xcode code, String pragma, Xobject args, BlockList body)
    {
        super(code, body);
        LineNo ln = getLineNo();
        if(ln != null)
            setLineNo(new LineNo(ln.fileName(), ln.lineNo() - 1));
        this.code = code;
        this.pragma = pragma;
        this.args = args;
    }

    public String getPragma()
    {
        return pragma;
    }

    public Xobject getClauses()
    {
        return args;
    }

    public void setClauses(Xobject args)
    {
        this.args = args;
    }

    public void addClauses(Xobject args)
    {
	if (this.args == null){
	    this.args = Xcons.List(args);
	}
	else {
	    ((XobjList)this.args).add(args);
	}
    }

    @Override
    public Xobject toXobject()
    {
        Xobject x = new XobjList(Opcode(),
            Xcons.String(pragma), args, super.toXobject());
        x.setLineNo(getLineNo());
        return x;
    }
}
