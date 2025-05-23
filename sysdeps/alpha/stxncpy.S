/* Copyright (C) 1996-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <https://www.gnu.org/licenses/>.  */

/* Copy no more than COUNT bytes of the null-terminated string from
   SRC to DST.

   This is an internal routine used by strncpy, stpncpy, and strncat.
   As such, it uses special linkage conventions to make implementation
   of these public functions more efficient.

   On input:
	t9 = return address
	a0 = DST
	a1 = SRC
	a2 = COUNT

   Furthermore, COUNT may not be zero.

   On output:
	t0  = last word written
	t8  = bitmask (with one bit set) indicating the last byte written
	t10 = bitmask (with one bit set) indicating the byte position of
	      the end of the range specified by COUNT
	a0  = unaligned address of the last *word* written
	a2  = the number of full words left in COUNT

   Furthermore, v0, a3-a5, t11, and t12 are untouched.
*/


/* This is generally scheduled for the EV5, but should still be pretty
   good for the EV4 too.  */

#include <sysdep.h>

	.set noat
	.set noreorder

	.text
	.type	__stxncpy, @function
	.globl	__stxncpy
	.usepv	__stxncpy, no

	cfi_startproc
	cfi_return_column (t9)

	/* On entry to this basic block:
	   t0 == the first destination word for masking back in
	   t1 == the first source word.  */
	.align 3
stxncpy_aligned:
	/* Create the 1st output word and detect 0's in the 1st input word.  */
	lda	t2, -1		# e1    : build a mask against false zero
	mskqh	t2, a1, t2	# e0    :   detection in the src word
	mskqh	t1, a1, t3	# e0    :
	ornot	t1, t2, t2	# .. e1 :
	mskql	t0, a1, t0	# e0    : assemble the first output word
	cmpbge	zero, t2, t7	# .. e1 : bits set iff null found
	or	t0, t3, t0	# e0    :
	beq	a2, $a_eoc	# .. e1 :
	bne	t7, $a_eos	# .. e1 :

	/* On entry to this basic block:
	   t0 == a source word not containing a null.  */
$a_loop:
	stq_u	t0, 0(a0)	# e0    :
	addq	a0, 8, a0	# .. e1 :
	ldq_u	t0, 0(a1)	# e0    :
	addq	a1, 8, a1	# .. e1 :
	subq	a2, 1, a2	# e0    :
	cmpbge	zero, t0, t7	# .. e1 (stall)
	beq	a2, $a_eoc      # e1    :
	beq	t7, $a_loop	# e1    :

	/* Take care of the final (partial) word store.  At this point
	   the end-of-count bit is set in t7 iff it applies.

	   On entry to this basic block we have:
	   t0 == the source word containing the null
	   t7 == the cmpbge mask that found it.  */
$a_eos:
	negq	t7, t8		# e0    : find low bit set
	and	t7, t8, t8	# e1 (stall)

	/* For the sake of the cache, don't read a destination word
	   if we're not going to need it.  */
	and	t8, 0x80, t6	# e0    :
	bne	t6, 1f		# .. e1 (zdb)

	/* We're doing a partial word store and so need to combine
	   our source and original destination words.  */
	ldq_u	t1, 0(a0)	# e0    :
	subq	t8, 1, t6	# .. e1 :
	or	t8, t6, t7	# e0    :
	unop			#
	zapnot	t0, t7, t0	# e0    : clear src bytes > null
	zap	t1, t7, t1	# .. e1 : clear dst bytes <= null
	or	t0, t1, t0	# e1    :

1:	stq_u	t0, 0(a0)	# e0    :
	ret	(t9)		# e1    :

	/* Add the end-of-count bit to the eos detection bitmask.  */
$a_eoc:
	or	t10, t7, t7
	br	$a_eos

	.align 3
__stxncpy:
	/* Are source and destination co-aligned?  */
	lda	t2, -1
	xor	a0, a1, t1
	srl	t2, 1, t2
	and	a0, 7, t0		# find dest misalignment
	cmovlt	a2, t2, a2		# bound neg count to LONG_MAX
	and	t1, 7, t1
	addq	a2, t0, a2		# bias count by dest misalignment
	subq	a2, 1, a2
	and	a2, 7, t2
	srl	a2, 3, a2		# a2 = loop counter = (count - 1)/8
	addq	zero, 1, t10
	sll	t10, t2, t10		# t10 = bitmask of last count byte
	bne	t1, $unaligned

	/* We are co-aligned; take care of a partial first word.  */

	ldq_u	t1, 0(a1)	# e0    : load first src word
	addq	a1, 8, a1	# .. e1 :

	beq	t0, stxncpy_aligned     # avoid loading dest word if not needed
	ldq_u	t0, 0(a0)	# e0    :
	br	stxncpy_aligned	# .. e1 :


/* The source and destination are not co-aligned.  Align the destination
   and cope.  We have to be very careful about not reading too much and
   causing a SEGV.  */

	.align 3
$u_head:
	/* We know just enough now to be able to assemble the first
	   full source word.  We can still find a zero at the end of it
	   that prevents us from outputting the whole thing.

	   On entry to this basic block:
	   t0 == the first dest word, unmasked
	   t1 == the shifted low bits of the first source word
	   t6 == bytemask that is -1 in dest word bytes */

	ldq_u	t2, 8(a1)	# e0    : load second src word
	addq	a1, 8, a1	# .. e1 :
	mskql	t0, a0, t0	# e0    : mask trailing garbage in dst
	extqh	t2, a1, t4	# e0    :
	or	t1, t4, t1	# e1    : first aligned src word complete
	mskqh	t1, a0, t1	# e0    : mask leading garbage in src
	or	t0, t1, t0	# e0    : first output word complete
	or	t0, t6, t6	# e1    : mask original data for zero test
	cmpbge	zero, t6, t7	# e0    :
	beq	a2, $u_eocfin	# .. e1 :
	lda	t6, -1		# e0    :
	bne	t7, $u_final	# .. e1 :

	mskql	t6, a1, t6		# e0    : mask out bits already seen
	nop				# .. e1 :
	stq_u	t0, 0(a0)		# e0    : store first output word
	or      t6, t2, t2		# .. e1 :
	cmpbge	zero, t2, t7		# e0    : find nulls in second partial
	addq	a0, 8, a0		# .. e1 :
	subq	a2, 1, a2		# e0    :
	bne	t7, $u_late_head_exit	# .. e1 :

	/* Finally, we've got all the stupid leading edge cases taken care
	   of and we can set up to enter the main loop.  */

	extql	t2, a1, t1	# e0    : position hi-bits of lo word
	beq	a2, $u_eoc	# .. e1 :
	ldq_u	t2, 8(a1)	# e0    : read next high-order source word
	addq	a1, 8, a1	# .. e1 :
	extqh	t2, a1, t0	# e0    : position lo-bits of hi word
	cmpbge	zero, t2, t7	# .. e1 : test new word for eos
	nop			# e0    :
	bne	t7, $u_eos	# .. e1 :

	/* Unaligned copy main loop.  In order to avoid reading too much,
	   the loop is structured to detect zeros in aligned source words.
	   This has, unfortunately, effectively pulled half of a loop
	   iteration out into the head and half into the tail, but it does
	   prevent nastiness from accumulating in the very thing we want
	   to run as fast as possible.

	   On entry to this basic block:
	   t0 == the shifted low-order bits from the current source word
	   t1 == the shifted high-order bits from the previous source word
	   t2 == the unshifted current source word

	   We further know that t2 does not contain a null terminator.  */

	.align 3
$u_loop:
	or	t0, t1, t0	# e0    : current dst word now complete
	subq	a2, 1, a2	# .. e1 : decrement word count
	stq_u	t0, 0(a0)	# e0    : save the current word
	addq	a0, 8, a0	# .. e1 :
	extql	t2, a1, t1	# e0    : extract high bits for next time
	beq	a2, $u_eoc	# .. e1 :
	ldq_u	t2, 8(a1)	# e0    : load high word for next time
	addq	a1, 8, a1	# .. e1 :
	nop			# e0    :
	cmpbge	zero, t2, t7	# .. e1 : test new word for eos
	extqh	t2, a1, t0	# e0    : extract low bits for current word
	beq	t7, $u_loop	# .. e1 :

	/* We've found a zero somewhere in the source word we just read.
	   If it resides in the lower half, we have one (probably partial)
	   word to write out, and if it resides in the upper half, we
	   have one full and one partial word left to write out.

	   On entry to this basic block:
	   t0 == the shifted low-order bits from the current source word
	   t1 == the shifted high-order bits from the previous source word
	   t2 == the unshifted current source word.  */
$u_eos:
	or	t0, t1, t0	# e0    : first (partial) source word complete
	cmpbge	zero, t0, t7	# e0    : is the null in this first bit?
	bne	t7, $u_final	# .. e1 (zdb)

	stq_u	t0, 0(a0)	# e0    : the null was in the high-order bits
	addq	a0, 8, a0	# .. e1 :
	subq	a2, 1, a2	# e0    :

$u_late_head_exit:
	extql	t2, a1, t0	# e0    :
	cmpbge	zero, t0, t7	# e0    :
	or	t7, t10, t6	# e1    :
	cmoveq	a2, t6, t7	# e0    :

	/* Take care of a final (probably partial) result word.
	   On entry to this basic block:
	   t0 == assembled source word
	   t7 == cmpbge mask that found the null.  */
$u_final:
	negq	t7, t6		# e0    : isolate low bit set
	and	t6, t7, t8	# e1    :

	and	t8, 0x80, t6	# e0    : avoid dest word load if we can
	bne	t6, 1f		# .. e1 (zdb)

	ldq_u	t1, 0(a0)	# e0    :
	subq	t8, 1, t6	# .. e1 :
	or	t6, t8, t7	# e0    :
	zapnot	t0, t7, t0	# .. e1 : kill source bytes > null
	zap	t1, t7, t1	# e0    : kill dest bytes <= null
	or	t0, t1, t0	# e1    :

1:	stq_u	t0, 0(a0)	# e0    :
	ret	(t9)		# .. e1 :

	/* Got to end-of-count before end of string.
	   On entry to this basic block:
	   t1 == the shifted high-order bits from the previous source word  */
$u_eoc:
	and	a1, 7, t6	# e1    :
	sll	t10, t6, t6	# e0    :
	and	t6, 0xff, t6	# e0	:
	bne	t6, 1f		# e1    : avoid src word load if we can

	ldq_u	t2, 8(a1)	# e0    : load final src word
	nop			# .. e1 :
	extqh	t2, a1, t0	# e0    : extract high bits for last word
	or	t1, t0, t1	# e1    :

1:	cmpbge	zero, t1, t7
	mov	t1, t0

$u_eocfin:			# end-of-count, final word
	or	t10, t7, t7
	br	$u_final

	/* Unaligned copy entry point.  */
	.align 3
$unaligned:

	ldq_u	t1, 0(a1)	# e0    : load first source word

	and	a0, 7, t4	# .. e1 : find dest misalignment
	and	a1, 7, t5	# e0    : find src misalignment

	/* Conditionally load the first destination word and a bytemask
	   with 0xff indicating that the destination byte is sacrosanct.  */

	mov	zero, t0	# .. e1 :
	mov	zero, t6	# e0    :
	beq	t4, 1f		# .. e1 :
	ldq_u	t0, 0(a0)	# e0    :
	lda	t6, -1		# .. e1 :
	mskql	t6, a0, t6	# e0    :
1:
	subq	a1, t4, a1	# .. e1 : sub dest misalignment from src addr

	/* If source misalignment is larger than dest misalignment, we need
	   extra startup checks to avoid SEGV.  */

	cmplt	t4, t5, t8	# e1    :
	extql	t1, a1, t1	# .. e0 : shift src into place
	lda	t2, -1		# e0    : for creating masks later
	beq	t8, $u_head	# e1    :

	mskqh	t2, t5, t2	# e0    : begin src byte validity mask
	cmpbge	zero, t1, t7	# .. e1 : is there a zero?
	extql	t2, a1, t2	# e0    :
	or	t7, t10, t5	# .. e1 : test for end-of-count too
	cmpbge	zero, t2, t3	# e0    :
	cmoveq	a2, t5, t7	# .. e1 :
	andnot	t7, t3, t7	# e0    :
	beq	t7, $u_head	# .. e1 (zdb)

	/* At this point we've found a zero in the first partial word of
	   the source.  We need to isolate the valid source data and mask
	   it into the original destination data.  (Incidentally, we know
	   that we'll need at least one byte of that original dest word.) */

	ldq_u	t0, 0(a0)	# e0    :
	negq	t7, t6		# .. e1 : build bitmask of bytes <= zero
	mskqh	t1, t4, t1	# e0    :
	and	t6, t7, t8	# .. e1 :
	subq	t8, 1, t6	# e0    :
	or	t6, t8, t7	# e1    :

	zapnot	t2, t7, t2	# e0    : prepare source word; mirror changes
	zapnot	t1, t7, t1	# .. e1 : to source validity mask

	andnot	t0, t2, t0	# e0    : zero place for source to reside
	or	t0, t1, t0	# e1    : and put it there
	stq_u	t0, 0(a0)	# e0    :
	ret	(t9)		# .. e1 :

	cfi_endproc
