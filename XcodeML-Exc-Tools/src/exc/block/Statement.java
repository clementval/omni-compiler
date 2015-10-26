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
// statement
//
public class Statement
{
    Statement prev, next;
    BasicBlock parent;
    Xobject statement;

    LineNo lineno; // lineno information

    public Statement(Xobject statement)
    {
        this.statement = statement;
    }

    public Statement getNext()
    {
        return next;
    }

    public Statement getPrev()
    {
        return prev;
    }

    public BasicBlock getParent()
    {
        return parent;
    }

    public Xobject getExpr()
    {
        return statement;
    }

    public void setExpr(Xobject x)
    {
        statement = x;
    }

    public void setLineNo(LineNo ln)
    {
        lineno = ln;
    }

    public LineNo getLineNo()
    {
        return lineno;
    }

    // remove itself
    public void remove()
    {
        if(parent == null)
            return; // already removed
        if(prev == null) { // head of double linked list
            parent.head = next;
            if(next != null)
                next.prev = null;
        } else
            prev.next = next;
        if(next == null) { // tail of double linked list
            parent.tail = prev;
            if(prev != null)
                prev.next = null;
        } else
            next.prev = prev;
        parent = null;
        next = null;
        prev = null;
    }

    public boolean isRemoved()
    {
        return parent == null;
    }

    // add s after this
    public Statement add(Xobject x)
    {
        return add(new Statement(x));
    }

    public Statement add(Statement s)
    {
        s.parent = parent;
        s.next = next;
        next = s;
        s.prev = this;
        if(s.next == null) { // tail of list
            parent.tail = s;
        } else {
            s.next.prev = s;
        }
        return s;
    }

    // insert s before this
    public Statement insert(Xobject x)
    {
        return insert(new Statement(x));
    }

    public Statement insert(Statement s)
    {
        s.parent = parent;
        s.prev = prev;
        prev = s;
        s.next = this;
        if(s.prev == null) { // head of list
            parent.head = s;
        } else {
            s.prev.next = s;
        }
        return s;
    }

    // insert block before this statement
    public void insertBlock(Block b)
    {
        Block b0 = parent.parent;
        if(parent.head != this) { // not head, then move precedings to new
            BasicBlock bb_new = new BasicBlock();
            bb_new.head = parent.head;
            for(Statement s = parent.head; s != this; s = s.next)
                s.parent = bb_new;
            this.prev.next = null; // tail
            this.prev = null;
            parent.head = this; // this is head
            b0.insert(Bcons.BasicBlock(bb_new));
        }
        b0.insert(b);
    }
    
    @Override
    public String toString()
    {
        return statement == null ? "()" : statement.toString();
    }
}
