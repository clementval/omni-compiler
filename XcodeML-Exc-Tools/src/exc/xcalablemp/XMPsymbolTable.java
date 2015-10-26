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

import java.util.HashMap;

public class XMPsymbolTable {
  private HashMap<String, XMPobject> _XMPobjectTable;
  private HashMap<String, XMPalignedArray> _XMPalignedArrayTable;
  private HashMap<String, XMPcoarray> _XMPcoarrayTable;

  public XMPsymbolTable() {
    _XMPobjectTable = new HashMap<String, XMPobject>();
    _XMPalignedArrayTable = new HashMap<String, XMPalignedArray>();
    _XMPcoarrayTable = new HashMap<String, XMPcoarray>();
  }

  public void putXMPobject(XMPobject o) {
    _XMPobjectTable.put(o.getName(), o);
  }

  public XMPobject getXMPobject(String name) {
    return _XMPobjectTable.get(name);
  }

  public XMPnodes getXMPnodes(String name) {
    XMPobject o = _XMPobjectTable.get(name);

    if (o == null) return null;
    else if (o.getKind() != XMPobject.NODES) return null;
    else return (XMPnodes)o;
  }

  public XMPtemplate getXMPtemplate(String name) {
    XMPobject o = _XMPobjectTable.get(name);

    if (o == null) return null;
    else if (o.getKind() != XMPobject.TEMPLATE) return null;
    else return (XMPtemplate)o;
  }

  public void putXMPalignedArray(XMPalignedArray array) {
    _XMPalignedArrayTable.put(array.getName(), array);
  }

  public XMPalignedArray getXMPalignedArray(String name) {
    return _XMPalignedArrayTable.get(name);
  }

  public void putXMPcoarray(XMPcoarray array) {
    _XMPcoarrayTable.put(array.getName(), array);
  }

  public XMPcoarray getXMPcoarray(String name) {
    return _XMPcoarrayTable.get(name);
  }
}
