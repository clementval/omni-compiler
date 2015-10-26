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

PROGRAMS	= cpyin001 cpyin002 cpyin003 cpyin004 \
		  cpyin005 cpyin006 cpyin007 cpyin008 \
		  cpyin009 cpyin010 cpyin011 cpyin012 \
		  cpyin013 cpyin014 cpyin015 cpyin016 \
		  cpyin017 cpyin018 cpyin019 cpyin020 \
		  cpyin021
OBJS		= cpyin001.o cpyin002.o cpyin003.o cpyin004.o \
		  cpyin005.o cpyin006.o cpyin007.o cpyin008.o \
		  cpyin009.o cpyin010.o cpyin011.o cpyin012.o \
		  cpyin013.o cpyin014.o cpyin015.o cpyin016.o \
		  cpyin017.o cpyin018.o cpyin019.o cpyin020.o \
		  cpyin021.o
SRCS		= cpyin001.c cpyin002.c cpyin003.c cpyin004.c \
		  cpyin005.c cpyin006.c cpyin007.c cpyin008.c \
		  cpyin009.c cpyin010.c cpyin011.c cpyin012.c \
		  cpyin013.c cpyin014.c cpyin015.c cpyin016.c \
		  cpyin017.c cpyin018.c cpyin019.c cpyin020.c \
		  cpyin021.c


all:	${PROGRAMS}

clean:
	rm -f ${PROGRAMS} ${OBJS} *~

test:	${PROGRAMS}
	@for prog in ${PROGRAMS}; do	\
	  echo "run : $$prog";		\
	  $(EXEC) ./$$prog;		\
	done
