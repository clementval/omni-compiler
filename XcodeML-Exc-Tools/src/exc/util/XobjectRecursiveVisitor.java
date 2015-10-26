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
package exc.util;

import exc.object.XobjList;
import exc.object.Xobject;
import exc.object.XobjectDef;
import exc.object.XobjectDefEnv;

/**
 * Xobject Visitor which visits objects recursively
 */
public class XobjectRecursiveVisitor implements XobjectVisitor
{
    @Override
    public boolean enter(Xobject v)
    {
        if(v instanceof XobjList) {
            for(Xobject a : (XobjList)v) {
                if(a != null && !a.enter(this))
                    return false;
            }
        }
        
        return true;
    }

    @Override
    public boolean enter(XobjectDef v)
    {
        if((v.getDef() != null) && !v.getDef().enter(this)) {
            return false;
        }
        if(v.hasChildren()) {
            for(XobjectDef d : v.getChildren()) {
                if(!d.enter(this))
                    return false;
            }
        }
        return true;
    }

    @Override
    public boolean enter(XobjectDefEnv v)
    {
        for(XobjectDef def : v) {
            if(def != null && !def.enter(this))
                return false;
        }
        return true;
    }
}
