# $Id: Makefile.in 86 2012-07-30 05:33:07Z m-hirano $

TOPDIR		= /tmp/omnicompiler-1.0.0
MKRULESDIR	= /tmp/omnicompiler-1.0.0/Driver/atool/mk

include $(MKRULESDIR)/vars.mk

DIRS	=	$(TOPDIR)/Driver/atool/src/lib \
		$(TOPDIR)/Driver/atool/src/include/nata \
		$(TOPDIR)/Driver/atool/src/cmd

include $(MKRULESDIR)/rules.mk

clean::
	$(RM) -r autom4te.cache config.log
	find . -type f -name '*~' -o -name '*.core' -exec rm -f {} \;

distclean::
	$(RM) config.* mk/vars.mk ./libtool
