# $Id: vars.mk.in 86 2012-07-30 05:33:07Z m-hirano $

TARGET_ARCH	= POSIX

SHELL		= /bin/bash
VPATH		= .
srcdir		= .
TOPDIR		= /tmp/omnicompiler-1.0.0
top_builddir	?= $(TOPDIR)
MKRULESDIR	= /tmp/omnicompiler-1.0.0/Driver/atool/mk

PREFIX		= /usr/local
DEST_EXEDIR	= $(PREFIX)/bin
DEST_LIBDIR	= $(PREFIX)/lib
DEST_HDRDIR_TOP	= $(PREFIX)/include

LIBTOOL_DEPS	= @LIBTOOL_DEPS@

MAKE		= LC_ALL=C make
RM		= rm -f
MKDIR		= @MKDIR@
LIBTOOL		= LC_ALL=C @LIBTOOL@ --quiet

CC		= gcc
CXX		= g++

INSTALL		= /usr/bin/install -c
INSTALL_DATA	= ${INSTALL} -m 644
INSTALL_SCRIPT	= ${INSTALL}
INSTALL_PROGRAM	= ${INSTALL}

BUILD_SRCDIR	= $(TOPDIR)/Driver/atool/src
BUILD_INCDIR	= $(BUILD_SRCDIR)/include
BUILD_LIBDIR	= $(BUILD_SRCDIR)/lib

SITECONF_MK	?=	$(shell ls $(MKRULESDIR)/siteconf.mk 2>/dev/null)
ifdef SITECONF_MK
__SITECONF__=.pre.
include $(SITECONF_MK)
endif

NATALIB		= libnata.la

DEP_NATALIB	= $(BUILD_LIBDIR)/$(NATALIB)

CPPFLAGS	+= -I$(BUILD_INCDIR)

WARN_BASE_CFLAGS	+= -W -Wall -Wextra -pedantic \
	-Wshadow \
	-Wcast-align \
	-Wwrite-strings \
	-Wconversion \
	-Wmissing-format-attribute \
	-Wno-long-long \
	-Wno-variadic-macros

#	-Wlogical-op
#	-Waddress 

WARN_CFLAGS	+= $(WARN_BASE_CFLAGS) \
	-Wstrict-prototypes \
	-Wold-style-definition \
	-Wmissing-declarations \
	-Wmissing-prototypes \
	-Wnested-externs \
	-Wdeclaration-after-statement


WARN_CXXFLAGS	+= $(WARN_BASE_CFLAGS) \
	-Wnon-virtual-dtor \
	-Wstrict-null-sentinel \
	-Woverloaded-virtual

DEBUG_CFLAGS	+= -g3
DEBUG_CXXFLAGS	+= -g3

OPT_CFLAGS	+= -O0 -fno-omit-frame-pointer
OPT_CXXFLAGS	+= -O0 -fno-omit-frame-pointer

CODEGEN_CFLAGS		+= -fkeep-inline-functions
CODEGEN_CXXFLAGS	+= -fkeep-inline-functions


COMMON_CFLAGS	= $(WARN_CFLAGS) $(DEBUG_CFLAGS) $(OPT_CFLAGS) \
	$(CODEGEN_CFLAGS) $(LOCAL_CFLAGS)

COMMON_CXXFLAGS	= $(WARN_CXXFLAGS) $(DEBUG_CXXFLAGS) $(OPT_CXXFLAGS) \
	$(CODEGEN_CXXFLAGS) $(LOCAL_CXXFLAGS)

CFLAGS		+=  -g -O2 -std=gnu99 -Wall -Wpointer-arith $(COMMON_CFLAGS)
CXXFLAGS	+=  -g -O2 $(COMMON_CXXFLAGS)

LDFLAGS		+=  -lrt -lpthread 

OBJS		?= $(SRCS:.cpp=.lo)

ifdef TARGET_LIB
SHLIB_VERSION	?= 0:0:0
LTLINK_VERSION	= -version-info $(SHLIB_VERSION)
endif
LTLINK_RPATH	= -rpath $(DEST_LIBDIR)

STATICBUILD	=	@STATICBUILD@
ifndef STATICBUILD
LT_SHARED	=	-shared
endif

LTCOMPILE_CC	= $(LIBTOOL) --mode=compile --tag=CC $(CC) $(CFLAGS) \
	$(CPPFLAGS) $(LT_SHARED)
LTCOMPILE_CXX	= $(LIBTOOL) --mode=compile --tag=CXX $(CXX) $(CXXFLAGS) \
	$(CPPFLAGS) $(LT_SHARED)
LTLINK_CC	= $(LIBTOOL) --mode=link \
	$(CC) $(CFLAGS) $(LTLINK_RPATH) $(LTLINK_VERSION) $(LT_SHARED)
LTLINK_CXX	= $(LIBTOOL) --mode=link \
	$(CXX) $(CXXFLAGS) $(LTLINK_RPATH) $(LTLINK_VERSION) $(LT_SHARED)
LTINSTALL_EXE	= $(LIBTOOL) --mode=install $(INSTALL_PROGRAM)
LTINSTALL_LIB	= $(LIBTOOL) --mode=install $(INSTALL_DATA)
LTINSTALL_HEADER= $(LIBTOOL) --mode=install $(INSTALL_DATA)
LTCLEAN		= $(LIBTOOL) --mode=clean $(RM)

ifdef SITECONF_MK
__SITECONF__=.post.
include $(SITECONF_MK)
endif
