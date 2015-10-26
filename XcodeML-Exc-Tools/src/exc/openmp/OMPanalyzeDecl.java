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

import exc.object.*;
import exc.block.*;

import java.util.Vector;

import xcodeml.util.XmOption;

public class OMPanalyzeDecl implements OMPfileEnv
{
    private XobjectFile env;
    
    private Vector<Ident> thdprv_vars = new Vector<Ident>();
    
    private static final String PROP_KEY = "OMPanalyzeDecl";
    
    private OMPanalyzeDecl parent;

    public OMPanalyzeDecl(XobjectFile env)
    {
        this.env = env;
    }
    
    @Override
    public XobjectFile getFile()
    {
        return env;
    }

    private void setToXobject(PropObject o)
    {
        o.setProp(PROP_KEY, this);
    }
    
    private OMPanalyzeDecl getParent(XobjectDef def)
    {
        if(parent != null)
            return parent;
        
        PropObject p = def.getParent();
        if(p == null)
            p = def.getParentEnv();
        if(p == null)
            throw new IllegalStateException();
        OMPanalyzeDecl a = (OMPanalyzeDecl)p.getProp(PROP_KEY);
        if(a == null) {
            a = new OMPanalyzeDecl(def.getFile());
            p.setProp(PROP_KEY, a);
        }
        parent = a;
        return a;
    }
    
    public void analyze(XobjectDef def)
    {
        Xobject x = def.getDef();
        
        if(x.Opcode() == Xcode.OMP_PRAGMA) {
            // (OMP_PRAGMA (STRING PragmaSyntax) (STRING OMPPragma) (LIST ...))
            if(OMPpragma.valueOf(x.getArg(1)) != OMPpragma.THREADPRIVATE)
                OMP.fatal("not threadprivate in decl");
            getParent(def).declThreadPrivate(x, def, x.getArg(2));
            def.setDef(null);
        } else if(def.isFuncDef() || def.isFmoduleDef()) {
            setToXobject(def);
            getParent(def); // to set parent
            topdownXobjectIterator ite = def.getDef().topdownIterator();
            for(ite.init(); !ite.end(); ite.next()) {
                x = ite.getXobject();
                if(x == null || x.Opcode() == null)
                    continue;
                switch(x.Opcode()) {
                case OMP_PRAGMA:
                    // (OMP_PRAGMA (STRING OMPPragma) (LIST ...))
                    if(OMPpragma.valueOf(x.getArg(0)) == OMPpragma.THREADPRIVATE) {
                        if(def.isFmoduleDef()) {
                            OMP.error((LineNo)def.getLineNo(),
                                "threadprivate for module variable is not supported");
                        } else
                            declThreadPrivate(x, def, x.getArg(1));
                        ite.setXobject(Xcons.List(Xcode.NULL));
                    }
                    break;
                }
            }
        }
    }
    
    // declare threadprivate variables
    @Override
    public void declThreadPrivate(Xobject x, IVarContainer vc, Xobject args)
    {
        Xtype voidP_t = Xtype.Pointer(Xtype.voidType);
        for(XobjArgs a = args.getArgs(); a != null; a = a.nextArgs()) {
            String name = a.getArg().getName();
            Ident id = (vc != null) ? vc.findVarIdent(name) : x.findVarIdent(name);
            if(id == null) {
                OMP.fatal("undefined variable '" + name
                    + "' in threadprivate directive");
                continue;
            }

            if(isThreadPrivate(id))
                continue; // already defined as threadprivate
            thdprv_vars.addElement(id);

            OMP.setThreadPrivate(id);
            
            if(OMP.leaveThreadPrivateFlag)
                continue;

            switch(id.getStorageClass()) {
            case EXTDEF:
            case EXTERN:
            case STATIC:
            case FCOMMON:
            case FSAVE:
                break;
            default:
                if(XmOption.isLanguageC()) {
                    OMP.error(x.getLineNo(), "variable '" + id.getName()
                        + "' is not extern or static variable.");
                } else {
                    OMP.error(x.getLineNo(), "variable '" + id.getName()
                        + "' does not have common or save attribute.");
                }
                return;
            }
            
            if(XmOption.isLanguageC()) {
                // declare threadprivate pointer table
                String thdprv_name = OMPtransPragma.THDPRV_STORE_PREFIX + id.getName();
                switch(id.getStorageClass()) {
                case EXTDEF:
                    env.declGlobalIdent(thdprv_name, voidP_t);
                    break;
                case EXTERN:
                    env.declExternIdent(thdprv_name, voidP_t);
                    break;
                case STATIC:
                    env.declStaticIdent(thdprv_name, voidP_t);
                    break;
                default:
                    OMP.fatal("declThreadPrivate: bad class, " + id.getName());
                }
            }
        }
    }

    @Override
    public boolean isThreadPrivate(Ident id)
    {
        if(thdprv_vars.contains(id))
            return true;
        return (parent != null) ? parent.isThreadPrivate(id) : false;
    }

    @Override
    public Ident findThreadPrivate(Block b, String name)
    {
        for(Ident id : thdprv_vars) {
            if(id.getName().equals(name))
                return id;
        }
        
        return (parent != null) ? parent.findThreadPrivate(b, name) : null;
    }
}
