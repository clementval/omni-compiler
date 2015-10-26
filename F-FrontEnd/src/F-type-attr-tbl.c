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
/**
 * \file F-type-attr-tbl.c
 */

#include "F-front.h"

struct type_attr_check type_attr_checker[] = {
    {
        TYPE_ATTR_PARAMETER,
        (TYPE_ATTR_PARAMETER|TYPE_ATTR_PUBLIC|TYPE_ATTR_PRIVATE|TYPE_ATTR_SEQUENCE|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE),
        "parameter",
    },
    {
        TYPE_ATTR_ALLOCATABLE,
        (TYPE_ATTR_ALLOCATABLE|TYPE_ATTR_SAVE|TYPE_ATTR_TARGET|TYPE_ATTR_PUBLIC|TYPE_ATTR_PRIVATE|TYPE_ATTR_SEQUENCE|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE),
        "allocatable",
    },
    {
        TYPE_ATTR_EXTERNAL,
        (TYPE_ATTR_EXTERNAL|TYPE_ATTR_OPTIONAL|TYPE_ATTR_PUBLIC|TYPE_ATTR_PRIVATE|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE),
        "external",
    },
    {
        TYPE_ATTR_INTRINSIC,
        (TYPE_ATTR_INTRINSIC|TYPE_ATTR_PUBLIC|TYPE_ATTR_PRIVATE|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE),
        "intrinsic",
    },
    {
        TYPE_ATTR_OPTIONAL,
        (TYPE_ATTR_OPTIONAL|TYPE_ATTR_EXTERNAL|TYPE_ATTR_INTENT_IN|TYPE_ATTR_INTENT_OUT|
                                TYPE_ATTR_INTENT_INOUT|TYPE_ATTR_POINTER|TYPE_ATTR_TARGET|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE),
        "optional",
    },
    {
        TYPE_ATTR_POINTER,
        (TYPE_ATTR_OPTIONAL|TYPE_ATTR_POINTER|TYPE_ATTR_PUBLIC|TYPE_ATTR_PRIVATE|TYPE_ATTR_SEQUENCE|TYPE_ATTR_SAVE|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE|TYPE_ATTR_INTENT_IN|TYPE_ATTR_INTENT_OUT|TYPE_ATTR_INTENT_INOUT),
        "pointer",
    },
    {
        TYPE_ATTR_SAVE,
        (TYPE_ATTR_ALLOCATABLE|TYPE_ATTR_POINTER|TYPE_ATTR_PUBLIC|TYPE_ATTR_PRIVATE|
                                TYPE_ATTR_SAVE|TYPE_ATTR_TARGET|TYPE_ATTR_SEQUENCE|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE),
        "save",
    },
    {
        TYPE_ATTR_TARGET,
        (TYPE_ATTR_ALLOCATABLE|TYPE_ATTR_INTENT_IN|TYPE_ATTR_INTENT_OUT|TYPE_ATTR_INTENT_INOUT|
                TYPE_ATTR_OPTIONAL|TYPE_ATTR_PUBLIC|TYPE_ATTR_PRIVATE|TYPE_ATTR_SEQUENCE|TYPE_ATTR_SAVE|TYPE_ATTR_TARGET|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE),
        "target",
    },
    {
        TYPE_ATTR_PUBLIC,
        (TYPE_ATTR_ALLOCATABLE|TYPE_ATTR_EXTERNAL|TYPE_ATTR_INTRINSIC|TYPE_ATTR_PARAMETER|
                                TYPE_ATTR_POINTER|TYPE_ATTR_PUBLIC|TYPE_ATTR_INTERNAL_PRIVATE|TYPE_ATTR_SAVE|TYPE_ATTR_TARGET|TYPE_ATTR_SEQUENCE|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE),
        "public",
    },
    {
        TYPE_ATTR_PRIVATE,
        (TYPE_ATTR_ALLOCATABLE|TYPE_ATTR_EXTERNAL|TYPE_ATTR_INTRINSIC|TYPE_ATTR_PARAMETER|
                                TYPE_ATTR_POINTER|TYPE_ATTR_PRIVATE|TYPE_ATTR_INTERNAL_PRIVATE|TYPE_ATTR_SAVE|TYPE_ATTR_TARGET|TYPE_ATTR_SEQUENCE|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE),
        "private",
    },
    {
        TYPE_ATTR_INTENT_IN,
        (TYPE_ATTR_INTENT_IN|TYPE_ATTR_OPTIONAL|TYPE_ATTR_TARGET|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE|TYPE_ATTR_POINTER),
        "intent in",
    },
    {
        TYPE_ATTR_INTENT_OUT,
        (TYPE_ATTR_INTENT_OUT|TYPE_ATTR_OPTIONAL|TYPE_ATTR_TARGET|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE|TYPE_ATTR_POINTER),
        "intent out",
    },
    {
        TYPE_ATTR_INTENT_INOUT,
        (TYPE_ATTR_INTENT_INOUT|TYPE_ATTR_OPTIONAL|TYPE_ATTR_TARGET|TYPE_ATTR_RECURSIVE|TYPE_ATTR_PURE|TYPE_ATTR_POINTER),
        "intent out",
    },
    {  /* terminater, DO NOT remove */
        0,0,NULL
    }
};
