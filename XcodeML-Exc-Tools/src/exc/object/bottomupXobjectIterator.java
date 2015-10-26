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
package exc.object;

import java.util.Stack;

public class bottomupXobjectIterator extends XobjectIterator
{
    Stack<Xobject> obj_stack;
    Stack<XobjArgs> arg_stack;

    XobjArgs prevArgs = null;

    public bottomupXobjectIterator(Xobject x)
    {
        topXobject = x;
    }

    @Override
    public void init()
    {
        init(topXobject);
    }

    @Override
    public void init(Xobject x)
    {
        obj_stack = new Stack<Xobject>();
        arg_stack = new Stack<XobjArgs>();

        currentXobject = x;
        while(currentXobject != null && currentXobject.Opcode() != Xcode.ID_LIST
            && currentXobject instanceof XobjList && currentXobject.getArgs() != null) {
            obj_stack.push(currentXobject);
            arg_stack.push(currentArgs);
            currentArgs = null;
            for(XobjArgs args = currentXobject.getArgs(); args != null; args = args.nextArgs()) {
                arg_stack.push(currentArgs);
                currentArgs = args;
            }
            currentXobject = currentArgs.getArg(); // next
        }
    }

    @Override
    public void next()
    {
        prevArgs = currentArgs;

        if(obj_stack.empty()) {
            currentXobject = null;
            return;
        }
        currentArgs = arg_stack.pop();
        if(currentArgs == null) {
            currentXobject = obj_stack.pop();
            currentArgs = arg_stack.pop();
            return;
        }
        currentXobject = currentArgs.getArg();
        while(currentXobject != null && currentXobject.Opcode() != Xcode.ID_LIST
            && currentXobject instanceof XobjList && currentXobject.getArgs() != null) {
            obj_stack.push(currentXobject);
            arg_stack.push(currentArgs);
            currentArgs = null;
            for(XobjArgs args = currentXobject.getArgs(); args != null; args = args.nextArgs()) {
                arg_stack.push(currentArgs);
                currentArgs = args;
            }
            currentXobject = currentArgs.getArg(); // next
        }
    }

    public void setPrevXobject(Xobject x)
    {
        prevArgs.setArg(x);
    }

    public Xobject getPrevXobject()
    {
        return prevArgs.getArg();
    }

    @Override
    public boolean end()
    {
        return currentXobject == null && obj_stack.empty();
    }

    @Override
    public Xobject getParent()
    {
        if(obj_stack.empty())
            return null;
        else
            return obj_stack.peek();
    }
}
