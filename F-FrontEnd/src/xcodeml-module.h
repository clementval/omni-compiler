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
 * \file xcodeml-module.h
 */

#ifndef _XCODEML_MODULE_H_
#define _XCODEML_MODULE_H_

extern int use_module(const char * module_filename, const char * fortran_filename);
extern int use_module_to(const char * module_filename, FILE * fd);

typedef struct symbol_filterElm_t {
    char * use;
    char * local;
    struct symbol_filterElm_t * next;
} symbol_filterElem;

enum filter_usage {
    RENAME,
    LIMIT,
    ACCEPTANY,
};

typedef struct symbol_filter_t {
    enum filter_usage usage;
    struct symbol_filterElm_t * list;
    struct symbol_filter_t * next;
    int nonUseSymbolNumber;
} symbol_filter;

#define FILTER_USAGE(f) ((f)->usage)

extern symbol_filter * push_new_filter(void);
extern symbol_filter * peek_filter(void);
extern void pop_filter(void);
extern void symbol_filter_addElem(symbol_filter * filter, char * use, char * local);
extern char * apply_filter(symbol_filter * filter, char * symbol);
extern int is_use_symbol(char *symbol);
extern char * convert_to_non_use_symbol(char *orgname);

#endif /* _XCODEML_MODULE_H_ */
