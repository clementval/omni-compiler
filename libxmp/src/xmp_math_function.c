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

#include "xmp_math_function.h"

int _XMP_modi_ll_i(long long value, int cycle) {
  int mod = value % cycle;
  if (mod < 0) {
    return (mod += cycle) % cycle;
  }
  else {
    return mod;
  }
}

int _XMP_modi_i_i(int value, int cycle) {
  int mod = value % cycle;
  if (mod < 0) {
    return (mod += cycle) % cycle;
  }
  else {
    return mod;
  }
}

int _XMP_ceili(int a, int b) {
  int div = a / b;

  if ((a < 0) || (b < 0)) {
    return div;
  } else {
    if ((a % b) == 0) {
      return div;
    } else {
      return div + 1;
    }
  }
}

int _XMP_floori(int a, int b) {
  int div = a / b;

  if ((a < 0) || (b < 0)) {
    if ((a % b) == 0) {
      return div;
    } else {
      return div - 1;
    }
  } else {
    return div;
  }
}

int _XMP_gcd(int a, int b) {
  int r = a % b;
  if (r == 0) {
    return b;
  } else {
    return _XMP_gcd(b, r);
  }
}

int _XMP_lcm(int a, int b) {
  return (a * b) / _XMP_gcd(a, b);
}
