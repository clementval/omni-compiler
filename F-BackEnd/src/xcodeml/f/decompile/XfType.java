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
 * Type expression in decompiler.
 */
enum XfType
{
    VOID("Fvoid", null, false),
    INT("Fint", "INTEGER", true),
    REAL("Freal", "REAL", true),
    COMPLEX("Fcomplex", "COMPLEX", true),
    LOGICAL("Flogical", "LOGICAL", true),
    CHARACTER("Fcharacter", "CHARACTER", true),
    NUMERIC("Fnumeric", null, true),
    NUMERICALL("FnumericAll", null, true),
    DERIVED(null, null, false);

    private boolean _isPrimitive = false;
    private String _xcodemlName;
    private String _fortranName;

    private XfType(String xcodemlName, String fortranName, boolean isPrimitive)
    {
        _isPrimitive = isPrimitive;
        _xcodemlName = xcodemlName;
        _fortranName = fortranName;
    }

    public boolean isPrimitive()
    {
        return _isPrimitive;
    }

    public String xcodemlName()
    {
        return _xcodemlName;
    }

    public String fortranName()
    {
        return _fortranName;
    }

    public static XfType getTypeIdFromXcodemlTypeName(String xcodemlTypeName)
    {
        if (xcodemlTypeName == null) {
            throw new IllegalArgumentException();
        }

        for (XfType type: XfType.values()) {
            String workTypeName = type.xcodemlName();
            if (workTypeName != null) {
                if (xcodemlTypeName.compareToIgnoreCase(type.xcodemlName()) == 0) {
                    return type;
                }
            }
        }
        return DERIVED;
    }
}

