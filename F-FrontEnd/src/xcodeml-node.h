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
typedef enum {
    XcodeML_Unknown = 0,
    XcodeML_Element,
    XcodeML_Attribute,
    XcodeML_Value
} XcodeMLNodeTypeT;


struct XcodeMLListRec;


typedef struct {
    XcodeMLNodeTypeT xcType;
    char *xcName;
    union {
        void *xcGen;
        char *xcValuePtr;
        struct XcodeMLListRec *xcListPtr;
    } xcVal;

    int outputed; /* for xcodeml_out_F */
} XcodeMLNode;


typedef struct XcodeMLListRec {
    struct XcodeMLListRec *lNext;
    XcodeMLNode *lNode;
} XcodeMLList;


#define XCODEML_TYPE(x)     ((x)->xcType)
#define XCODEML_NAME(x)     ((x)->xcName)

#define XCODEML_GEN(x)      ((x)->xcVal.xcGen)
#define XCODEML_VALUE(x)    ((x)->xcVal.xcValuePtr)
#define XCODEML_LIST(x)     ((x)->xcVal.xcListPtr)

#define XCODEML_IS_TERMINAL(x) \
    ((XCODEML_TYPE(x) == XcodeML_Value) ? \
     true : false)

#define XCODEML_LIST_NEXT(lp)   ((lp)->lNext)
#define XCODEML_LIST_NODE(lp)   ((lp)->lNode)

#define XCODEML_ARG1(x) XCODEML_LIST_NODE(XCODEML_LIST(x))
#define XCODEML_ARG2(x) XCODEML_LIST_NODE(XCODEML_LIST_NEXT(XCODEML_LIST(x)))
#define XCODEML_ARG3(x) XCODEML_LIST_NODE(XCODEML_LIST_NEXT(XCODEML_LIST_NEXT(XMODEML_LIST(x))))

#define XCODEML_IS_OUTPUTED(x) ((x)->outputed)

#define FOR_ITEMS_IN_XCODEML_LIST(lp, x) \
    if ((x) != NULL) for (lp = XCODEML_LIST(x); \
                          lp != NULL; \
                          lp = XCODEML_LIST_NEXT(lp))


extern XcodeMLNode *    xcodeml_CreateGenericNode(XcodeMLNodeTypeT t,
                                                  void *v);
extern XcodeMLNode *    xcodeml_CreateValueNode(char *s);

extern XcodeMLNode *    xcodeml_CreateList0(XcodeMLNodeTypeT t);
extern XcodeMLNode *    xcodeml_CreateList1(XcodeMLNodeTypeT t,
                                            XcodeMLNode *x1);
extern XcodeMLNode *    xcodeml_CreateList2(XcodeMLNodeTypeT t,
                                            XcodeMLNode *x1, 
                                            XcodeMLNode *x2);
extern XcodeMLNode *    xcodeml_CreateList3(XcodeMLNodeTypeT t,
                                            XcodeMLNode *x1,
                                            XcodeMLNode *x2,
                                            XcodeMLNode *x3);
extern XcodeMLNode *    xcodeml_AppendNode(XcodeMLNode *xlPtr,
                                           XcodeMLNode *x);
