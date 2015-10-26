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

// Warning !
// topdownXobjectIterator.setXobject cannot be applied to the topXobject.

public class topdownXobjectIterator extends XobjectIterator
{
    Stack<Xobject> obj_stack;
    Stack<XobjArgs> arg_stack;

    public topdownXobjectIterator(Xobject x)
    {
        topXobject = x;
    }

    @Override
    public void init(Xobject x)
    {
        obj_stack = new Stack<Xobject>();
        arg_stack = new Stack<XobjArgs>();
        currentXobject = x;
    }

    @Override
    public void init()
    {
        init(topXobject);
    }

    @Override
    public void next()
    {
        if(currentXobject != null && currentXobject.Opcode() != Xcode.ID_LIST
            && currentXobject instanceof XobjList && currentXobject.getArgs() != null) {
            // save current top
            obj_stack.push(currentXobject);
            arg_stack.push(currentArgs);
            currentArgs = currentXobject.getArgs();
            currentXobject = currentArgs.getArg();
            return;
        }
        while(!obj_stack.empty()) {
            currentArgs = currentArgs.nextArgs();
            if(currentArgs != null) {
                currentXobject = currentArgs.getArg();
                return;
            }
            obj_stack.pop();
            currentArgs = arg_stack.pop();
        }
        currentXobject = null;
        return;
    }

    public void setXobject(Xobject x)
    {
      // fix me
      //      if(currentArgs == null){
      //	currentArgs = new XobjArgs(null, null);
      //      }

      currentArgs.setArg(x);
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
