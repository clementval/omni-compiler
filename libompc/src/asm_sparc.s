/* 
 * $TSUKUBA_Release: Omni Compiler Version 0.9.1 $
 * $TSUKUBA_Copyright:
 *  Copyright (C) 2010-2014 University of Tsukuba, 
 *  	      2012-2014  University of Tsukuba and Riken AICS
 *  
 *  This software is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 published by the Free Software Foundation.
 *  
 *  Please check the Copyright and License information in the files named
 *  COPYRIGHT and LICENSE under the top  directory of the Omni Compiler
 *  Software release kit.
 *  
 *  * The specification of XcalableMP has been designed by the XcalableMP
 *    Specification Working Group (http://www.xcalablemp.org/).
 *  
 *  * The development of this software was partially supported by "Seamless and
 *    Highly-productive Parallel Programming Environment for
 *    High-performance computing" project funded by Ministry of Education,
 *    Culture, Sports, Science and Technology, Japan.
 *  $
 */

	.align  8
	.skip   16

	.type   LockWithLdstUB,#function
	.global LockWithLdstUB
LockWithLdstUB:
retry:
	ldstub  [%o0],%o1       ! atomic load store
	tst     %o1
	be      out
	nop
loop:
	ldub    [%o0],%o1       ! load and test
	tst     %o1
	bne     loop
	nop
	ba,a    retry
out:
	nop
	jmp     %o7+8   ! return
	nop

	.type   TestLockWithLdstUB,#function
	.global TestLockWithLdstUB
TestLockWithLdstUB:
	ldstub  [%o0],%o0       ! atomic load store
	jmp     %o7+8   ! return
	nop

	.type   UnlockWithLdstUB,#function
	.global UnlockWithLdstUB
UnlockWithLdstUB:
	stbar
	stb     %g0,[%o0]       ! clear lock
	jmp     %o7+8           ! return
	nop
