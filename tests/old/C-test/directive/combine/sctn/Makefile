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

PROGRAMS	= prlsctn001 prlsctn002 prlsctn003 prlsctn004 \
	          prlsctn005 prlsctn006 prlsctn007 prlsctn008
OBJS		= prlsctn001.o prlsctn002.o prlsctn003.o prlsctn004.o \
	          prlsctn005.o prlsctn006.o prlsctn007.o prlsctn008.o
SRCS		= prlsctn001.c prlsctn002.c prlsctn003.c prlsctn004.c \
	          prlsctn005.c prlsctn006.c prlsctn007.c prlsctn008.c

all:	${PROGRAMS}

clean:
	rm -f ${PROGRAMS} ${OBJS} *~

test:	${PROGRAMS}
	@for prog in ${PROGRAMS}; do	\
	  echo "run : $$prog";		\
	  $(EXEC) ./$$prog;		\
	done
