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

PROGRAMS	= shrd001 shrd002 shrd003 shrd004 \
		  shrd005 shrd006 shrd007 shrd008 \
		  shrd009 shrd010 shrd011 shrd012 \
		  shrd013 shrd014 shrd015 shrd016 \
		  shrd017 shrd018 shrd019 shrd020 \
		  shrd021 shrd022
OBJS		= shrd001.o shrd002.o shrd003.o shrd004.o \
		  shrd005.o shrd006.o shrd007.o shrd008.o \
		  shrd009.o shrd010.o shrd011.o shrd012.o \
		  shrd013.o shrd014.o shrd015.o shrd016.o \
		  shrd017.o shrd018.o shrd019.o shrd020.o \
		  shrd021.o shrd022.o
SRCS		= shrd001.c shrd002.c shrd003.c shrd004.c \
		  shrd005.c shrd006.c shrd007.c shrd008.c \
		  shrd009.c shrd010.c shrd011.c shrd012.c \
		  shrd013.c shrd014.c shrd015.c shrd016.c \
		  shrd017.c shrd018.c shrd019.c shrd020.c \
		  shrd021.c shrd022.c


all:	${PROGRAMS}

clean:
	rm -f ${PROGRAMS} ${OBJS} *~

test:	${PROGRAMS}
	@for prog in ${PROGRAMS}; do	\
	  echo "run : $$prog";		\
	  $(EXEC) ./$$prog;		\
	done
