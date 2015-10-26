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

package exc.xcalablemp;

import exc.object.*;
import java.util.Vector;

public class XMPobject {
  public final static int NODES		= 100;
  public final static int TEMPLATE	= 101;

  private int			_kind;
  private String		_name;
  private int			_dim;
  private Ident			_descId;
  private Vector<Xobject>	_lowerVector;
  private Vector<Xobject>	_upperVector;

  public XMPobject(int kind, String name, int dim, Ident descId) {
    _kind = kind;
    _name = name;
    _dim = dim;
    _descId = descId;
    _lowerVector = new Vector<Xobject>();
    _upperVector = new Vector<Xobject>();
  }

  public int getKind() {
    return _kind;
  }

  public String getName() {
    return _name;
  }

  public int getDim() {
    return _dim;
  }

  public Ident getDescId() {
    return _descId;
  }

  public void addLower(Xobject lower) {
    _lowerVector.add(lower);
  }

  public Xobject getLowerAt(int index) {
    return _lowerVector.get(index);
  }

  public void addUpper(Xobject upper) {
    _upperVector.add(upper);
  }

  public Xobject getUpperAt(int index) {
    return _upperVector.get(index);
  }

  public boolean checkInheritExec() {
    throw new UnsupportedOperationException();
  }
}
