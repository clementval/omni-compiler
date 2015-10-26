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
package xcodeml.binding;

/**
 * Represents element which has lineno and file attribute.
 */
public interface IXbLineNo
{
    /**
     * Gets a line number of original statement/expression/declaration in source code.
     *
     * @return line number description.
     */
    public String getLineno();

    public void setLineno(String lineno);

    /**
     * Gets a raw line number of the original statement/expression/declaration in pre processed source code.
     *
     * @return line number description.
     */
    public String getRawlineno();

    public void setRawlineno(String rawlineno);

    /**
     * Gets file name of the original statement/expression/declaration described.
     *
     * @return file name
     */
    public String getFile();

    public void setFile(String file);
}
