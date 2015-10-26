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

import xcodeml.ILineNo;

public class LineNo implements ILineNo
{
    String fname;
    int ln;

    static LineNo current_lineno;

    public LineNo(String fname, int ln)
    {
        this.fname = fname.intern();
        this.ln = ln;
    }

    public int lineNo()
    {
        return ln;
    }

    public String fileName()
    {
        return fname;
    }

    @Override
    public String toString()
    {
        return (fname != null ? fname : "") + ":" + ln;
    }
    
    public static LineNo make(String fname, int ln)
    {
        if(current_lineno == null || current_lineno.ln != ln || !current_lineno.fname.equals(fname)) {
            if(fname == null) {
                if(current_lineno == null)
                    fname = "*";
                else
                    fname = current_lineno.fname;
            }
            current_lineno = new LineNo(fname, ln);
        }
        return current_lineno;
    }
}
