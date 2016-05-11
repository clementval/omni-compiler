# $Id: Makefile.in 86 2012-07-30 05:33:07Z m-hirano $

TOPDIR		= /tmp/omnicompiler-1.0.0
MKRULESDIR	= /tmp/omnicompiler-1.0.0/Driver/atool/mk

include $(MKRULESDIR)/vars.mk

INSTALL_HEADER_DIR	= $(DEST_HDRDIR_TOP)/nata

include .headers

INSTALL_HEADER_TARGETS	= $(HEADERS)

include $(MKRULESDIR)/rules.mk

distclean::
	$(RM) nata_config.h nata_platform.h *.new *.bak .headers

