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

package exc.xmpF;

import exc.object.*;
import exc.block.*;

/*
 * Base class of XMPnodes and XMPtemplate
 */
public class XMPobject {
  public final static int NODES		= 100;
  public final static int TEMPLATE	= 101;

  int			_kind;
  String		_name;
  int			_dim;
  Ident			_descId;

  public XMPobject(int kind){
    _kind = kind;
  }

  public XMPobject(int kind, String name, int dim, Ident descId) {
    _kind = kind;
    _name = name;
    _dim = dim;
    _descId = descId;
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

  public void buildConstructor(BlockList body, XMPenv def){
    // abstract method
    XMP.fatal("buildConstrutor");
  }

  public void buildDestructor(BlockList body, XMPenv def){
    // abstract method
    XMP.fatal("buildDestrutor");
  }  
}
