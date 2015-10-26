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

import java.util.HashMap;
import java.util.Vector;

public class XMPsymbolTable {
  private HashMap<String, XMPobject> objectTable;
  private HashMap<String, XMParray> arrayTable;
  private HashMap<String, XMPcoarray> coarrayTable;

  private Vector<XMPobject> objects;
  private Vector<XMParray> arrays;
  private Vector<XMPcoarray> coarrays;
  
  private Vector<String> used_modules;

  public XMPsymbolTable() {
    objectTable = new HashMap<String, XMPobject>();
    arrayTable = new HashMap<String, XMParray>();
    coarrayTable = new HashMap<String, XMPcoarray>();

    objects = new Vector<XMPobject>();
    arrays = new Vector<XMParray>();
    coarrays = new Vector<XMPcoarray>();

    used_modules = new Vector<String>();
  }

  /* module */
  public void addUseModule(String module_name){
    used_modules.add(module_name);
  }

  public Vector<String> getUsedModules(){
    return used_modules;
  }

  /*
   * objects (nodes and templates)
   */
  public void putXMPobject(XMPobject o) {
    objectTable.put(o.getName(), o);
    objects.add(o);
  }

  public XMPobject getXMPobject(String name) {
    return objectTable.get(name);
  }

  public Vector<XMPobject> getXMPobjects(){
    return objects;
  }

  /*
   * array
   */
  public void putXMParray(XMParray array) {
    arrayTable.put(array.getName(), array);
    arrays.add(array);
  }

  public XMParray getXMParray(String name) {
    return arrayTable.get(name);
  }

  public Vector<XMParray> getXMParrays(){
    return arrays;
  }


  // for debug
  public void dump(String msg){
    System.out.println("dump XMP Symbol Table: --- "+msg);
    for(XMPobject o: objects) System.out.println("o="+o);
    for(XMParray a: arrays) System.out.println("a="+a);
    System.out.println("dump end: ---");
  }
}
