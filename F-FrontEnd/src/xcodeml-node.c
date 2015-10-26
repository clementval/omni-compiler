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
#include "xcodeml.h"

static XcodeMLList *
consList(XcodeMLNode *x, XcodeMLList *l) {
    XcodeMLList *ret = XMALLOC(XcodeMLList *, sizeof(XcodeMLList));
    XCODEML_LIST_NODE(ret) = x;
    XCODEML_LIST_NEXT(ret) = l;
    return ret;
}


XcodeMLNode *
xcodeml_CreateGenericNode(XcodeMLNodeTypeT t, void *v) {
    XcodeMLNode *ret = XMALLOC(XcodeMLNode *, sizeof(*ret));
    XCODEML_TYPE(ret) = t;
    XCODEML_GEN(ret) = v;
    XCODEML_IS_OUTPUTED(ret) = false;
    return ret;
}


XcodeMLNode *
xcodeml_CreateValueNode(char *s) {
    XcodeMLNode *ret = xcodeml_CreateGenericNode(XcodeML_Value, NULL);
    XCODEML_VALUE(ret) = strdup(s);
    return ret;
}


XcodeMLNode *
xcodeml_CreateList0(XcodeMLNodeTypeT t) {
    return xcodeml_CreateGenericNode(t, NULL);
}


XcodeMLNode *
xcodeml_CreateList1(XcodeMLNodeTypeT t, XcodeMLNode *x1) {
    return xcodeml_CreateGenericNode(t,
                                     (void *)consList(x1, NULL));
}


XcodeMLNode *
xcodeml_CreateList2(XcodeMLNodeTypeT t,
                    XcodeMLNode *x1, XcodeMLNode *x2) {
    return xcodeml_CreateGenericNode(t,
                                     (void *)consList(x1,
                                                      consList(x2, NULL)));
}


XcodeMLNode *
xcodeml_CreateList3(XcodeMLNodeTypeT t,
                    XcodeMLNode *x1, XcodeMLNode *x2, XcodeMLNode *x3) {
    return xcodeml_CreateGenericNode(
        t,
        (void *)consList(x1,
                         consList(x2,
                                  consList(x3, NULL))));
}


XcodeMLNode *
xcodeml_AppendNode(XcodeMLNode *xlPtr, XcodeMLNode *x) {
    if (xlPtr != NULL) {
        if (XCODEML_LIST(xlPtr) == NULL) {
            XCODEML_LIST(xlPtr) = consList(x, NULL);
        } else {
            XcodeMLList *lPtr;
            for (lPtr = XCODEML_LIST(xlPtr);
                 XCODEML_LIST_NEXT(lPtr) != NULL;
                 lPtr = XCODEML_LIST_NEXT(lPtr)) {
                ;
            }
            XCODEML_LIST_NEXT(lPtr) = consList(x, NULL);
        }
    }
    return xlPtr;
}


