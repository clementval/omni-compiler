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
import java.util.*;

/*
 * Madiator for each coarray
 */
public class XMPcoarray {

  // name of library
  final static String XMPF_LCOBOUND = "xmpf_lcobound";
  final static String XMPF_UCOBOUND = "xmpf_ucobound";
  final static String XMPF_COSIZE = "xmpf_cosize";
  final static String GET_IMAGE_INDEX_NAME = "xmpf_coarray_get_image_index";
  public final static String SET_COSHAPE_NAME = "xmpf_coarray_set_coshape";
  public final static String SET_VARNAME_NAME = "xmpf_coarray_set_varname";

  // original attributes
  private Ident ident;
  private String name;
  private FindexRange indexRange = null;
  private FindexRange coindexRange = null;
  //private Xtype originalType;
  private Boolean isAllocatable;
  private Boolean isPointer;

  // corresponding cray pointer and descriptor
  private String crayPtrName = null;
  private Ident crayPtrId = null;
  private String descPtrName = null;
  private Ident descPtrId = null;

  // context
  protected XMPenv env;
  protected XobjectDef def;
  protected FunctionBlock fblock;

  // for debug
  private Boolean DEBUG = false;        // switch me on debugger

  //------------------------------
  //  CONSTRUCTOR
  //------------------------------
  public XMPcoarray(Ident ident, FuncDefBlock funcDef, XMPenv env) {
    this(ident, funcDef.getDef(), funcDef.getBlock(), env);
  }
  public XMPcoarray(Ident ident, XobjectDef def, FunctionBlock fblock, XMPenv env) {
    this.ident = ident;
    this.env = env;
    this.def = def;
    this.fblock = fblock;
    name = ident.getName();
    //originalType = ident.Type().copy();
    isAllocatable = ident.Type().isFallocatable();
    isPointer = ident.Type().isFpointer();
    if (DEBUG) System.out.println("[XMPcoarray] new coarray = "+this);
  }

  //------------------------------
  //  actions
  //------------------------------

  // declare cray-pointer variable correspoinding to this.
  //
  public void genDecl_crayPointer(String crayPtrPrefix) {

    BlockList blist = fblock.getBody();
    crayPtrName = crayPtrPrefix + "_" + name;

    // generate declaration of crayPtrId
    Xtype crayPtrType = Xtype.Farray(BasicType.Fint8Type);
    crayPtrType.setIsFcrayPointer(true);
    crayPtrId = blist.declLocalIdent(crayPtrName,
                                     crayPtrType,
                                     StorageClass.FLOCAL,
                                     Xcons.FvarRef(ident));  // ident.Ref() if C
  }


  // declare variable of descriptor pointer corresponding to this.
  //
  public void genDecl_descPointer(String descPtrPrefix) {

    BlockList blist = fblock.getBody();
    descPtrName = descPtrPrefix + "_" + name;

    // generate declaration of descPtrId
    descPtrId = blist.declLocalIdent(descPtrName,
                                   BasicType.Fint8Type,
                                   StorageClass.FLOCAL,
                                   null);
  }



  /*
   *  m. "CALL set_coshape(descPtr, corank, clb1, clb2, ..., clbr)"
   *     without static coshape
   */
  public Xobject makeStmt_setCoshape() {
    int corank = getCorank();

    Xobject args = Xcons.List(getDescPointerId(),
                              Xcons.IntConstant(corank));
    for (int i = 0; i < corank - 1; i++) {
      args.add(getLcobound(i));
      args.add(getUcobound(i));
    }
    args.add(getLcobound(corank - 1));

    Ident subr = env.findVarIdent(SET_COSHAPE_NAME, null);
    if (subr == null) {
      subr = env.declExternIdent(SET_COSHAPE_NAME,
                                 BasicType.FexternalSubroutineType);
    }
    Xobject subrCall = subr.callSubroutine(args);
    return subrCall;
  }


  /*
   *  m. "CALL set_coshape(descPtr, corank, clb1, clb2, ..., clbr)"
   *     with static coshape
   */
  public Xobject makeStmt_setCoshape(XobjList coshape) {
    int corank = getCorank();
    if (corank != coshape.Nargs()) {
      XMP.error("number of codimensions not matched with the declaration:"
                + corank + " and " + coshape.Nargs());
      return null;
    }

    Xobject args = Xcons.List(getDescPointerId(),
                              Xcons.IntConstant(corank));
    for (int i = 0; i < corank - 1; i++) {
      args.add(_getLboundInIndexRange(coshape.getArg(i)));
      args.add(_getUboundInIndexRange(coshape.getArg(i)));
    }
    args.add(_getLboundInIndexRange(coshape.getArg(corank - 1)));

    Ident subr = env.findVarIdent(SET_COSHAPE_NAME, null);
    if (subr == null) {
      subr = env.declExternIdent(SET_COSHAPE_NAME,
                                 BasicType.FexternalSubroutineType);
    }
    Xobject subrCall = subr.callSubroutine(args);
    return subrCall;
  }


  private Xobject _getLboundInIndexRange(Xobject dimension) {
    Xobject lbound;

    if (dimension == null)
      lbound = null;
    else {
      switch (dimension.Opcode()) {
      case F_INDEX_RANGE:
        lbound = dimension.getArg(0);
        break;
      case F_ARRAY_INDEX:
        lbound = null;
        break;
      default:
        lbound = null;
        break;
      }
    }

    if (lbound == null)
      return Xcons.IntConstant(1);

    return lbound.cfold(fblock);
  }


  private Xobject _getUboundInIndexRange(Xobject dimension) {
    Xobject ubound;

    if (dimension == null)
      ubound = null;
    else {
      switch (dimension.Opcode()) {
      case F_INDEX_RANGE:
        ubound = dimension.getArg(1);
        break;
      case F_ARRAY_INDEX:
        ubound = dimension.getArg(0);
        break;
      default:
        ubound = dimension;
      }
    }

    if (ubound == null)
      XMP.error("illegal upper bound specified in ALLOCATE statement");

    return ubound.cfold(fblock);
  }


  /*
   *  n. "CALL set_varname(descPtr, name, namelen)"
   */
  public Xobject makeStmt_setVarName() {
    String varName = getName();
    Xobject varNameObj = 
      Xcons.FcharacterConstant(Xtype.FcharacterType, varName, null);
    Xobject varNameLen = 
      Xcons.IntConstant(varName.length());
    Xobject args = Xcons.List(getDescPointerId(),
                              varNameObj, varNameLen);

    Ident subr = env.findVarIdent(SET_VARNAME_NAME, null);
    if (subr == null) {
      subr = env.declExternIdent(SET_VARNAME_NAME,
                                 BasicType.FexternalSubroutineType);
    }
    Xobject subrCall = subr.callSubroutine(args);
    return subrCall;
  }



  /*** not used now ***/
  public Xobject genMallocCallStmt(String mallocLibName) {
    BlockList blist = fblock.getBody();
    Ident mallocId = blist.declLocalIdent(mallocLibName,
                                          BasicType.FsubroutineType);
    Xobject varRef = Xcons.FvarRef(getCrayPointerId());
    Xobject elem = getElementLengthExpr(); 
    Xobject count = getTotalArraySizeExpr();
    Xobject args = Xcons.List(varRef, count, elem);
    Xobject stmt = Xcons.functionCall(mallocId, args);
    return stmt;
  }


  //------------------------------
  //  self error check
  //------------------------------
  public void errorCheck() {

    if (ident.isCoarray()) {  // if it is not converted yet
      if (isPointer()) {
        XMP.error("Coarray variable cannot be a pointer: " + name);
      }
      if (isDummyArg()) {
        if (!isScalar() && !isExplicitShape() && !isAllocatable())
          XMP.error("Coarray dummy argument must be explicit-shaped or allocatable: "
                    + name);
      }
    }

  }


  //------------------------------
  //  IndexRange (to be abolished)
  //------------------------------

  private void _setIndexRange() {
    Xobject[] shape = getShape();
    indexRange = new FindexRange(shape, fblock, env);
  }

  private void _setIndexRange(Block block, XMPenv env) {
    Xobject[] shape = getShape();
    indexRange = new FindexRange(shape, block, env);
  }

  public FindexRange getIndexRange() {
    if (indexRange == null)
      _setIndexRange();
    return indexRange;
  }


  //------------------------------
  //  CoindexRange
  //------------------------------

  private void _setCoindexRange() {
    Xobject[] shape = getCoshape();
    coindexRange = new FindexRange(shape, fblock, env);
  }

  private void _setCoindexRange(Block block, XMPenv env) {
    Xobject[] shape = getCoshape();
    coindexRange = new FindexRange(shape, block, env);
  }

  public FindexRange getCoindexRange() {
    if (coindexRange == null)
      _setCoindexRange();
    return coindexRange;
  }


  //------------------------------
  //  evaluate index
  //------------------------------
  public int getElementLength() {
    Xobject elem = getElementLengthExpr(); 
    if (!elem.isIntConstant()) {
      XMP.error("current restriction: " +
                "could not numerically evaluate the element length of: "+name);
      return 0;
    }
    return elem.getInt();
  }

  public Xobject getElementLengthExpr() {
    return getElementLengthExpr(fblock);
  }
  public Xobject getElementLengthExpr(Block block) {
    Xobject elem = ident.Type().getElementLengthExpr(block);    // see BasicType.java
    if (elem == null)
      XMP.error("current restriction: " + 
                "could not find the element length of: "+name);
    return elem;
  }

  public int getTotalArraySize() {
    Xobject size = getTotalArraySizeExpr();
    if (!size.isIntConstant()) {
      XMP.error("current restriction: " +
                "could not numerically evaluate the total size of: "+name);
      return 0;
    }
    return size.getInt();
  }

  public Xobject getTotalArraySizeExpr() {
    Xobject size = getIndexRange().getTotalArraySizeExpr();
    if (size == null)
      XMP.error("current restriction: " +
                "could not find the total size of: "+name);
    return size;
  }


  //------------------------------
  //  inquire in Fortran terminology:
  //   rank, shape, lower/upper bound and size
  //------------------------------

  public int getRank() {
    return ident.Type().getNumDimensions();
  }

  public Xobject[] getShape() {
    if (getRank() == 0)
      return new Xobject[0];

    FarrayType ftype = (FarrayType)ident.Type();
    return ftype.getFarraySizeExpr();
  }


  public Xobject getLboundStatic(int i) {
    FarrayType ftype = (FarrayType)ident.Type();
    return ftype.getLbound(i, fblock);
  }

  public Xobject getUboundStatic(int i) {
    FarrayType ftype = (FarrayType)ident.Type();
    return ftype.getUbound(i, fblock);
  }

  public Xobject getLbound(int i) {
    Xobject lbound = getLboundStatic(i);
    if (lbound == null) {
      // generate intrinsic function call "lbound(a,dim)"
      Xobject arg1 = Xcons.Symbol(Xcode.VAR, name);
      Xobject arg2 = Xcons.IntConstant(i + 1);
      Ident lboundId = declIntIntrinsicIdent("lbound");
      lbound = lboundId.Call(Xcons.List(arg1, arg2));
    }
    return lbound;
  }

  public Xobject getUbound(int i) {
    Xobject ubound = getUboundStatic(i);
    if (ubound == null) {
      // generate intrinsic function call "ubound(a,dim)"
      Xobject arg1 = Xcons.Symbol(Xcode.VAR, name);
      Xobject arg2 = Xcons.IntConstant(i + 1);
      Ident uboundId = declIntIntrinsicIdent("ubound");
      ubound = uboundId.Call(Xcons.List(arg1, arg2));
    }
    return ubound;
  }


  public Xobject getSizeFromLbUb(Xobject lb, Xobject ub) {
    return getIndexRange().getSizeFromLbUb(lb, ub);
  }

  public Xobject getSizeFromIndexRange(Xobject range) {
    Xobject i1 = range.getArg(0);
    Xobject i2 = range.getArg(1);
    Xobject i3 = range.getArg(2);
    return getIndexRange().getSizeFromTriplet(i1, i2, i3);
  }


  //public Xobject getSizeFromTriplet(Xobject i1, Xobject i2, Xobject i3)
  //{
  //  return getIndexRange().getSizeFromTriplet(i1, i2, i3);
  //}

  public Xobject getSizeFromTriplet(int i, Xobject i1, Xobject i2, Xobject i3) {
    return getIndexRange().getSizeFromTriplet(i, i1, i2, i3);
  }


  //------------------------------
  //  evaluation in Fortran terminology:
  //   corank, coshape, lower/upper cobound and cosize
  //------------------------------

  public int getCorank() {
    return ident.Type().getCorank();
  }
 
  public Xobject[] getCoshape() {
    return ident.Type().getCodimensions();
  }

  public Xobject getLcoboundStatic(int i) {
    FindexRange indexRange = getCoindexRange();
    return (indexRange == null) ? null : indexRange.getLbound(i);
  }

  public Xobject getUcoboundStatic(int i) {
    FindexRange indexRange = getCoindexRange();
    return (indexRange == null) ? null : indexRange.getUbound(i);
  }

  public Xobject getCosizeStatic(int i) {
    FindexRange indexRange = getCoindexRange();
    return (indexRange == null) ? null : indexRange.getExtent(i);
  }

  public Xobject getLcobound(int i) {
    Xobject lcobound = getLcoboundStatic(i);
    if (lcobound == null) {
      // generate intrinsic function call "xmpf_lcobound(serno, dim)"
      Xobject arg1 = descPtrId;
      Xobject arg2 = Xcons.IntConstant(i + 1);
      Ident lcoboundId = getEnv().findVarIdent(XMPF_LCOBOUND, null);
      if (lcoboundId == null)
        lcoboundId = getEnv().declExternIdent(XMPF_LCOBOUND, Xtype.FintFunctionType);
      lcobound = lcoboundId.Call(Xcons.List(arg1, arg2));
    }
    return lcobound;
  }

  public Xobject getUcobound(int i) {
    Xobject ucobound = getUcoboundStatic(i);
    if (ucobound == null) {
      // generate intrinsic function call "xmpf_ucobound(serno, dim)"
      Xobject arg1 = descPtrId;
      Xobject arg2 = Xcons.IntConstant(i + 1);
      Ident ucoboundId = getEnv().findVarIdent(XMPF_UCOBOUND, null);
      if (ucoboundId == null)
        ucoboundId = getEnv().declExternIdent(XMPF_UCOBOUND, Xtype.FintFunctionType);
      ucobound = ucoboundId.Call(Xcons.List(arg1, arg2));
    }
    return ucobound;
  }

  public Xobject getCosize(int i) {
    Xobject cosize = getCosizeStatic(i);
    if (cosize == null) {
      // generate intrinsic function call "xmpf_cosize(serno, dim)"
      Xobject arg1 = descPtrId;
      Xobject arg2 = Xcons.IntConstant(i + 1);
      Ident cosizeId = getEnv().findVarIdent(XMPF_COSIZE, null);
      if (cosizeId == null)
        cosizeId = getEnv().declExternIdent(XMPF_COSIZE, Xtype.FintFunctionType);
      cosize = cosizeId.Call(Xcons.List(arg1, arg2));
    }
    return cosize;
  }


  //------------------------------
  //  evaluation in Fortran terminology:
  //   image index
  //------------------------------

  public Xobject getImageIndex(Xobject baseAddr, Xobject cosubscripts) {
    String fname = GET_IMAGE_INDEX_NAME;
    Ident fnameId = getEnv().findVarIdent(fname, null);
    if (fnameId == null)
      fnameId = getEnv().declExternIdent(fname, Xtype.FintFunctionType);

    XobjList args = Xcons.List(getDescPointerIdExpr(baseAddr), 
                               Xcons.IntConstant(getCorank()));
    for (Xobject cosubs: (XobjList)cosubscripts) {
      args.add(cosubs);
    }

    return fnameId.Call(args);
  }



  //------------------------------
  //  tool
  //------------------------------
  private Ident declIntIntrinsicIdent(String name) { 
    FunctionType ftype = new FunctionType(Xtype.FintType, Xtype.TQ_FINTRINSIC);
    Ident ident = getEnv().declIntrinsicIdent(name, ftype);
    return ident;
  }


  //------------------------------
  //  get/set Xtype object
  //------------------------------
  public Boolean isScalar() {
    return (ident.Type().getNumDimensions() == 0);
  }

  public Boolean isAllocatable() {
    return isAllocatable;
  }

  public void setAllocatable() {
    ident.Type().setIsFallocatable(true);
  }

  public void resetAllocatable() {
    for (Xtype type = ident.Type(); type != null; ) {
      type.setIsFallocatable(false);
      if (type.copied != null)
        type = type.copied;
      else if (type.isBasic())
        break;
      else
        type = type.getRef();
    }
  }

  public Boolean isPointer() {
    return isPointer;
  }

  public void setPointer() {
    ident.Type().setIsFpointer(true);
  }

  public void resetPointer() {
    for (Xtype type = ident.Type(); type != null; ) {
      type.setIsFpointer(false);
      if (type.copied != null)
        type = type.copied;
      else if (type.isBasic())
        break;
      else
        type = type.getRef();
    }
  }

  public Boolean isDummyArg() {
    if (ident.getStorageClass() == StorageClass.FPARAM)
      return true;
    return false;
  }

  public Boolean isAssumedSize() {
    return ident.Type().isFassumedSize();
  }

  public Boolean isAssumedShape() {
    return ident.Type().isFassumedShape();
  }

  public Boolean isExplicitShape() {
    return (!isAssumedSize() && !isAssumedShape() &&
            !isAllocatable() && !isPointer());
  }

  public Boolean isUseAssociated() {
    return ident.getFdeclaredModule() != null;
  }



  public Ident getIdent() {
    return ident;
  }

  public XMPenv getEnv() {
    return env;
  }

  public String getCrayPointerName() {
    return crayPtrName;
  }

  public Ident getCrayPointerId() {
    return crayPtrId;
  }

  public String getDescPointerName() {
    return descPtrName;
  }

  public Ident getDescPointerId() {
    return descPtrId;
  }

  public Xobject getDescPointerIdExpr(Xobject baseAddr) {
    if (descPtrId != null)
      return descPtrId;

    Ident funcIdent =
      getEnv().declExternIdent("xmpf_get_descr_id", Xtype.FintFunctionType);
    Xobject descId = funcIdent.Call(Xcons.List(baseAddr));
    return descId;
  }

  public Xobject[] getCodimensions() {
    Xobject[] codims = ident.Type().getCodimensions();
    return codims;
  }

  public void setCodimensions(Xobject[] codimensions) {
    ident.Type().setCodimensions(codimensions);
  }

  public void removeCodimensions() {
    ident.Type().removeCodimensions();
  }

  public void hideCodimensions() {
    ident.Type().setIsCoarray(false);
  }

  public String getName() {
    return ident.getName();
  }

  public Xtype getType() {
    return ident.Type();
  }

  //public Xtype getOriginalType() {
  //return originalType;
  //}

  public String toString() {
    return toString(ident);
  }
  public String toString(Xobject obj) {
    return "Xobject(" + obj.getName()
      + ",rank=" + obj.Type().getNumDimensions()
      + ",corank=" + obj.Type().getCorank()
      + ")";
  }
  public String toString(Xtype type) {
    return "Xtype(rank=" + type.getNumDimensions()
      + ",corank=" + type.getCorank()
      + ")";
  }



  //------------------------------
  //  low-level handling
  //------------------------------
  public Ident unlinkIdent() {
    return unlinkIdent(def);
  }
  public Ident unlinkIdent(XobjectDef def) {
    return unlinkIdent((XobjList)def.getDef());
  }
  public Ident unlinkIdent(XobjList def) {
    XobjArgs args0 = def.getIdentList().getArgs();
    XobjArgs lastArgs = null;
    XobjArgs thisArgs = null;
    for (XobjArgs args = args0; args != null; args = args.nextArgs()) {
      Xobject arg = args.getArg();
      Ident id = (Ident)arg;
      if (id == ident) {
        thisArgs = args;
        break;
      }
      if (id.getName().equals(name)) {
        XMP.fatal("unexpected matching of ident names: " + name);
        thisArgs = args;
        break;
      }
      lastArgs = args;
    }

    if (thisArgs == null)   // not found
      return null;

    // unlink and reconnect
    if (lastArgs == null)
      def.getIdentList().setArgs(thisArgs.nextArgs());
    else
      lastArgs.setNext(thisArgs.nextArgs());

    thisArgs.setNext(null);

    return (Ident)thisArgs.getArg();
  }


  //------------------------------------------------------------
  //  Fortran Type and Kind
  //   ******** under construction *********
  //------------------------------------------------------------

  /* TEMPORARY VERSION
   *   getFkind().getKind() is useful, which is integer as Xtype.Fxxx
   */
  public Xtype getFtype() {
    Xtype ftype = ident.Type();
    if (ftype.getKind() == Xtype.F_ARRAY)
      ftype = ftype.getRef();
    return ftype;
  }

  /* TEMPORARY VERSION
   *   getFkind().getInt() is useful.
   */
  public Xobject getFkind() {
    return getFtype().getFkind();
  }

  /*
   * return a name of Fortran intrinsic function
   */
  private String getTypeIntrinsicName() {
    return getTypeIntrinsicName(getType());
  }

  private String getTypeIntrinsicName(Xtype xtype) {
    String name = null;

    switch (xtype.getKind()) {
    case Xtype.F_ARRAY:
      name = _getTypeIntrinName_1(xtype.getRef());
      break;
    case Xtype.BASIC:
      name = _getTypeIntrinName_1(xtype);
      break;
    case Xtype.STRUCT:
      //XMP.error("internal error: STRUCT unsupported in _getTypeSuffix()");
    default:
      //XMP.error("internal error: unexpected kind in _getTypeSuffix(): xtype.getKind()");
      break;
    }

    return name;
  }

  /// see also BasicType.getElementLength
  private String _getTypeIntrinName_1(Xtype xtype) {
    String key = null;
    switch(xtype.getBasicType()) {
    case BasicType.BOOL:
      key = "l";
      break;
    case BasicType.SHORT:
    case BasicType.UNSIGNED_SHORT:
    case BasicType.INT:
    case BasicType.UNSIGNED_INT:
    case BasicType.LONG:
    case BasicType.UNSIGNED_LONG:
    case BasicType.LONGLONG:
    case BasicType.UNSIGNED_LONGLONG:
      key = "int";
      break;
    case BasicType.FLOAT:
    case BasicType.DOUBLE:
    case BasicType.LONG_DOUBLE:
      key = "real";
      break;
    case BasicType.FLOAT_COMPLEX:
    case BasicType.DOUBLE_COMPLEX:
    case BasicType.LONG_DOUBLE_COMPLEX:
      key = "cmplx";
      break;
    case BasicType.CHAR:
    case BasicType.UNSIGNED_CHAR:
    case BasicType.F_CHARACTER:
      key = "c";
      break;

    default:
      XMP.error("found unsupported type of coarray");
      break;
    }

    return key;
  }

}

