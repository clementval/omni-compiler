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
import java.util.*;

public class XMPtranslateGlobalPragma {
  private XMPglobalDecl		_globalDecl;

  public XMPtranslateGlobalPragma(XMPglobalDecl globalDecl) {
    _globalDecl = globalDecl;
  }

  public void translate(Xobject x) {
    try {
      translatePragma(x);
    } catch (XMPexception e) {
      XMP.error(x.getLineNo(), e.getMessage());
    }
  }

  public void translatePragma(Xobject x) throws XMPexception {
    String pragmaName = x.getArg(0).getString();

    switch (XMPpragma.valueOf(pragmaName)) {
      case NODES:
        translateNodes(x);
        break;
      case TEMPLATE:
        translateTemplate(x);
        break;
      case DISTRIBUTE:
        translateDistribute(x);
        break;
      case ALIGN:
        translateAlign(x);
        break;
      case SHADOW:
        translateShadow(x);
        break;
      case COARRAY:
        translateCoarray(x);
        break;
      case LOCAL_ALIAS:
        translateLocalAlias(x);
        break;
      default:
        throw new XMPexception("'" + pragmaName.toLowerCase() + "' directive is not supported yet");
    }
  }

  private void translateNodes(Xobject nodesPragma) throws XMPexception {
    XobjList nodesDecl = (XobjList)nodesPragma.getArg(1);
    XobjList nodesNameList = (XobjList)nodesDecl.getArg(0);
    XobjList nodesDeclCopy = (XobjList)nodesDecl.copy();

    Iterator<Xobject> iter = nodesNameList.iterator();
    while (iter.hasNext()) {
      Xobject x = iter.next();
      nodesDeclCopy.setArg(0, x);
      XMPnodes.translateNodes(nodesDeclCopy, _globalDecl, false, null);
    }
  }

  private void translateTemplate(Xobject templatePragma) throws XMPexception {
    XobjList templateDecl = (XobjList)templatePragma.getArg(1);
    XobjList templateNameList = (XobjList)templateDecl.getArg(0);
    XobjList templateDeclCopy = (XobjList)templateDecl.copy();

    Iterator<Xobject> iter = templateNameList.iterator();
    while (iter.hasNext()) {
      Xobject x = iter.next();
      templateDeclCopy.setArg(0, x);
      XMPtemplate.translateTemplate(templateDeclCopy, _globalDecl, false, null);
    }
  }

  private void translateDistribute(Xobject distributePragma) throws XMPexception {
    XobjList distributeDecl = (XobjList)distributePragma.getArg(1);
    XobjList distributeNameList = (XobjList)distributeDecl.getArg(0);
    XobjList distributeDeclCopy = (XobjList)distributeDecl.copy();

    Iterator<Xobject> iter = distributeNameList.iterator();
    while (iter.hasNext()) {
      Xobject x = iter.next();
      distributeDeclCopy.setArg(0, x);
      XMPtemplate.translateDistribute(distributeDeclCopy, _globalDecl, false, null);
    }
  }

  private void translateAlign(Xobject alignPragma) throws XMPexception {
    XobjList alignDecl = (XobjList)alignPragma.getArg(1);
    XobjList alignNameList = (XobjList)alignDecl.getArg(0);
    XobjList alignDeclCopy = (XobjList)alignDecl.copy();

    Iterator<Xobject> iter = alignNameList.iterator();
    while (iter.hasNext()) {
      Xobject x = iter.next();
      alignDeclCopy.setArg(0, x);
      XMPalignedArray.translateAlign(alignDeclCopy, _globalDecl, false, null);
    }
  }

  private void translateLocalAlias(Xobject localAliasPragma) throws XMPexception {
    XMPalignedArray.translateLocalAlias((XobjList)localAliasPragma.getArg(1), _globalDecl, false, null);
  }

  private void translateShadow(Xobject shadowPragma) throws XMPexception {
    XobjList shadowDecl = (XobjList)shadowPragma.getArg(1);
    XobjList shadowNameList = (XobjList)shadowDecl.getArg(0);
    XobjList shadowDeclCopy = (XobjList)shadowDecl.copy();

    Iterator<Xobject> iter = shadowNameList.iterator();
    while (iter.hasNext()) {
      Xobject x = iter.next();
      shadowDeclCopy.setArg(0, x);
      XMPshadow.translateShadow(shadowDeclCopy, _globalDecl, false, null);
    }
  }

  private void translateCoarray(Xobject coarrayPragma) throws XMPexception {
    XobjList coarrayDecl = (XobjList)coarrayPragma.getArg(1);
    XobjList coarrayNameList = (XobjList)coarrayDecl.getArg(0);
    XobjList coarrayDeclCopy = (XobjList)coarrayDecl.copy();

    Iterator<Xobject> iter = coarrayNameList.iterator();
    while (iter.hasNext()) {
      Xobject x = iter.next();

      coarrayDeclCopy.setArg(0, x);
      XMPcoarray.translateCoarray(coarrayDeclCopy, _globalDecl, false, null);
    }
  }
}
