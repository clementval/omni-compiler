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

public class BasicBlockExprIterator
{
    BasicBlockIterator i;
    protected StatementIterator is;
    protected Statement current_statement;
    protected BasicBlock current_bblock;

    // constructor
    public BasicBlockExprIterator(Block b)
    {
        init(b);
    }

    public BasicBlockExprIterator(BlockList body)
    {
        init(body);
    }

    public BasicBlockExprIterator()
    {
    }

    public void init(Block b)
    {
        i = new BasicBlockIterator(b);
        initialize();
    }

    public void init(BlockList body)
    {
        i = new BasicBlockIterator(body);
        initialize();
    }

    public void init()
    {
        i.init();
        initialize();
    }

    // initialize internal iterators
    void initialize()
    {
        current_bblock = i.getBasicBlock();
        if(current_bblock == null)
            return;
        is = current_bblock.statements();
        next();
    }

    public void next()
    {
        current_statement = null; // unset current_statment
        do {
            if(is != null) { // if statement iterator is active,
                if(is.hasMoreStatement()) {
                    current_statement = is.nextStatement();
                    return;
                } else {
                    is = null; // inactive
                    if(current_bblock.getExpr() != null)
                        return;
                }
            }
            // move to the next basic block.
            nextBasicBlock();
            if(current_bblock == null)
                return;
            is = current_bblock.statements();
        } while(true);
    }

    public void nextBasicBlock()
    {
        i.next();
        if(i.end())
            current_bblock = null;
        else
            current_bblock = i.getBasicBlock();
    }

    public boolean end()
    {
        return current_bblock == null;
    }

    public Statement getStatement()
    {
        return current_statement;
    }

    public BasicBlock getBasicBlock()
    {
        return current_bblock;
    }

    public Xobject getExpr()
    {
        if(current_statement != null)
            return current_statement.getExpr();
        else
            return current_bblock.getExpr();
    }

    public void setExpr(Xobject x)
    {
        if(current_statement != null)
            current_statement.setExpr(x);
        else
            current_bblock.setExpr(x);
    }

    public void insertStatement(Xobject s)
    {
        if(current_statement != null)
            current_statement.insert(s);
        else
            current_bblock.add(s);
    }

    public void addStatement(Xobject s)
    {
        if(current_statement != null)
            current_statement.add(s);
        else
            current_bblock.add(s);
    }

    public LineNo getLineNo()
    {
        if(current_statement != null)
            return current_statement.getLineNo();
        else
            return current_bblock.getParent().getLineNo();
    }
}
