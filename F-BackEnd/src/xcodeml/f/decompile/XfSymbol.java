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
package xcodeml.f.decompile;

/**
 * Symbol expression in decompiler.
 */
class XfSymbol
{
    private String _symbolName;
    private XfType _typeId;
    private String _derivedName;

    public XfSymbol(String symbolName)
    {
        this(symbolName, XfType.VOID, null);
    }

    public XfSymbol(String symbolName, XfType typeId)
    {
        this(symbolName, typeId, null);
    }

    public XfSymbol(String symbolName, XfType typeId, String derivedName)
    {
        _symbolName = symbolName;
        _typeId = typeId;
        _derivedName = derivedName;
    }

    public XfType getTypeId()
    {
        return _typeId;
    }

    public String getSymbolName()
    {
        return _symbolName;
    }

    public String getDerivedName()
    {
        return _derivedName;
    }
}

