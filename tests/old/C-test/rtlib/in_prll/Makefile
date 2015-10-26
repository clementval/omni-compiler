# $Id$
# $TSUKUBA_Release: Omni Compiler Version 0.9.1 $
# $TSUKUBA_Copyright:
#  Copyright (C) 2010-2014 University of Tsukuba, 
#  	      2012-2014  University of Tsukuba and Riken AICS
#  
#  This software is free software; you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License version
#  2.1 published by the Free Software Foundation.
#  
#  Please check the Copyright and License information in the files named
#  COPYRIGHT and LICENSE under the top  directory of the Omni Compiler
#  Software release kit.
#  
#  * The specification of XcalableMP has been designed by the XcalableMP
#    Specification Working Group (http://www.xcalablemp.org/).
#  
#  * The development of this software was partially supported by "Seamless and
#    Highly-productive Parallel Programming Environment for
#    High-performance computing" project funded by Ministry of Education,
#    Culture, Sports, Science and Technology, Japan.
#  $
SHELL		= /bin/sh
EXEC		= /bin/sh -c
CC		= omcc
CFLAGS		= -O

PROGRAMS	= in_prll001 in_prll002 in_prll003 in_prll004 \
		  in_prll005 in_prll006 in_prll007
OBJS		= in_prll001.o in_prll002.o in_prll003.o in_prll004.o \
		  in_prll005.o in_prll006.o in_prll007.o
SRCS		= in_prll001.c in_prll002.c in_prll003.c in_prll004.c \
		  in_prll005.c in_prll006.c in_prll007.c


all:	${PROGRAMS}

clean:
	rm -f ${PROGRAMS} ${OBJS} *~

test:	${PROGRAMS}
	@for prog in ${PROGRAMS}; do	\
	  echo "run : $$prog";		\
	  $(EXEC) ./$$prog;		\
	done
