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
 *
 * @file ompc_reduction.h
 */
/*
 *  for reduction operation in Omni runtime
 */

typedef struct { float re,im; } ompc_complex_float;	/* float complex */
typedef struct { double re,im; } ompc_complex_double;	/* double complex */

typedef union {
    char c;
    unsigned char uc;
    short s;
    unsigned short us;
    int i;
    unsigned int ui;
    long l;
    unsigned long ul;
    long long ll;
    unsigned long long ull;
    float f;
    double d;
    float _Complex fcx;
    double _Complex dcx;
    long double ld;
    long double _Complex ldcx;
} any_type;

#define OMPC_REDUCTION_CHAR 2
#define OMPC_REDUCTION_UNSIGNED_CHAR 3
#define OMPC_REDUCTION_SHORT 4
#define OMPC_REDUCTION_UNSIGNED_SHORT 5
#define OMPC_REDUCTION_SIGNED 6
#define OMPC_REDUCTION_INT 7
#define OMPC_REDUCTION_UNSIGNED_INT 8
#define OMPC_REDUCTION_LONG 9
#define OMPC_REDUCTION_UNSIGNED_LONG 10
#define OMPC_REDUCTION_LONGLONG 11
#define OMPC_REDUCTION_UNSIGNED_LONGLONG 12
#define OMPC_REDUCTION_FLOAT 13
#define OMPC_REDUCTION_DOUBLE  14
#define OMPC_REDUCTION_LONG_DOUBLE 15
#define OMPC_REDUCTION_FLOAT_IMAGINARY 16
#define OMPC_REDUCTION_DOUBLE_IMAGINARY 17
#define OMPC_REDUCTION_LONG_DOUBLE_IMAGINARY 18
#define OMPC_REDUCTION_FLOAT_COMPLEX 19
#define OMPC_REDUCTION_DOUBLE_COMPLEX 20
#define OMPC_REDUCTION_LONG_DOUBLE_COMPLEX 21
#define OMPC_REDUCTION_GCC_BUILTIN_VA_LIST 22
#define OMPC_REDUCTION_F_CHARACTER 23
#define OMPC_REDUCTION_F_NUMERIC 24
#define OMPC_REDUCTION_F_NUMERIC_ALL 25
#define OMPC_REDUCTION_MAX_TYPES 26

#define OMPC_REDUCTION_PLUS     1
#define OMPC_REDUCTION_MINUS    2
#define OMPC_REDUCTION_MUL      3
#define OMPC_REDUCTION_LOGAND   4
#define OMPC_REDUCTION_LOGOR    5
#define OMPC_REDUCTION_MIN      6
#define OMPC_REDUCTION_MAX      7
#define OMPC_REDUCTION_BITAND   8
#define OMPC_REDUCTION_BITOR    9
#define OMPC_REDUCTION_BITXOR   10
#define OMPC_REDUCTION_LOGEQV   11
#define OMPC_REDUCTION_LOGNEQV  12
#define OMPC_REDUCTION_IAND     13
#define OMPC_REDUCTION_IOR      14
#define OMPC_REDUCTION_IEOR     15

