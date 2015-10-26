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
 * ID=060
 */

package exc.object;
import static xcodeml.util.XmLog.fatal;

/**
 * information and methods about co-shape of Fortran coarray
 */
public class Coshape
{
  private final static int MAX_CORANK = 31;

  private Xobject[] codimensions;
  private int corank;

  /** constructor */
  public Coshape()
  {
    setCodimensions(new Xobject[0]);
  }
  public Coshape(Xobject[] codimensions)
  {
    setCodimensions(codimensions);
  }

  public int getCorank()
  {
    return corank;
  }

  public Xobject[] getCodimensions()
  {
    return codimensions;
  }

  public void setCodimensions(Xobject[] codimensions)
  {
    if (codimensions != null) {
      this.codimensions = codimensions;
      corank = codimensions.length;
    } else {   // non-coarray
      this.codimensions = new Xobject[0];
      corank = 0;
    }
  }

  public void removeCodimensions()
  {
    if (codimensions != null) {
      this.codimensions = new Xobject[0];
      corank = 0;
    }
  }

  public Xobject[] copyCodimensions()
  {
    Xobject[] codimensions1 = new Xobject[corank];
    // which is good?
    //    System.arraycopy(codimensions, 0, codimensions1, 0, corank);
    for (int i = 0; i < corank; i++)
      codimensions1[i] = codimensions[i].copy();
    return codimensions1;
  }

  public Coshape copy()
  {
    Xobject[] codim1 = copyCodimensions();
    return new Coshape(codim1);
  }
}

