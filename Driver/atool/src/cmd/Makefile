# $Id: Makefile.in 111 2012-08-07 13:04:22Z m-hirano $

TOPDIR		= /tmp/omnicompiler-1.0.0
MKRULESDIR	= /tmp/omnicompiler-1.0.0/Driver/atool/mk

include $(MKRULESDIR)/vars.mk

SRCS		= \
	OutputFileProviderStatics.cpp \
	main.cpp

OBJS		= \
	OutputFileProviderStatics.lo \
	main.lo

TARGETS		= atool
INSTALL_EXE_TARGETS	= $(TARGETS)
INSTALL_EXE_DIR	= $(DEST_EXEDIR)

ALL::	$(TARGETS)

atool:	$(OBJS) $(DEP_NATALIB)
	$(LTCLEAN) $@
	$(LTLINK_CXX) -o $@ $(OBJS) $(DEP_NATALIB) $(LDFLAGS)

$(DEP_NATALIB):
	(cd $(BUILD_LIBDIR); $(MAKE))

distclean::
	$(RM) paths.h

include $(MKRULESDIR)/rules.mk
include .depend
