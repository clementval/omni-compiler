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

import xcodeml.util.XmOption;
import exc.object.*;
import exc.block.*;

/**
 * OpenMP AST translator
 */
public class OMPtranslate implements XobjectDefVisitor
{
    BlockPrintWriter debug_out;
    XobjectFile env;

    // alorithms
    OMPanalyzePragma anaPragma = new OMPanalyzePragma();
    OMPrewriteExpr rewriteExpr = new OMPrewriteExpr();
    OMPtransPragma transPragma = new OMPtransPragma();
    
    public OMPtranslate()
    {
    }
    
    public OMPtranslate(XobjectFile env)
    {
        init(env);
    }

    public void init(XobjectFile env)
    {
        this.env = env;
        if(OMP.debugFlag)
            debug_out = new BlockPrintWriter(System.out);
    }
    
    public void finish()
    {
        FmoduleBlock mod = (FmoduleBlock)env.getProp(OMPtransPragma.PROP_KEY_FINTERNAL_MODULE);
        if(mod != null) {
            XobjectDef lastMod = null;
            for(XobjectDef d : env) {
                if(d.isFmoduleDef())
                    lastMod = d;
            }
            if(lastMod == null)
                env.insert(mod.toXobjectDef());
            else
                lastMod.addAfterThis(mod.toXobjectDef());
        }
        env.collectAllTypes();
        env.fixupTypeRef();
    }
    
    private void replace_main(XobjectDef d)
    {
        String name = d.getName();
        Ident id = env.findVarIdent(name);
        if(id == null)
            OMP.fatal("'" + name + "' not in id_list");
        id.setName(transPragma.mainFunc);
        d.setName(transPragma.mainFunc);
    }

    // do transform takes three passes
    public void doDef(XobjectDef d)
    {
        OMP.resetError();

        OMPanalyzeDecl anaDecl = new OMPanalyzeDecl(env);
        anaDecl.analyze(d);
        
        if(OMP.hasError())
            return;
        
        if(!d.isFuncDef()) {
            return;
        }
        
        if(XmOption.isLanguageC()) {
            if(d.getName().equals("main"))
                replace_main(d);
        } else {
            Xtype ft = d.getFuncType();
            if(ft != null && ft.isFprogram()) {
                ft.setIsFprogram(false);
                replace_main(d);
            }
        }
        
        FuncDefBlock fd = new FuncDefBlock(d);
        if(XmOption.isLanguageC())
            fd.removeDeclInit();

        if(OMP.hasError())
            return;
        
        anaPragma.run(fd, anaDecl);
        if(OMP.hasError())
            return;

        rewriteExpr.run(fd, anaDecl);
        if(OMP.hasError())
            return;

        transPragma.run(fd);
        if(OMP.hasError())
            return;
        
        // finally, replace body
        fd.Finalize();
    }

    // not used?
    boolean haveOMPpragma(Xobject x)
    {
        XobjectIterator i = new topdownXobjectIterator(x);
        for(i.init(); !i.end(); i.next()) {
            Xobject xx = i.getXobject();
            if(xx != null && xx.Opcode() == Xcode.OMP_PRAGMA)
                return true;
        }
        return false;
    }
}
