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
 * struct/union member list (element type is XmIdent)
 */
public final class XcMemberList extends XcIdentList
{
    private XcType _parentType;
    
    public XcMemberList(XcType parentType)
    {
        _parentType = parentType;
    }

    @Override
    public final void add(XcIdent e)
    {
        super.add(e);
        e.setVarKindEnum(XcVarKindEnum.MEMBER);
        e.setParentType(_parentType);
    }

    public final void appendCode(XmcWriter w) throws XmException
    {
        Iterator<XcIdent> ite = iterator();

        w.spc().add('{').lf();

        for(; ite.hasNext();) {
            XcIdent ident = ite.next();
            String symbol = ident.getSymbol();
            XcType type = ident.getType();

            ident.appendGccExtension(w);

            type.appendDeclCode(w, symbol, true, false);

            if(ident.getIsBitField()) {
                w.add(":");
                if(ident.getIsBitFieldExpr()) {
                    w.add(ident.getBitFieldExpr());
                } else {
                    w.add(ident.getBitField());
                }
            }

            w.add(ident.getGccAttribute());

            w.add(';').lf();
        }
        
        w.add('}');
    }
}
