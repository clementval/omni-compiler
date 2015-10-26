#!/usr/bin/perl

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

my $thisfile = "c-exprcode.pl";
my $dfile = "c-exprcode.def";
my $hfile = "c-exprcode.h";
my $cfile = "c-exprcode.c";

open(IN, $dfile) || die "$!";
open(HOUT, ">${hfile}") || die "$!";
open(COUT, ">${cfile}") || die "$!";

print HOUT<<_EOL_;
/* This file is generated automatically by ${thisfile} */

#ifndef _C_EXPRCODE_H_
#define _C_EXPRCODE_H_

typedef enum {

_EOL_

print COUT<<_EOL_;
/* This file is generated automatically by ${thisfile} */

#include "c-expr.h"
#include "${hfile}"

const CExprCodeInfo s_CExprCodeInfos[] = {
_EOL_

my $i = 0;
while(my $l = <IN>) {
    next if($l =~ /^#|^\s*$/);
    chomp $l;
    my($type, $name, $ope) = split(/\s+/, $l);
    $ope =~ s/\s+//g;
    $ope =~ s/^"//;
    $ope =~ s/"$//;
    if($type eq 'T') {
        $type = "TERMINAL",
    } elsif($type eq 'L') {
        $type = "LIST",
    } elsif($type eq 'B') {
        $type = "BINARYOPE";
    } elsif($type eq 'U') {
        $type = "UNARYOPE";
    }

    if($i > 0) {
        print HOUT ",\n";
        print COUT ",\n";
    }
    printf HOUT "\t%-31s = %3d", "EC_${name}", $i;
    printf COUT "\t{ %-12s, %-33s, %-8s }", "ET_${type}", "\"${name}\"",
        (length($ope) > 0 ? "\"${ope}\"" : "(void*)0");
    ++$i;
}

close IN;

print HOUT<<_EOL_;
,
    EC_END = ${i}

} CExprCodeEnum;

typedef struct {
    CExprTypeEnum   ec_type;
    const char      *ec_name;
    const char      *ec_opeName;
} CExprCodeInfo;

extern const CExprCodeInfo s_CExprCodeInfos[EC_END];

#endif /* _C_EXPRCODE_H_ */

_EOL_

print COUT<<_EOL_;

};
_EOL_

close HOUT;
close COUT;

print "Created ${hfile}, ${cfile}\n";

