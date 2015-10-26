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

PROGRAMS	= flush001 flush002 flush003 flush004 \
		  flush005 flush006 flush007 flush008 \
		  flush009 flush010 flush011 flush012 \
		  flush013 flush014 flush015 flush016 \
		  flush017 flush018 flush019 flush020 \
		  flush021 flush022 flush023
OBJS		= flush001.o flush002.o flush003.o flush004.o \
		  flush005.o flush006.o flush007.o flush008.o \
		  flush009.o flush010.o flush011.o flush012.o \
		  flush013.o flush014.o flush015.o flush016.o \
		  flush017.o flush018.o flush019.o flush020.o \
		  flush021.o flush022.o flush023.o
SRCS		= flush001.c flush002.c flush003.c flush004.c \
		  flush005.c flush006.c flush007.c flush008.c \
		  flush009.c flush010.c flush011.c flush012.c \
		  flush013.c flush014.c flush015.c flush016.c \
		  flush017.c flush018.c flush019.c flush020.c \
		  flush021.c flush022.c flush023.c


all:	${PROGRAMS}

clean:
	rm -f ${PROGRAMS} ${OBJS} *~

test:	${PROGRAMS}
	@for prog in ${PROGRAMS}; do	\
	  echo "run : $$prog";		\
	  $(EXEC) ./$$prog;		\
	done
