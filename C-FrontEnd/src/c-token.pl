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
use strict;

my $cfile = "c-token.c";
my $hfile = "c-token.h";

open(IN, "c-parser.h") || die "$!";
open(COUT, ">${cfile}") || die "$!";

print COUT<<_EOL_;
#include "c-token.h"

const CTokenInfo s_CTokenInfos[] = {
_EOL_

my $fmt = "    { %-30s, %3d },\n";

while(<IN>) {
	if(/^#define\s+(IDENTIFIER)\s+([0-9]+)\s*$/) {
		printf COUT $fmt, "\"$1\"", $2;
		last;
	}
}

my $count = 1;

while(<IN>) {
	if(/^#define\s+([a-zA-Z0-9_]+)\s+([0-9]+)$/) {
		printf COUT $fmt, "\"$1\"", $2;
		++$count;
	} else {
		last;
	}
}

print COUT<<_EOL_;
};

_EOL_

close IN;
close COUT;

open(HOUT, ">${hfile}") || die "$!";

print HOUT<<_EOL_;
#ifndef _C_TOKEN_H_
#define _C_TOKEN_H_

typedef struct {
	const char *name;
	const int code;
} CTokenInfo;

#define CTOKENINFO_SIZE ${count}

extern const CTokenInfo s_CTokenInfos[CTOKENINFO_SIZE];

#endif /* _C_TOKEN_H_ */

_EOL_

close HOUT;

print "Created ${cfile}, ${hfile}\n";


