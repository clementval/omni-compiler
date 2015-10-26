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
/*
 * regs:
 *	$0  ... return val
 *	$16 ... 1st arg
 *	$31 ... zero reg
 */

	.set noat
	.set noreorder
	
	.text

.align 3
.globl	__alpha_get_clock
.ent	__alpha_get_clock

__alpha_get_clock:
	rpcc	$0
	ret
.end	__alpha_get_clock


.align 3
.globl	__alpha_mbar
.ent	__alpha_mbar
__alpha_mbar:
	mb
	ret
.end	__alpha_mbar

.align 3
.globl	__alpha_spin_unlock
.ent	__alpha_spin_unlock
__alpha_spin_unlock:
	mb
	stl	$31, 0($16)		/* store zero to lock var */
	ret
.end	__alpha_spin_unlock

.align 3
.globl	__alpha_spin_test_lock
.globl	__alpha_spin_lock
.ent	__alpha_spin_test_lock
__alpha_spin_test_lock:
	ldl_l	$0, 0($16)		/* load lock var */
	blbs	$0, alreadyLocked	/* if the lock var is NOT zero, go to alreadyLocked */
	br	fromTest		/* otherwise go to fromTest */
__alpha_spin_lock:
retry:
	ldl_l	$0, 0($16)		/* load lock var */
	blbs	$0, loopBody		/* if the lock var is NOT zero, go to loopBody */
fromTest:
	mov	1, $0			/* otherwise set $0 to one */
	stl_c	$0, 0($16)		/* store one to the lock var */
	beq	$0, loopBody		/* if the store failed, go to loopBody */
	mb				/* othewise flush */
	ret				/* and return 1 */
loopBody:
	ldl	$0, 0($16)		/* load the lock var again */
	blbs	$0, loopBody		/* if the lock var is one, loop */
	br	retry			/* otherwise (means some one unlock the lock var) go to retry */

alreadyLocked:
	mov	0, $0			/* return 0 */
	ret
.end	__alpha_spin_test_lock
