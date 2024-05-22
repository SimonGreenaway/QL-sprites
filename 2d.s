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
	.extern	 _masks4
	.align 2
_masks4:
	.data2 32639
	.data2 49087
	.data2 57311
	.data2 61423
	.data2 63479
	.data2 64507
	.data2 65021
	.data2 65278
	.extern	 _colours4
	.align 2
_colours4:
	.data2 0
	.data2 128
	.data2 32768
	.data2 32896
	.data2 0
	.data2 64
	.data2 16384
	.data2 16448
	.data2 0
	.data2 32
	.data2 8192
	.data2 8224
	.data2 0
	.data2 16
	.data2 4096
	.data2 4112
	.data2 0
	.data2 8
	.data2 2048
	.data2 2056
	.data2 0
	.data2 4
	.data2 1024
	.data2 1028
	.data2 0
	.data2 2
	.data2 512
	.data2 514
	.data2 0
	.data2 1
	.data2 256
	.data2 257
	.extern	 _shifts
_shifts:
	.data1 6
	.data1 4
	.data1 2
	.data1 0
	.extern	 _lineColourw
	.align 2
_lineColourw:
	.data2 0
	.data2 85
	.data2 170
	.data2 255
	.data2 43520
	.data2 43605
	.data2 43690
	.data2 43775
	.extern	 _lineColourl
	.align 2
_lineColourl:
	.data4 0
	.data4 5570645
	.data4 11141290
	.data4 16711935
	.data4 -1442797056
	.data4 -1437226411
	.data4 -1431655766
	.data4 -1426085121
	.align 2
	.extern	 _line
_line:
	lea -16(sp),sp
	movem.l a6/a5/a4/a3/a2/d7/d6/d5/d4/d3,-(sp)
	move.l 64(sp),d5
	move.l 68(sp),d6
	move.l 72(sp),d7
	move.l 76(sp),d4
	move.l 80(sp),a4
	cmp.l d6,d4
	bne L49
	move.l d7,d0
	sub.l d5,d0
	bpl L50
	neg.l d0
L50:
	moveq.l #7,d1
	cmp.l d0,d1
	bge L49
	cmp.l d5,d7
	bcc L51
	eor.l d7,d5
	eor.l d5,d7
	eor.l d7,d5
L51:
	move.l d5,d0
	moveq.l #3,d2
	and.l d2,d0
	moveq.l #2,d3
	cmp.l d0,d3
	beq L55
	bcs L61
	moveq.l #1,d4
	cmp.l d0,d4
	beq L53
	move.l d6,d3
	lsl.l #7,d3
	bra L52
	.align 2
L61:
	move.l d6,d3
	lsl.l #7,d3
	moveq.l #3,d1
	cmp.l d0,d1
	beq L57
	bra L52
	.align 2
L53:
	move.l d5,d1
	addq.l #1,d5
	move.l d6,d0
	lsl.l #7,d0
	move.l 60(sp),a2
	add.l d0,a2
	move.l d1,d0
	lsr.l #2,d0
	move.l d0,a1
	add.l d0,a1
	moveq.l #3,d2
	and.l d2,d1
	move.l d1,d0
	add.l d1,d0
	lea _masks,a0
	move.w 0(a1,a2.l),d2
	and.w 0(a0,d0.l),d2
	move.w a4,d3
	clr.l d0
	move.b d3,d0
	add.l d0,d0
	lsl.l #4,d1
	add.l d1,d0
	lea _colours,a0
	or.w 0(a0,d0.l),d2
	move.w d2,0(a1,a2.l)
L55:
	move.l d5,d1
	addq.l #1,d5
	move.l d6,d3
	lsl.l #7,d3
	move.l 60(sp),a2
	add.l d3,a2
	move.l d1,d0
	lsr.l #2,d0
	move.l d0,a1
	add.l d0,a1
	moveq.l #3,d4
	and.l d4,d1
	move.l d1,d0
	add.l d1,d0
	lea _masks,a0
	move.w 0(a1,a2.l),d2
	and.w 0(a0,d0.l),d2
	move.w a4,d4
	clr.l d0
	move.b d4,d0
	add.l d0,d0
	lsl.l #4,d1
	add.l d1,d0
	lea _colours,a0
	or.w 0(a0,d0.l),d2
	move.w d2,0(a1,a2.l)
L57:
	move.l d5,d1
	addq.l #1,d5
	move.l 60(sp),a2
	add.l d3,a2
	move.l d1,d0
	lsr.l #2,d0
	move.l d0,a1
	add.l d0,a1
	moveq.l #3,d0
	and.l d0,d1
	move.l d1,d0
	add.l d1,d0
	lea _masks,a0
	move.w 0(a1,a2.l),d2
	and.w 0(a0,d0.l),d2
	move.w a4,d4
	clr.l d0
	move.b d4,d0
	add.l d0,d0
	lsl.l #4,d1
	add.l d1,d0
	lea _colours,a0
	or.w 0(a0,d0.l),d2
	move.w d2,0(a1,a2.l)
L52:
	move.l d7,d0
	moveq.l #3,d1
	and.l d1,d0
	moveq.l #1,d2
	cmp.l d0,d2
	beq L65
	bhi L67
	moveq.l #2,d4
	cmp.l d0,d4
	bne L62
	move.l d7,d1
	subq.l #1,d7
	move.l 60(sp),a2
	add.l d3,a2
	move.l d1,d0
	lsr.l #2,d0
	move.l d0,a1
	add.l d0,a1
	moveq.l #3,d0
	and.l d0,d1
	move.l d1,d0
	add.l d1,d0
	lea _masks,a0
	move.w 0(a1,a2.l),d2
	and.w 0(a0,d0.l),d2
	move.w a4,d4
	clr.l d0
	move.b d4,d0
	add.l d0,d0
	lsl.l #4,d1
	add.l d1,d0
	lea _colours,a0
	or.w 0(a0,d0.l),d2
	move.w d2,0(a1,a2.l)
L65:
	move.l d7,d1
	subq.l #1,d7
	move.l 60(sp),a2
	add.l d3,a2
	move.l d1,d0
	lsr.l #2,d0
	move.l d0,a1
	add.l d0,a1
	moveq.l #3,d0
	and.l d0,d1
	move.l d1,d0
	add.l d1,d0
	lea _masks,a0
	move.w 0(a1,a2.l),d2
	and.w 0(a0,d0.l),d2
	move.w a4,d4
	clr.l d0
	move.b d4,d0
	add.l d0,d0
	lsl.l #4,d1
	add.l d1,d0
	lea _colours,a0
	or.w 0(a0,d0.l),d2
	move.w d2,0(a1,a2.l)
L67:
	move.l d7,d1
	subq.l #1,d7
	move.l 60(sp),a2
	add.l d3,a2
	move.l d1,d0
	lsr.l #2,d0
	move.l d0,a1
	add.l d0,a1
	moveq.l #3,d0
	and.l d0,d1
	move.l d1,d0
	add.l d1,d0
	lea _masks,a0
	move.w 0(a1,a2.l),d2
	and.w 0(a0,d0.l),d2
	move.w a4,d4
	clr.l d0
	move.b d4,d0
	add.l d0,d0
	lsl.l #4,d1
	add.l d1,d0
	lea _colours,a0
	or.w 0(a0,d0.l),d2
	move.w d2,0(a1,a2.l)
L62:
	btst #0,d7
	beq L71
	move.l d7,d0
	lsr.l #2,d0
	move.l d0,a2
	add.l d0,a2
	move.l 60(sp),a1
	add.l d3,a1
	move.l a4,d0
	add.l a4,d0
	lea _lineColourw,a0
	move.w 0(a0,d0.l),0(a1,a2.l)
	subq.l #4,d7
L71:
	move.l 60(sp),d1
	add.l d3,d1
	move.l d5,d0
	lsr.l #2,d0
	add.l d0,d0
	move.l d1,a1
	add.l d0,a1
	btst #0,d5
	beq L72
	move.l a4,d0
	add.l a4,d0
	lea _lineColourw,a0
	move.w 0(a0,d0.l),(a1)+
	addq.l #4,d5
L72:
	move.l a4,d0
	lsl.l #2,d0
	move.l d0,a4
	lea _lineColourl,a0
	move.l 0(a4,a0.l),d2
	cmp.l d7,d5
	bcc L79
	moveq.l #0,d3
	move.l d7,d0
	sub.l d5,d0
	lsr.l #3,d0
	cmp.l d3,d0
	bcs L79
	.align 2
L77:
	move.l d2,(a1)+
	addq.l #1,d3
	cmp.l d3,d0
	bcc L77
	bra L79
	.align 2
L49:
	cmp.l d5,d7
	bne L80
	move.l a4,d2
	add.l a4,d2
	move.l d5,d1
	moveq.l #3,d3
	and.l d3,d1
	move.l d1,d0
	lsl.l #4,d0
	add.l d0,d2
	lea _colours,a0
	move.w 0(a0,d2.l),d2
	add.l d1,d1
	lea _masks,a0
	move.w 0(a0,d1.l),d3
	cmp.l d4,d6
	bcc L81
	move.l d6,d0
	lsl.l #7,d0
	add.l 60(sp),d0
	lsr.l #2,d5
	move.l d5,d1
	add.l d5,d1
	move.l d0,a1
	add.l d1,a1
	cmp.l d6,d4
	bcs L79
	.align 2
L85:
	move.w (a1),d0
	and.w d3,d0
	or.w d2,d0
	move.w d0,(a1)
	lea 128(a1),a1
	addq.l #1,d6
	cmp.l d6,d4
	bcc L85
	bra L79
	.align 2
L81:
	move.l d4,d0
	lsl.l #7,d0
	add.l 60(sp),d0
	lsr.l #2,d5
	move.l d5,d1
	add.l d5,d1
	move.l d0,a1
	add.l d1,a1
	.align 2
L91:
	move.w (a1),d0
	and.w d3,d0
	or.w d2,d0
	move.w d0,(a1)
	lea 128(a1),a1
	addq.l #1,d4
	cmp.l d4,d6
	bcc L91
	bra L79
	.align 2
L80:
	sub.l a2,a2
	move.l d4,d2
	sub.l d6,d2
	move.l d7,d0
	sub.l d5,d0
	sub.l a5,a5
	move.l d2,d3
	bge L95
	neg.l d3
L95:
	move.l d0,d1
	bge L96
	neg.l d1
L96:
	cmp.l d3,d1
	bge L94
	eor.l d0,d2
	eor.l d2,d0
	eor.l d0,d2
	move.w #1,a2
L94:
	move.l d0,a3
	cmp.w #0,a3
	bge L97
	move.w #-1,a6
	move.l a6,48(sp)
	neg.l d0
	bra L98
	.align 2
L97:
	moveq.l #1,d1
	move.l d1,48(sp)
L98:
	tst.l d0
	bne L99
	clr.l 40(sp)
	bra L100
	.align 2
L99:
	swap d2
	clr.w d2
	move.l d0,-(sp)
	move.l d2,-(sp)
	bsr .GXldiv
	addq.l #8,sp
	move.l d0,40(sp)
L100:
	cmp.w #0,a2
	beq L101
	sub.l a2,a2
	lsl.l #7,d4
	move.l d4,44(sp)
	move.l d7,d4
	moveq.l #3,d2
	and.l d2,d4
	lsr.l #2,d7
	cmp.l a2,a3
	beq L108
	moveq.l #0,d3
	lsl.l #7,d6
	move.l 60(sp),a1
	add.l d6,a1
	move.l 48(sp),d6
	lsl.l #7,d6
	.align 2
L105:
	move.l a5,d1
	swap d1
	ext.l d1
	add.l d5,d1
	move.l d1,d0
	lsr.l #2,d0
	move.l d0,a0
	add.l d0,a0
	moveq.l #3,d0
	and.l d0,d1
	move.l d1,d0
	add.l d1,d0
	move.w 0(a0,a1.l),d2
	lea _masks,a6
	and.w 0(a6,d0.l),d2
	move.w a4,d0
	move.b d0,d3
	move.l d3,d0
	add.l d3,d0
	lsl.l #4,d1
	add.l d1,d0
	lea _colours,a6
	or.w 0(a6,d0.l),d2
	move.w d2,0(a0,a1.l)
	add.l 40(sp),a5
	add.l d6,a1
	add.l 48(sp),a2
	cmp.l a2,a3
	bne L105
	bra L108
	.align 2
L101:
	sub.l a2,a2
	lsl.l #7,d4
	move.l d4,44(sp)
	move.l d7,d4
	moveq.l #3,d0
	and.l d0,d4
	lsr.l #2,d7
	cmp.l a2,a3
	beq L108
	moveq.l #0,d3
	.align 2
L112:
	move.l a5,d0
	swap d0
	ext.l d0
	move.l d5,d1
	add.l a2,d1
	add.l d6,d0
	lsl.l #7,d0
	move.l 60(sp),a1
	add.l d0,a1
	move.l d1,d0
	lsr.l #2,d0
	move.l d0,a0
	add.l d0,a0
	moveq.l #3,d2
	and.l d2,d1
	move.l d1,d0
	add.l d1,d0
	move.w 0(a0,a1.l),d2
	lea _masks,a6
	and.w 0(a6,d0.l),d2
	move.w a4,d0
	move.b d0,d3
	move.l d3,d0
	add.l d3,d0
	lsl.l #4,d1
	add.l d1,d0
	lea _colours,a6
	or.w 0(a6,d0.l),d2
	move.w d2,0(a0,a1.l)
	add.l 40(sp),a5
	add.l 48(sp),a2
	cmp.l a2,a3
	bne L112
L108:
	move.l 60(sp),a1
	add.l 44(sp),a1
	move.l d7,a0
	add.l d7,a0
	move.l d4,d0
	add.l d4,d0
	move.w 0(a0,a1.l),d1
	lea _masks,a2
	and.w 0(a2,d0.l),d1
	move.w a4,d2
	clr.l d0
	move.b d2,d0
	add.l d0,d0
	lsl.l #4,d4
	add.l d4,d0
	lea _colours,a2
	or.w 0(a2,d0.l),d1
	move.w d1,0(a0,a1.l)
L79:
	movem.l (sp)+,d3/d4/d5/d6/d7/a2/a3/a4/a5/a6
	lea 16(sp),sp
	rts
	.align 2
	.extern	 _fillTriangle
_fillTriangle:
	lea -16(sp),sp
	movem.l a6/a5/a4/a3/a2/d7/d6/d5/d4/d3,-(sp)
	move.l 64(sp),d6
	move.l 68(sp),d7
	move.l 72(sp),a3
	move.l 76(sp),a4
	move.l 80(sp),a5
	move.l 84(sp),a6
	cmp.l d7,a4
	bge L131
	move.l a3,d0
	eor.l d0,d6
	move.l a3,d1
	eor.l d6,d1
	move.l d1,a3
	eor.l d1,d6
	move.l a4,d0
	eor.l d0,d7
	move.l a4,d1
	eor.l d7,d1
	move.l d1,a4
	eor.l d1,d7
L131:
	cmp.l d7,a6
	bge L132
	move.l a5,d0
	eor.l d0,d6
	move.l a5,d1
	eor.l d6,d1
	move.l d1,a5
	eor.l d1,d6
	move.l a6,d0
	eor.l d0,d7
	move.l a6,d1
	eor.l d7,d1
	move.l d1,a6
	eor.l d1,d7
L132:
	cmp.l a4,a6
	bge L133
	move.l a5,d0
	move.l a3,d1
	eor.l d1,d0
	move.l d0,a3
	move.l a5,d1
	eor.l d1,d0
	move.l d0,a5
	move.l a3,d1
	eor.l d1,d0
	move.l d0,a3
	move.l a6,d0
	move.l a4,d1
	eor.l d1,d0
	move.l d0,a4
	move.l a6,d1
	eor.l d1,d0
	move.l d0,a6
	move.l a4,d1
	eor.l d1,d0
	move.l d0,a4
L133:
	cmp.l a4,a6
	bne L134
	move.l d6,d5
	move.l a5,d4
	move.l a4,a2
	move.l a3,d0
	sub.l d5,d0
	lsl.l #7,d0
	move.l a2,d3
	sub.l d7,d3
	move.l d3,-(sp)
	move.l d0,-(sp)
	bsr .GXldiv
	addq.l #8,sp
	move.l d0,a4
	sub.l d5,d4
	lsl.l #7,d4
	move.l d3,-(sp)
	move.l d4,-(sp)
	bsr .GXldiv
	addq.l #8,sp
	move.l d0,a3
	lsl.l #7,d5
	move.l d5,d3
	move.l d7,d4
	cmp.l d4,a2
	bcs L141
	.align 2
L137:
	move.l 88(sp),-(sp)
	move.l d4,-(sp)
	move.l d5,d0
	lsr.l #7,d0
	move.l d0,-(sp)
	move.l d4,-(sp)
	move.l d3,d0
	lsr.l #7,d0
	move.l d0,-(sp)
	move.l 80(sp),-(sp)
	bsr _line
	add.l a4,d3
	add.l a3,d5
	lea 24(sp),sp
	addq.l #1,d4
	cmp.l d4,a2
	bcc L137
	bra L141
	.align 2
L134:
	cmp.l d7,a4
	bne L142
	move.l a3,d5
	move.l a5,d3
	move.l d7,a2
	move.l d3,d0
	sub.l d6,d0
	lsl.l #7,d0
	move.l a6,d4
	sub.l a2,d4
	move.l d4,-(sp)
	move.l d0,-(sp)
	bsr .GXldiv
	addq.l #8,sp
	move.l d0,d7
	move.l d3,d0
	sub.l d5,d0
	lsl.l #7,d0
	move.l d4,-(sp)
	move.l d0,-(sp)
	bsr .GXldiv
	addq.l #8,sp
	move.l d0,d6
	move.l d3,d4
	lsl.l #7,d4
	move.l d4,d5
	move.l a6,d3
	cmp.l d3,a2
	bcc L141
	.align 2
L145:
	move.l 88(sp),-(sp)
	move.l d3,-(sp)
	move.l d4,d0
	bge L146
	moveq.l #127,d0
	add.l d4,d0
L146:
	asr.l #7,d0
	move.l d0,-(sp)
	move.l d3,-(sp)
	move.l d5,d0
	bge L147
	moveq.l #127,d0
	add.l d5,d0
L147:
	asr.l #7,d0
	move.l d0,-(sp)
	move.l 80(sp),-(sp)
	bsr _line
	sub.l d7,d5
	sub.l d6,d4
	lea 24(sp),sp
	subq.l #1,d3
	cmp.l d3,a2
	bcs L145
	bra L141
	.align 2
L142:
	lea .GYsfltosf,a2
	move.l d6,-(sp)
	jsr (a2)
	addq.l #4,sp
	move.l d0,d4
	move.l a4,d0
	sub.l d7,d0
	move.l d0,-(sp)
	jsr (a2)
	addq.l #4,sp
	move.l d0,d3
	move.l a6,d1
	sub.l d7,d1
	move.l d1,-(sp)
	jsr (a2)
	move.l d0,(sp)
	move.l d3,-(sp)
	bsr .GYsfdiv
	addq.l #8,sp
	move.l d0,d3
	move.l a5,d0
	sub.l d6,d0
	move.l d0,-(sp)
	jsr (a2)
	move.l d0,(sp)
	move.l d3,-(sp)
	bsr .GYsfmul
	addq.w #4,sp
	move.l d0,(sp)
	move.l d4,-(sp)
	bsr .GYsfadd
	addq.w #4,sp
	move.l d0,(sp)
	bsr .GYsftol
	addq.l #4,sp
	move.l d0,48(sp)
	move.l d6,d4
	move.l a4,a2
	move.l a3,d0
	sub.l d4,d0
	lsl.l #7,d0
	move.l a2,d3
	sub.l d7,d3
	move.l d3,-(sp)
	move.l d0,-(sp)
	bsr .GXldiv
	addq.l #8,sp
	move.l d0,44(sp)
	move.l 48(sp),d0
	sub.l d4,d0
	lsl.l #7,d0
	move.l d3,-(sp)
	move.l d0,-(sp)
	bsr .GXldiv
	addq.l #8,sp
	move.l d0,40(sp)
	move.l d4,d3
	lsl.l #7,d3
	move.l d3,d5
	move.l d7,d4
	cmp.l d4,a2
	bcs L157
	.align 2
L154:
	move.l 88(sp),-(sp)
	move.l d4,-(sp)
	move.l d3,d0
	lsr.l #7,d0
	move.l d0,-(sp)
	move.l d4,-(sp)
	move.l d5,d0
	lsr.l #7,d0
	move.l d0,-(sp)
	move.l 80(sp),-(sp)
	bsr _line
	add.l 68(sp),d5
	add.l 64(sp),d3
	lea 24(sp),sp
	addq.l #1,d4
	cmp.l d4,a2
	bcc L154
L157:
	move.l a5,d3
	move.l a4,d6
	move.l d3,d0
	sub.l a3,d0
	lsl.l #7,d0
	move.l a6,d4
	sub.l d6,d4
	move.l d4,-(sp)
	move.l d0,-(sp)
	bsr .GXldiv
	addq.l #8,sp
	move.l d0,a2
	move.l d3,d0
	sub.l 48(sp),d0
	lsl.l #7,d0
	move.l d4,-(sp)
	move.l d0,-(sp)
	bsr .GXldiv
	addq.l #8,sp
	move.l d0,d7
	move.l d3,d4
	lsl.l #7,d4
	move.l d4,d5
	move.l a6,d3
	cmp.l d3,d6
	bcc L141
	.align 2
L160:
	move.l 88(sp),-(sp)
	move.l d3,-(sp)
	move.l d4,d0
	bge L161
	moveq.l #127,d0
	add.l d4,d0
L161:
	asr.l #7,d0
	move.l d0,-(sp)
	move.l d3,-(sp)
	move.l d5,d0
	bge L162
	moveq.l #127,d0
	add.l d5,d0
L162:
	asr.l #7,d0
	move.l d0,-(sp)
	move.l 80(sp),-(sp)
	bsr _line
	sub.l a2,d5
	sub.l d7,d4
	lea 24(sp),sp
	subq.l #1,d3
	cmp.l d3,d6
	bcs L160
L141:
	movem.l (sp)+,d3/d4/d5/d6/d7/a2/a3/a4/a5/a6
	lea 16(sp),sp
	rts
	.align 2
	.extern	 _fill
_fill:
	move.l 8(sp),d0
	clr.l d2
	move.b 17(sp),d2
	move.l 12(sp),d1
	sub.l d0,d1
	lsl.l #7,d1
	move.l d1,-(sp)
	move.l d2,-(sp)
	lsl.l #7,d0
	add.l 12(sp),d0
	move.l d0,-(sp)
	bsr _memset
	lea 12(sp),sp
	rts
	nop
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
	.align 2
	.extern	 _plot4
_plot4:
	move.l a2,-(sp)
	move.l 12(sp),d1
	move.l 16(sp),d0
	lsl.l #7,d0
	move.l 8(sp),a2
	add.l d0,a2
	move.l d1,d0
	lsr.l #3,d0
	move.l d0,a1
	add.l d0,a1
	moveq.l #7,d0
	and.l d0,d1
	move.l d1,d0
	add.l d1,d0
	lea _masks4,a0
	move.w 0(a1,a2.l),d2
	and.w 0(a0,d0.l),d2
	clr.l d0
	move.b 21(sp),d0
	add.l d0,d0
	lsl.l #3,d1
	add.l d1,d0
	lea _colours4,a0
	or.w 0(a0,d0.l),d2
	move.w d2,0(a1,a2.l)
	move.l (sp)+,a2
	rts
	.align 2
	.extern	 _unplot
_unplot:
	move.w 8(sp),d2
	clr.l d1
	move.w 10(sp),d1
	move.w d2,d0
	lsr.w #2,d0
	and.l #16383,d0
	move.l d0,a1
	add.l d0,a1
	lsl.l #7,d1
	move.l d1,a0
	add.l 4(sp),a0
	clr.l d1
	move.w 0(a0,a1.l),d1
	moveq.l #3,d0
	and.l d0,d2
	move.l d2,d0
	add.l d2,d0
	lea _masks,a0
	move.w 0(a0,d0.l),d0
	and.l #0xFFFF,d0
	not.l d0
	and.l d0,d1
	lea _shifts,a0
	clr.l d0
	move.b 0(a0,d2.l),d0
	asr.l d0,d1
	moveq.l #3,d0
	and.l d1,d0
	cmp.w #256,d1
	bls L15
	addq.l #4,d0
L15:
	rts
	nop
	.align 2
	.extern	 _box
_box:
	movem.l a2/d7/d6/d5/d4/d3,-(sp)
	move.l 32(sp),d7
	move.l 36(sp),d5
	move.l 40(sp),d3
	move.l 44(sp),d6
	move.l 48(sp),d4
	move.l d4,-(sp)
	move.l d5,-(sp)
	move.l d3,-(sp)
	move.l d5,-(sp)
	move.l d7,-(sp)
	move.l _SCREEN,-(sp)
	lea _line,a2
	jsr (a2)
	move.l d4,-(sp)
	move.l d6,-(sp)
	move.l d3,-(sp)
	move.l d5,-(sp)
	move.l d3,-(sp)
	move.l _SCREEN,-(sp)
	jsr (a2)
	lea 44(sp),sp
	move.l d4,(sp)
	move.l d6,-(sp)
	move.l d7,-(sp)
	move.l d6,-(sp)
	move.l d3,-(sp)
	move.l _SCREEN,-(sp)
	jsr (a2)
	move.l d4,-(sp)
	move.l d5,-(sp)
	move.l d7,-(sp)
	move.l d6,-(sp)
	move.l d7,-(sp)
	move.l _SCREEN,-(sp)
	jsr (a2)
	lea 48(sp),sp
	movem.l (sp)+,d3/d4/d5/d6/d7/a2
	rts
	.align 2
	.extern	 _fillBox
_fillBox:
	movem.l a2/d7/d6/d5/d4/d3,-(sp)
	move.l 28(sp),a2
	move.l 32(sp),d7
	move.l 36(sp),d3
	move.l 40(sp),d6
	move.l 44(sp),d4
	move.l 48(sp),d5
	cmp.l d3,d4
	bcs L19
	.align 2
L21:
	move.l d5,-(sp)
	move.l d3,-(sp)
	move.l d6,-(sp)
	move.l d3,-(sp)
	move.l d7,-(sp)
	move.l a2,-(sp)
	bsr _line
	lea 24(sp),sp
	addq.l #1,d3
	cmp.l d3,d4
	bcc L21
L19:
	movem.l (sp)+,d3/d4/d5/d6/d7/a2
	rts
	.align 2
	.extern	 _copyBox
_copyBox:
	movem.l a6/a5/a4/a3/a2/d7/d6/d5/d4/d3,-(sp)
	move.l 52(sp),d1
	cmp.l 60(sp),d1
	bhi L25
	sub.l a4,a4
	.align 2
L27:
	move.l 56(sp),a2
	move.l d1,a6
	addq.l #1,a6
	cmp.l 64(sp),a2
	bhi L26
	move.w d1,d0
	moveq.l #0,d7
	move.w d0,d3
	lsr.w #2,d3
	moveq.l #0,d4
	and.w #3,d0
	move.w d0,a5
	moveq.l #0,d2
	moveq.l #0,d6
	moveq.l #0,d5
	lsl.l #2,d1
	move.l d1,a3
	.align 2
L31:
	move.w a2,d7
	move.w d3,d4
	move.l d4,a1
	add.l d4,a1
	move.l d7,d0
	lsl.l #7,d0
	move.l 44(sp),a0
	add.l d0,a0
	move.l a4,d0
	move.w 0(a0,a1.l),d0
	move.l d0,a4
	move.w a5,d2
	move.l d2,d0
	add.l d2,d0
	lea _masks,a0
	move.w 0(a0,d0.l),d6
	move.l d6,d1
	not.l d1
	move.l a4,d0
	and.l d1,d0
	lea _shifts,a0
	move.b 0(a0,d2.l),d5
	asr.l d5,d0
	moveq.l #3,d1
	and.l d0,d1
	cmp.w #256,d0
	bls L32
	addq.l #4,d1
L32:
	move.l 48(sp),d0
	move.l 0(a3,d0.l),a0
	move.b d1,0(a2,a0.l)
	addq.l #1,a2
	cmp.l 64(sp),a2
	bls L31
L26:
	move.l a6,d1
	cmp.l 60(sp),d1
	bls L27
L25:
	movem.l (sp)+,d3/d4/d5/d6/d7/a2/a3/a4/a5/a6
	rts
	.align 2
	.extern	 _drawBox
_drawBox:
	subq.w #8,sp
	movem.l a6/a5/a4/a3/a2/d7/d6/d5/d4/d3,-(sp)
	move.l 56(sp),a6
	move.l 64(sp),d1
	move.l 68(sp),a5
	move.l 72(sp),d7
	moveq.l #0,d0
	cmp.l d0,a5
	bcs L38
	lsl.l #7,d1
	add.l 52(sp),d1
	move.l d1,40(sp)
	.align 2
L40:
	sub.l a2,a2
	move.l d0,d6
	addq.l #1,d6
	cmp.l a2,d7
	bcs L39
	move.l d0,d2
	lsl.l #2,d2
	add.l 60(sp),d0
	move.l d0,d1
	lsr.l #2,d1
	moveq.l #3,d3
	and.l d3,d0
	move.l d0,d5
	add.l d0,d5
	lea _masks,a4
	moveq.l #0,d3
	move.l d0,d4
	lsl.l #4,d4
	move.l 40(sp),d0
	add.l d1,d0
	move.l d0,a1
	add.l d1,a1
	lea _colours,a3
	.align 2
L44:
	move.l 0(a6,d2.l),a0
	move.w (a1),d1
	and.w 0(a4,d5.l),d1
	move.b 0(a2,a0.l),d3
	move.l d3,d0
	add.l d3,d0
	add.l d4,d0
	or.w 0(a3,d0.l),d1
	move.w d1,(a1)
	lea 128(a1),a1
	addq.l #1,a2
	cmp.l a2,d7
	bcc L44
L39:
	move.l d6,d0
	cmp.l d0,a5
	bcc L40
L38:
	movem.l (sp)+,d3/d4/d5/d6/d7/a2/a3/a4/a5/a6
	addq.w #8,sp
	rts
	.align 2
	.extern	 _triangle
_triangle:
	movem.l a5/a4/a3/a2/d7/d6/d5/d4/d3,-(sp)
	move.l 40(sp),d4
	move.l 44(sp),a5
	move.l 48(sp),a4
	move.l 52(sp),d6
	move.l 56(sp),d5
	move.l 60(sp),a3
	move.l 64(sp),d7
	move.l 68(sp),d3
	move.l d3,-(sp)
	move.l d5,-(sp)
	move.l d6,-(sp)
	move.l a4,-(sp)
	move.l a5,-(sp)
	move.l d4,-(sp)
	lea _line,a2
	jsr (a2)
	move.l d3,-(sp)
	move.l d7,-(sp)
	move.l a3,-(sp)
	move.l d5,-(sp)
	move.l d6,-(sp)
	move.l d4,-(sp)
	jsr (a2)
	lea 44(sp),sp
	move.l d3,(sp)
	move.l d7,-(sp)
	move.l a3,-(sp)
	move.l a4,-(sp)
	move.l a5,-(sp)
	move.l d4,-(sp)
	jsr (a2)
	lea 24(sp),sp
	movem.l (sp)+,d3/d4/d5/d6/d7/a2/a3/a4/a5
	rts
	.align 2
	.extern	 _cls
_cls:
	move.l #32768,-(sp)
	move.l 8(sp),-(sp)
	bsr _bzero
	addq.l #8,sp
	rts
	nop
	.align 2
	.extern	 _peek
_peek:
	move.l 8(sp),d1
	move.l 12(sp),d2
	lsl.l #6,d1
	move.l d2,d0
	lsr.l #2,d0
	add.l d0,d1
	add.l d1,d1
	move.l 4(sp),a0
	add.l d1,a0
	move.w (a0),d0
	moveq.l #3,d1
	and.l d1,d2
	moveq.l #1,d1
	cmp.l d2,d1
	beq L8
	bhi L9
	moveq.l #2,d1
	cmp.l d2,d1
	beq L7
	moveq.l #3,d1
	cmp.l d2,d1
	bne L4
	and.l #515,d0
	rts
	.align 2
L7:
	and.l #2060,d0
	rts
	.align 2
L8:
	and.l #8240,d0
	rts
	.align 2
L9:
	and.l #32960,d0
L4:
	rts
	nop
	.align 2
	.extern	 _fillBottomFlatTriangle
_fillBottomFlatTriangle:
	movem.l a5/a4/a3/a2/d7/d6/d5/d4/d3,-(sp)
	move.l 40(sp),a5
	move.l 44(sp),d4
	move.l 48(sp),d5
	move.l 56(sp),d7
	move.l 60(sp),d3
	move.l 64(sp),d6
	move.l 68(sp),a4
	move.l 52(sp),d0
	sub.l d4,d0
	lsl.l #7,d0
	lea .GXldiv,a2
	move.l d7,d1
	sub.l d5,d1
	move.l d1,-(sp)
	move.l d0,-(sp)
	jsr (a2)
	addq.l #8,sp
	move.l d0,a3
	sub.l d4,d3
	lsl.l #7,d3
	sub.l d5,d6
	move.l d6,-(sp)
	move.l d3,-(sp)
	jsr (a2)
	addq.l #8,sp
	move.l d0,d6
	lsl.l #7,d4
	move.l d4,d3
	cmp.l d5,d7
	bcs L118
	.align 2
L120:
	move.l a4,-(sp)
	move.l d5,-(sp)
	move.l d4,d0
	lsr.l #7,d0
	move.l d0,-(sp)
	move.l d5,-(sp)
	move.l d3,d0
	lsr.l #7,d0
	move.l d0,-(sp)
	move.l a5,-(sp)
	bsr _line
	add.l a3,d3
	add.l d6,d4
	lea 24(sp),sp
	addq.l #1,d5
	cmp.l d5,d7
	bcc L120
L118:
	movem.l (sp)+,d3/d4/d5/d6/d7/a2/a3/a4/a5
	rts
	.align 2
	.extern	 _fillTopFlatTriangle
_fillTopFlatTriangle:
	movem.l a5/a4/a3/a2/d7/d6/d5/d4/d3,-(sp)
	move.l 40(sp),a5
	move.l 48(sp),d7
	move.l 52(sp),d5
	move.l 56(sp),d6
	move.l 60(sp),d3
	move.l 64(sp),d4
	move.l 68(sp),a4
	move.l d3,d0
	sub.l 44(sp),d0
	lsl.l #7,d0
	lea .GXldiv,a2
	move.l d4,d1
	sub.l d7,d1
	move.l d1,-(sp)
	move.l d0,-(sp)
	jsr (a2)
	addq.l #8,sp
	move.l d0,a3
	move.l d3,d0
	sub.l d5,d0
	lsl.l #7,d0
	move.l d4,d1
	sub.l d6,d1
	move.l d1,-(sp)
	move.l d0,-(sp)
	jsr (a2)
	addq.l #8,sp
	move.l d0,d6
	lsl.l #7,d3
	move.l d3,d5
	cmp.l d4,d7
	bcc L124
	.align 2
L126:
	move.l a4,-(sp)
	move.l d4,-(sp)
	move.l d3,d0
	bge L127
	moveq.l #127,d0
	add.l d3,d0
L127:
	asr.l #7,d0
	move.l d0,-(sp)
	move.l d4,-(sp)
	move.l d5,d0
	bge L128
	moveq.l #127,d0
	add.l d5,d0
L128:
	asr.l #7,d0
	move.l d0,-(sp)
	move.l a5,-(sp)
	bsr _line
	sub.l a3,d5
	sub.l d6,d3
	lea 24(sp),sp
	subq.l #1,d4
	cmp.l d4,d7
	bcs L126
L124:
	movem.l (sp)+,d3/d4/d5/d6/d7/a2/a3/a4/a5
	rts
