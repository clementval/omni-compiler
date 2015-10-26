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
my $ERROR_H = "c-error.h";
my $TMP_FILE = "__tmp__${ERROR_H}";
my $count = 0;

open(IN, $ERROR_H) || die "$!";
open(OUT, ">".$TMP_FILE) || die "$!";

while(my $l = <IN>) {
	if($l =~ /#define C([A-Z]+)_([0-9]+)\s+"([A-Z][0-9]{3}:[^"]+)"/) {
		print OUT $l;
	} elsif($l =~ /#define C([A-Z]+)_([0-9]+)\s+"([^"]+)"/) {
		my ($k, $n, $m, $kh) = ($1, $2, $3);
		$k =~ /^(.)/;
		$kh = $1;
		print OUT "#define C${k}_${n} \"${kh}${n}: ${m}\"\n";
		++$count;
	} else {
		print OUT $l;
	}
}

close(IN);
close(OUT);

if($count > 0) {
	unlink $ERROR_H || die "$!";
	rename $TMP_FILE, $ERROR_H || die "$!";
	print "modified ${count} line(s)\n";
} else {
	unlink $TMP_FILE || die "$!";
	print "no modification\n";
}

