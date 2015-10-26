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

import exc.openmp.OMPpragmaParser;
import xcodeml.XmException;

import java.util.Stack;

/**
 * Base pragma parser.
 */
public class PragmaParser
{
    /** XobjectFile of target AST */
    private XobjectFile xobjFile;
    
    private OMPpragmaParser ompPragmaParser;
    
    /** A stack of environments. */
    protected Stack<XobjList> stackEnv = new Stack<XobjList>();

    public PragmaParser(XobjectFile xobjFile)
    {
        this.xobjFile = xobjFile;
        ompPragmaParser = new OMPpragmaParser(this);
        pushEnv((XobjList)xobjFile.getGlobalIdentList());
    }

    public void pushEnv(XobjList v)
    {
        stackEnv.push(v);
    }

    public void popEnv()
    {
        stackEnv.pop();
    }

    public XobjList peekEnv()
    {
        return stackEnv.peek();
    }
    
    public Ident findIdent(String name, int find_kind)
    {
        for(int i = stackEnv.size() - 1; i >=0; --i) {
            XobjList id_list = stackEnv.get(i);
            Ident id = id_list.findIdent(name, find_kind);
            if(id != null)
                return id;
        }
        
        return null;
    }

    public class Result
    {
        public final PragmaSyntax pragma_syntax;
        public final Xobject xobject;

        public Result(PragmaSyntax pragma_syntax, Xobject obj)
        {
            this.pragma_syntax = pragma_syntax;
            this.xobject = obj;
        }
    };
    
    public XobjectFile getXobjectFile()
    {
        return xobjFile;
    }
    
    public Xobject parse(Xobject x) throws XmException
    {
        switch(x.Opcode()) {
        case OMP_PRAGMA:
            return ompPragmaParser.parse(x);
        case XMP_PRAGMA:
            // do nothing for XcalableMP directives
            return x;
        }
        return x;
    }
    
    public boolean isPrePostPair(Xobject prefix, Xobject postfix)
    {
        switch(prefix.Opcode()) {
        case OMP_PRAGMA:
            return ompPragmaParser.isPrePostPair(prefix, postfix);
        }
        return false;
    }
    
    public void completePragmaEnd(Xobject prefix, Xobject body)
    {
        switch(prefix.Opcode()) {
        case OMP_PRAGMA:
            ompPragmaParser.completePragmaEnd(prefix, body);
            break;
        }
    }
    
    public XobjArgs getAbbrevPostfix(XobjArgs prefixArgs)
    {
        switch(prefixArgs.getArg().Opcode()) {
        case OMP_PRAGMA:
            return ompPragmaParser.getAbbrevPostfix(prefixArgs);
        }
        return null;
    }
    
    public void mergeStartAndPostfixArgs(Xobject start, Xobject postfix)
    {
        switch(start.Opcode()) {
        case OMP_PRAGMA:
            ompPragmaParser.mergeStartAndPostfixArgs(start, postfix);
        }
    }
}
