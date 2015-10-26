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
import java.util.Iterator; 

public class XMPrealloc implements XobjectDefVisitor {
  private XMPglobalDecl _globalDecl;

  public XMPrealloc(XMPglobalDecl globalDecl) {
    _globalDecl = globalDecl;
  }

  public void doDef(XobjectDef def) {
    try {
      alignArrayRealloc(def);
      originalCoarrayDelete(def);
    } catch (XMPexception e) {
      XMP.error(def.getLineNo(), e.getMessage());
    }
  }

  private void originalCoarrayDelete(XobjectDef def) throws XMPexception {
    if (def.isVarDecl()) {
      String varName = def.getName();
      XMPcoarray coarray = _globalDecl.getXMPcoarray(varName);

      if (coarray != null){
	def.setDef(Xcons.List(Xcode.TEXT,
			      Xcons.String("/* array '" + varName + "' is removed by XcalableMP coarray directive */")));
      }
    }
  }

  private void alignArrayRealloc(XobjectDef def) throws XMPexception {
    if (def.isVarDecl()) {
      String varName = def.getName();
      XMPalignedArray alignedArray = _globalDecl.getXMPalignedArray(varName);
      if (alignedArray != null && !alignedArray.isPointer()) {
        if (alignedArray.realloc()) {
          XobjList allocFuncArgs = Xcons.List(alignedArray.getAddrIdVoidAddr(), alignedArray.getDescId().Ref());
          for (int i = alignedArray.getDim() - 1; i >= 0; i--) {
            allocFuncArgs.add(Xcons.Cast(Xtype.Pointer(Xtype.unsignedlonglongType),
                                         alignedArray.getAccIdAt(i).getAddr()));
          }

          if (alignedArray.getAddrId().getStorageClass() == StorageClass.EXTERN) {
            _globalDecl.addGlobalInitFuncCall("_XMP_alloc_array_EXTERN", allocFuncArgs);
          }
          else {
            _globalDecl.addGlobalInitFuncCall("_XMP_alloc_array", allocFuncArgs);
          }

	  def.setDef(Xcons.List(Xcode.TEXT,
				Xcons.String("/* array '" + varName + "' is removed by XcalableMP align directive */")));
        } else {
          XobjList allocFuncArgs = Xcons.List(alignedArray.getAddrIdVoidAddr(),
                                              alignedArray.getArrayId().Ref(),
                                              alignedArray.getDescId().Ref());
          for (int i = alignedArray.getDim() - 1; i >= 0; i--) {
            allocFuncArgs.add(Xcons.Cast(Xtype.Pointer(Xtype.unsignedlonglongType),
                                         alignedArray.getAccIdAt(i).getAddr()));
          }

          _globalDecl.addGlobalInitFuncCall("_XMP_init_array_addr", allocFuncArgs);
        }
      }
    }
  }
}
