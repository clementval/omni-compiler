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

PROGRAMS	= lstprvt001 lstprvt002 lstprvt003 lstprvt004 \
		  lstprvt005 lstprvt006 lstprvt007 lstprvt008 \
		  lstprvt009 lstprvt010 lstprvt011 lstprvt012 \
		  lstprvt013 lstprvt014 lstprvt015 lstprvt016 \
		  lstprvt017 lstprvt018 lstprvt019 lstprvt020 \
		  lstprvt021 lstprvt022 lstprvt023
OBJS		= lstprvt001.o lstprvt002.o lstprvt003.o lstprvt004.o \
		  lstprvt005.o lstprvt006.o lstprvt007.o lstprvt008.o \
		  lstprvt009.o lstprvt010.o lstprvt011.o lstprvt012.o \
		  lstprvt013.o lstprvt014.o lstprvt015.o lstprvt016.o \
		  lstprvt017.o lstprvt018.o lstprvt019.o lstprvt020.o \
		  lstprvt021.o lstprvt022.o lstprvt023.o
SRCS		= lstprvt001.c lstprvt002.c lstprvt003.c lstprvt004.c \
		  lstprvt005.c lstprvt006.c lstprvt007.c lstprvt008.c \
		  lstprvt009.c lstprvt010.c lstprvt011.c lstprvt012.c \
		  lstprvt013.c lstprvt014.c lstprvt015.c lstprvt016.c \
		  lstprvt017.c lstprvt018.c lstprvt019.c lstprvt020.c \
		  lstprvt021.c lstprvt022.c lstprvt023.c


all:	${PROGRAMS}

clean:
	rm -f ${PROGRAMS} ${OBJS} *~

test:	${PROGRAMS}
	@for prog in ${PROGRAMS}; do	\
	  echo "run : $$prog";		\
	  $(EXEC) ./$$prog;		\
	done
