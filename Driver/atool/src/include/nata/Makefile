# $Id: Makefile.in 86 2012-07-30 05:33:07Z m-hirano $

TOPDIR		= /tmp/omnicompiler-0.9.3
MKRULESDIR	= /tmp/omnicompiler-0.9.3/Driver/atool/mk

include $(MKRULESDIR)/vars.mk

INSTALL_HEADER_DIR	= $(DEST_HDRDIR_TOP)/nata

include .headers

INSTALL_HEADER_TARGETS	= $(HEADERS)

include $(MKRULESDIR)/rules.mk

distclean::
	$(RM) nata_config.h nata_platform.h *.new *.bak .headers

