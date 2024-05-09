	.sect	.text
	.sect	.rom
	.sect	.data
	.sect	.bss

;gcc2_compiled
	.extern	 _masks
	.sect	.text
	.align 2
_masks:
	.data2 16191
	.data2 53199
	.data2 62451
	.data2 64764
	.extern	 _colours
	.align 2
_colours:
	.data2 0
	.data2 64
	.data2 128
	.data2 192
	.data2 32768
	.data2 32832
	.data2 32896
	.data2 32960
	.data2 0
	.data2 16
	.data2 32
	.data2 48
	.data2 8192
	.data2 8208
	.data2 8224
	.data2 8240
	.data2 0
	.data2 4
	.data2 8
	.data2 12
	.data2 2048
	.data2 2052
	.data2 2056
	.data2 2060
	.data2 0
	.data2 1
	.data2 2
	.data2 3
	.data2 512
	.data2 513
	.data2 514
	.data2 515
	.align 2
	.extern	 _plot
_plot:
	move.l a2,-(sp)
	move.l 12(sp),d1	# d1=x
	move.l 16(sp),d0	# d0=y
	lsl.l #7,d0		# d0=y*64
	move.l 8(sp),a2		# a2=screen
	add.l d0,a2		# a2=screen+y*64
	move.l d1,d0		# d0=x
	lsr.l #2,d0		# d0=x>>2
	move.l d0,a1		# a0=x>>2
	add.l d0,a1		# a0=2*(x>>2)
	moveq.l #3,d0
	and.l d0,d1
	move.l d1,d0
	add.l d1,d0
	lea _masks,a0
	move.w 0(a1,a2.l),d2
	and.w 0(a0,d0.l),d2
	clr.l d0
	move.b 21(sp),d0
	add.l d0,d0
	lsl.l #4,d1
	add.l d1,d0
	lea _colours,a0
	or.w 0(a0,d0.l),d2
	move.w d2,0(a1,a2.l)
	move.l (sp)+,a2
	rts
