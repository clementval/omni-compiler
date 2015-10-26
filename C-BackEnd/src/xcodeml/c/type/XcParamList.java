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
package xcodeml.c.type;

import java.util.Iterator;

import xcodeml.XmException;
import xcodeml.c.util.XmcWriter;

/**
 * function parameter list (element type is XmIdent)
 */
public final class XcParamList extends XcIdentList
{
    private boolean _isEllipsised;

    public XcParamList()
    {
        _isEllipsised = false;
    }

    public boolean isEllipsised()
    {
        return _isEllipsised;
    }
    
    public void setIsEllipsised(boolean enable)
    {
        _isEllipsised = enable;
    }
    
    @Override
    public final void add(XcIdent ident)
    {
        ident.setSymbolKindEnum(XcSymbolKindEnum.VAR);
        ident.setVarKindEnum(XcVarKindEnum.PARAM);
        super.add(ident);
    }

    public final void appendArgs(XmcWriter w, boolean paramSymbol, boolean isPreDecl) throws XmException
    {
        w.add("(");

        if(isEmpty() == false) {
            for(Iterator<XcIdent> ite = iterator(); ite.hasNext();) {
                XcIdent ident = ite.next();
                String symbol = (paramSymbol ? ident.getSymbol() : null);
                ident.getType().appendDeclCode(w, symbol, true, isPreDecl);
                if(ite.hasNext())
                    w.add(",");
            }
        }

        if(_isEllipsised)
            w.add(", ...");
        
        w.add(")");
    }
}
