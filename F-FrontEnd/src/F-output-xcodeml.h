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
 * \file F-output-xcodeml.h
 */

#ifndef _F_XCODEML_H_
#define _F_XCODEML_H_

#include "module-manager.h"

#ifdef Min
#undef Min
#endif
#define Min(a, b) (((a) > (b)) ? (b) : (a))

extern void final_fixup();
extern void output_XcodeML_file();
extern void output_module_file(struct module *);

#define CEXPR_OPTVAL_CHARLEN 128

#define C_SYM_NAME(X)  (SYM_NAME(X))

#define F_FRONTEND_NAME "XcodeML/Fortran-FrontEnd"
#define F_TARGET_LANG   "Fortran"
#define F_FRONTEND_VER  "1.0"
#define F_MODULE_VER  "1.0"

extern char s_timestamp[];
extern char s_xmlIndent[];

#endif /* _F_XCODEML_H_ */
