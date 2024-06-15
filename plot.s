	.sect	.text
	.sect	.rom
	.sect	.data
	.sect	.bss

;gcc2_compiled
	.sect	.text
	.align 2
	.extern	 _plot
_plot:
	move.l a2,-(sp)
	move.l 12(sp),d1
	move.l 16(sp),d0
	lsl.l #7,d0
	move.l 8(sp),a2
	add.l d0,a2
	move.l d1,d0
	lsr.l #2,d0
	move.l d0,a1
	add.l d0,a1
	moveq.l #3,d0
	and.l d0,d1
	move.l d1,d0
	lsl.l #4,d0
	add.l d1,d0
	add.l d1,d0
	move.l d0,a0
	add.l #_colours,a0
	move.w 0(a1,a2.l),d1
	and.w 16(a0),d1
	clr.l d0
	move.b 21(sp),d0
	add.l d0,d0
	or.w 0(a0,d0.l),d1
	move.w d1,0(a1,a2.l)
	move.l (sp)+,a2
	rts
