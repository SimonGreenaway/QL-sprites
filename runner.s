	.sect	.text
	.sect	.rom
	.sect	.data
	.sect	.bss

;gcc2_compiled
	.extern	 _frames2
	.sect	.data
	.align 2
_frames2:
	.data4 0
	.extern	 _list
	.align 2
_list:
	.data4 0
	.sect	.text
	.align 2
	.extern	 _interruptRunner
_interruptRunner:
	move.l a2,-(sp)
	move.l d3,-(sp)
	move.l _list,a2
	addq.l #1,_frames2
	cmp.w #0,a2
	beq L10
	moveq.l #0,d3
	.align 2
L11:
	tst.l 36(a2)
	beq L12
	move.l 104(a2),d0
	cmp.l _frames2,d0
	bhi L12
	tst.l 124(a2)
	bne L14
	move.l a2,-(sp)
	move.l 124(a2),a0
	jsr (a0)
	addq.l #4,sp
	bra L15
	.align 2
L14:
	tst.l 84(a2)
	bne L17
	tst.l 88(a2)
	beq L15
L17:
	clr.l 100(a2)
	move.l a2,-(sp)
	move.l _SCREEN,-(sp)
	bsr _spritePlot
	move.l 76(a2),d1
	add.l 84(a2),d1
	move.l d1,76(a2)
	move.l 80(a2),d2
	add.l 88(a2),d2
	move.l d2,80(a2)
	moveq.l #1,d0
	move.l d0,100(a2)
	move.l 92(a2),d0
	lsl.l #2,d0
	move.l 44(a2,d0.l),a0
	move.w 6(a0),d3
	move.l d1,d0
	add.l d3,d0
	addq.l #8,sp
	cmp.l #254,d0
	bgt L19
	tst.l d1
	blt L19
	tst.l d2
	blt L19
	clr.l d0
	move.w 4(a0),d0
	add.l d2,d0
	cmp.l #254,d0
	ble L15
L19:
	clr.l 36(a2)
L15:
	move.l _frames2,d0
	add.l 108(a2),d0
	move.l d0,104(a2)
	tst.l 36(a2)
	beq L12
	move.l a2,-(sp)
	move.l _SCREEN,-(sp)
	bsr _spritePlot
	addq.l #8,sp
L12:
	move.l 120(a2),a2
	cmp.w #0,a2
	bne L11
L10:
	move.l (sp)+,d3
	move.l (sp)+,a2
	rts
LC0:
	.data1	0x74,0x65,0x73,0x74,0x5f,0x6c,0x69,0x62,0x0
LC1:
	.data1	0x74,0x65,0x73,0x74,0x0
	.align 2
	.extern	 _main
_main:
	link a6,#-2160
	movem.l a5/a4/a3/a2/d7/d6/d5/d4/d3,-(sp)
	bsr ___main
	bsr _init
	pea 1
	pea LC0
	pea -2120(a6)
	bsr _loadLibrary
	moveq.l #0,d6
	lea 12(sp),sp
	lea -2112(a6),a0
	move.l a0,-2124(a6)
	lea -2076(a6),a0
	move.l a0,-2140(a6)
	lea -2016(a6),a0
	move.l a0,-2144(a6)
	lea -2012(a6),a0
	move.l a0,-2148(a6)
	lea -2020(a6),a2
	lea -2008(a6),a0
	move.l a0,-2152(a6)
	lea -2004(a6),a0
	move.l a0,-2156(a6)
	lea _rand,a3
	lea -2036(a6),a0
	move.l a0,-2160(a6)
	lea -2068(a6),a4
	lea -2032(a6),a5
	lea -2028(a6),a0
	move.l a0,-2132(a6)
	lea -2024(a6),a0
	move.l a0,-2136(a6)
	lea -1988(a6),a0
	move.l a0,-2128(a6)
	.align 2
L50:
	pea LC1
	move.l d6,d3
	lsl.l #5,d3
	move.l d3,d4
	add.l d6,d4
	lsl.l #2,d4
	move.l -2124(a6),d5
	add.l d4,d5
	move.l d5,-(sp)
	bsr _spriteSetup
	pea 3
	pea -2120(a6)
	move.l d5,-(sp)
	bsr _spriteAddImage
	moveq.l #1,d0
	move.l -2140(a6),a0
	move.l d0,0(a0,d4.l)
	move.l -2144(a6),a0
	move.l d0,0(a0,d4.l)
	move.l -2148(a6),a0
	move.l d0,0(a0,d4.l)
	clr.l 0(a2,d4.l)
	move.l -2152(a6),a0
	clr.l 0(a0,d4.l)
	moveq.l #5,d0
	move.l -2156(a6),a0
	move.l d0,0(a0,d4.l)
	lea 20(sp),sp
	move.l d6,d7
	addq.l #1,d7
	moveq.l #0,d5
	.align 2
L54:
	jsr (a3)
	and.l #0xFF,d0
	move.l -2160(a6),a0
	move.l d0,0(a0,d4.l)
	move.l 0(a2,d4.l),d1
	lsl.l #2,d1
	add.l d4,d1
	move.l 0(a4,d1.l),a0
	move.w 6(a0),d5
	add.l d5,d0
	cmp.l #254,d0
	bgt L54
	move.l d3,d4
	add.l d6,d4
	lsl.l #2,d4
	moveq.l #0,d5
	.align 2
L58:
	jsr (a3)
	and.l #0xFF,d0
	move.l d0,0(a5,d4.l)
	move.l 0(a2,d4.l),d1
	lsl.l #2,d1
	add.l d4,d1
	move.l 0(a4,d1.l),a0
	move.w 4(a0),d5
	add.l d5,d0
	cmp.l #254,d0
	bgt L58
	add.l d6,d3
	lsl.l #2,d3
	jsr (a3)
	moveq.l #-1,d1
	btst #0,d0
	beq L59
	moveq.l #1,d1
L59:
	move.l -2132(a6),a0
	move.l d1,0(a0,d3.l)
	jsr (a3)
	moveq.l #-1,d1
	btst #0,d0
	beq L61
	moveq.l #1,d1
L61:
	move.l -2136(a6),a0
	move.l d1,0(a0,d3.l)
	move.l -2128(a6),a0
	move.l #_m,0(a0,d3.l)
	lea 0(a6,d3.l),a0
	lea -2112(a0),a0
	move.l _list,120(a0)
	move.l a0,_list
	move.l d7,d6
	moveq.l #15,d0
	cmp.l d6,d0
	bcc L50
	move.l #_interruptRunner,_t2+4
	pea _t2
	bsr __sms_lpol
L70:
	move.l #1000,(sp)
	bsr _sleep
	bra L70
	nop
	.align 2
	.extern	 _addSprite
_addSprite:
	move.l 4(sp),a0
	move.l _list,120(a0)
	move.l a0,_list
	rts
	nop
	.align 2
	.extern	 _clearSprites
_clearSprites:
	movem.l a3/a2/d3,-(sp)
	move.l _list,a3
	cmp.w #0,a3
	beq L25
	.align 2
L26:
	move.l a3,a2
	move.l 120(a3),a3
	tst.l 36(a3)
	beq L27
	move.l 100(a2),d3
	clr.l 100(a2)
	move.l a2,-(sp)
	move.l _SCREEN,-(sp)
	bsr _spritePlot
	move.l d3,100(a2)
	addq.l #8,sp
L27:
	move.l a3,-(sp)
	bsr _free
	addq.l #4,sp
	cmp.w #0,a3
	bne L26
L25:
	clr.l _list
	movem.l (sp)+,d3/a2/a3
	rts
	.align 2
	.extern	 _removeSprite
_removeSprite:
	move.l a2,-(sp)
	move.l 8(sp),d0
	move.l _list,a2
	sub.l a0,a0
	cmp.w #0,a2
	beq L29
	.align 2
L32:
	cmp.l a2,d0
	bne L33
	cmp.w #0,a0
	bne L34
	move.l 120(a2),_list
	bra L36
	.align 2
L34:
	move.l 120(a2),120(a0)
	tst.l 36(a2)
	beq L36
	moveq.l #1,d0
	move.l d0,100(a2)
	move.l a2,-(sp)
	move.l _SCREEN,-(sp)
	bsr _spritePlot
	addq.l #8,sp
L36:
	move.l a2,-(sp)
	bsr _free
	addq.l #4,sp
	bra L29
	.align 2
L33:
	move.l a2,a0
	move.l 120(a2),a2
	cmp.w #0,a2
	bne L32
L29:
	move.l (sp)+,a2
	rts
	.sect	.bss
	.extern	_t2
_t2:
	.space	8
	.sect	.text
	.align 2
	.extern	 _runner
_runner:
	lea _t2+4,a0
	move.l #_interruptRunner,(a0)
	pea -4(a0)
	bsr __sms_lpol
	addq.l #4,sp
	rts
	nop
	.align 2
	.extern	 _m
_m:
	move.l a2,-(sp)
	move.l 8(sp),a2
	move.l 76(a2),d1
	moveq.l #1,d0
	tst.l d1
	beq L71
	move.l 92(a2),d0
	lsl.l #2,d0
	move.l 44(a2,d0.l),a0
	clr.l d0
	move.w 6(a0),d0
	moveq.l #0,d2
	not.b d2
	sub.l d0,d2
	move.l d2,d0
	cmp.l d1,d0
	bgt L41
	moveq.l #-1,d0
L71:
	move.l d0,84(a2)
L41:
	move.l 80(a2),d1
	bne L43
	moveq.l #1,d2
	move.l d2,88(a2)
	bra L44
	.align 2
L43:
	move.l 92(a2),d0
	lsl.l #2,d0
	move.l 44(a2,d0.l),a0
	clr.l d0
	move.w 4(a0),d0
	moveq.l #0,d2
	not.b d2
	sub.l d0,d2
	move.l d2,d0
	cmp.l d1,d0
	bgt L44
	moveq.l #-1,d0
	move.l d0,88(a2)
L44:
	clr.l 100(a2)
	move.l a2,-(sp)
	move.l _SCREEN,-(sp)
	bsr _spritePlot
	move.l 84(a2),d2
	add.l d2,76(a2)
	move.l 88(a2),d0
	add.l d0,80(a2)
	moveq.l #1,d2
	move.l d2,100(a2)
	addq.l #8,sp
	move.l (sp)+,a2
	rts
