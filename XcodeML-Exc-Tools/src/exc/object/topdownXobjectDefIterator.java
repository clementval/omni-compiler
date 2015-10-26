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

import java.util.LinkedList;

public class topdownXobjectDefIterator
{
    private LinkedList<XobjectDef> defQueue = new LinkedList<XobjectDef>();
    private XobjectDef curDef;
    
    public topdownXobjectDefIterator(XobjectDef def)
    {
        defQueue.add(def);
    }
    
    public topdownXobjectDefIterator(XobjectDefEnv env)
    {
        for(XobjectDef def : env) {
            defQueue.add(def);
        }
    }
    
    public void init()
    {
        next();
    }
    
    public void next()
    {
        if(defQueue.isEmpty()) {
            curDef = null;
            return;
        }
        curDef = defQueue.removeFirst();
        
        if(curDef.hasChildren()) {
            for(XobjectDef def : curDef.getChildren())
                defQueue.add(def);
        }
    }
    
    public XobjectDef getDef()
    {
        return curDef;
    }
    
    public boolean end()
    {
        return curDef == null && defQueue.isEmpty();
    }
}
