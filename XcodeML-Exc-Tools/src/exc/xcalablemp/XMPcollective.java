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

public class XMPcollective {
  // defined in xmp_constant.h
  public final static int REDUCE_SUM		= 300;
  public final static int REDUCE_PROD		= 301;
  public final static int REDUCE_BAND		= 302;
  public final static int REDUCE_LAND		= 303;
  public final static int REDUCE_BOR		= 304;
  public final static int REDUCE_LOR		= 305;
  public final static int REDUCE_BXOR		= 306;
  public final static int REDUCE_LXOR		= 307;
  public final static int REDUCE_MAX		= 308;
  public final static int REDUCE_MIN		= 309;
  public final static int REDUCE_FIRSTMAX	= 310;
  public final static int REDUCE_FIRSTMIN	= 311;
  public final static int REDUCE_LASTMAX	= 312;
  public final static int REDUCE_LASTMIN	= 313;
  public final static int REDUCE_EQV            = 314;
  public final static int REDUCE_NEQV           = 315;
  public final static int REDUCE_MINUS          = 316;

  public final static int GMOVE_NORMAL	= 400;
  public final static int GMOVE_IN	= 401;
  public final static int GMOVE_OUT	= 402;
}
