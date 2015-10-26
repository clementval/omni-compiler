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
package xcodeml;

public interface IXobject
{
    /** find() argument: find any symbol */
    public static int FINDKIND_ANY = 0;
    /** find() argument: find variable symbol */
    public static int FINDKIND_VAR = 1;
    /** find() argument: find common block symbol */
    public static int FINDKIND_COMMON = 2;
    /** find() argument: find tag, structure name symbol */
    public static int FINDKIND_TAGNAME = 3;

    /**
     * get line number.
     */
    public ILineNo getLineNo();

    /**
     * get parent IXobject.
     */
    public IXobject getParent();

    /**
     * set parent IXobject.
     */
    public void setParentRecursively(IXobject parent);

    /**
     * find symbol object.
     * 
     * @param name
     *      symbol name
     * @param kind
     *      FINDKIND_*
     */
    public IXobject find(String name, int kind);
}
