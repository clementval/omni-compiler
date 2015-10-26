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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *
chkIntSize(sz)
     int sz;
{
    if (sizeof(char) == sz) {
	return "char";
    } else if (sizeof(int) == sz) {
	return "int";
    } else if (sizeof(short) == sz) {
	return "short";
    } else if (sizeof(long int) == sz) {
	return "long int";
    } else if (sizeof(long long int) == sz) {
	return "long long int";
    } else {
	return "unknown";
    }
}


int
main(argc, argv)
     int argc;
     char *argv[];
{
    int sz;

    if (argc < 2) {
	return 1;
    }
    sz = atoi(argv[1]) / 8;

    printf("%s\n", chkIntSize(sz));
    return 0;
}
