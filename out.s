	.data
	.global c
c:
	.word 0
	.data
	.global chas
chas:
	.zero 40000
	.data
	.global chat
chat:
	.word 0
	.data
	.global get
get:
	.zero 40000
	.data
	.global get2
get2:
	.zero 40000
	.data
	.global i
i:
	.word 0
	.data
	.global ii
ii:
	.word 1
	.data
	.global ints
ints:
	.zero 40000
	.data
	.global intt
intt:
	.word 0
	.text
	.global isdigit
isdigit:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	li	a1,48
	bge	a0,a1, .L5
	j	.L4
.L5:
	li	a1,57
	ble	a0,a1, .L2
	j	.L4
.L2:
	li	a0,1
	j	.L6
.L6:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
.L4:
	li	a0,0
	j	.L6
	.text
	.global power
power:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	li	a2,1
	j	.L8
.L8:
	bnez	a1, .L9
	j	.L10
.L9:
	mul	a2,a2,a0
	addi	a1,a1,-1
	j	.L8
.L10:
	mv	a0,a2
	j	.L11
.L11:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
	.text
	.global getstr
getstr:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	sd	s2,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,32
	mv	s1,a0
	call	getch
	mv	a1,a0
	mv	a0,s1
	li	a2,0
	mv	a3,a2
	j	.L13
.L13:
	li	a2,13
	bne	a1,a2, .L16
	j	.L15
.L16:
	li	a2,10
	bne	a1,a2, .L14
	j	.L15
.L14:
	addi	a2,a3,0
	slli	a2,a2,2
	addi	a2,a2,0
	add	a2,a0,a2
	sw	a1,0(a2)
	addi	a1,a3,1
	mv	s2,a0
	mv	s1,a1
	call	getch
	mv	a1,a0
	mv	a0,s2
	mv	a3,s1
	j	.L13
.L15:
	mv	a0,a3
	j	.L17
.L17:
	ld	s1,0(sp)
	ld	s2,8(sp)
	ld	s0,16(sp)
	ld	ra,24(sp)
	addi	sp,sp,32
	ret
	.text
	.global intpush
intpush:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	la	a1,intt
	lw	a1,0(a1)
	addi	a1,a1,1
	la	a2,intt
	sw	a1,0(a2)
	la	a1,intt
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a1,a1,2
	la	a2,ints
	addi	a1,a1,0
	add	a1,a2,a1
	sw	a0,0(a1)
	ret
	.text
	.global chapush
chapush:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	la	a1,chat
	lw	a1,0(a1)
	addi	a1,a1,1
	la	a2,chat
	sw	a1,0(a2)
	la	a1,chat
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a1,a1,2
	la	a2,chas
	addi	a1,a1,0
	add	a1,a2,a1
	sw	a0,0(a1)
	ret
	.text
	.global intpop
intpop:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	la	a0,intt
	lw	a0,0(a0)
	addi	a0,a0,-1
	la	a1,intt
	sw	a0,0(a1)
	la	a0,intt
	lw	a0,0(a0)
	addi	a0,a0,1
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,ints
	addi	a1,a1,0
	add	a0,a0,a1
	lw	a0,0(a0)
	j	.L21
.L21:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
	.text
	.global chapop
chapop:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,-1
	la	a1,chat
	sw	a0,0(a1)
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,1
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,chas
	addi	a1,a1,0
	add	a0,a0,a1
	lw	a0,0(a0)
	j	.L23
.L23:
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	ret
	.text
	.global intadd
intadd:
	addi	sp,sp,-8
	sd	s0,0(sp)
	addi	s0,sp,8
	addi	sp,sp,-8
	addi	sp,sp,8
	ld	s0,0(sp)
	addi	sp,sp,8
	la	a1,intt
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a1,a1,2
	la	a2,ints
	addi	a1,a1,0
	add	a1,a2,a1
	li	a2,10
	lw	a1,0(a1)
	mul	a2,a1,a2
	la	a1,intt
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a3,a1,2
	la	a1,ints
	addi	a3,a3,0
	add	a1,a1,a3
	sw	a2,0(a1)
	la	a1,intt
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a1,a1,2
	la	a2,ints
	addi	a1,a1,0
	add	a1,a2,a1
	lw	a1,0(a1)
	add	a0,a1,a0
	la	a1,intt
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a1,a1,2
	la	a2,ints
	addi	a1,a1,0
	add	a1,a2,a1
	sw	a0,0(a1)
	ret
	.text
	.global find
find:
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	call	chapop
	la	a1,c
	sw	a0,0(a1)
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,get2
	addi	a1,a1,0
	add	a1,a0,a1
	li	a0,32
	sw	a0,0(a1)
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,1
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a1,a1,a0
	la	a0,c
	lw	a0,0(a0)
	sw	a0,0(a1)
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,2
	mv	a1,a0
	la	a0,ii
	sw	a1,0(a0)
	la	a0,chat
	lw	a0,0(a0)
	beqz	a0, .L26
	j	.L28
.L26:
	li	a0,0
	j	.L29
.L29:
	ld	s0,0(sp)
	ld	ra,8(sp)
	addi	sp,sp,16
	ret
.L28:
	li	a0,1
	j	.L29
	.text
	.global main
main:
	addi	sp,sp,-24
	sd	ra,16(sp)
	sd	s0,8(sp)
	sd	s1,0(sp)
	addi	s0,sp,24
	addi	sp,sp,-8
	li	a0,0
	la	a1,intt
	sw	a0,0(a1)
	li	a0,0
	la	a1,chat
	sw	a0,0(a1)
	la	a0,get
	addi	a0,a0,0
	call	getstr
	mv	s1,a0
	j	.L31
.L31:
	la	a0,i
	lw	a0,0(a0)
	blt	a0,s1, .L32
	j	.L113
.L32:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,get
	addi	a1,a1,0
	add	a0,a0,a1
	lw	a0,0(a0)
	call	isdigit
	li	a1,1
	beq	a0,a1, .L34
	j	.L35
.L34:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get
	addi	a0,a0,0
	add	a1,a1,a0
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a2,get2
	addi	a0,a0,0
	add	a0,a2,a0
	lw	a1,0(a1)
	sw	a1,0(a0)
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,1
	mv	a1,a0
	la	a0,ii
	sw	a1,0(a0)
	j	.L36
.L36:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,1
	la	a1,i
	sw	a0,0(a1)
	j	.L31
.L35:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,40
	lw	a0,0(a0)
	beq	a0,a1, .L37
	j	.L39
.L37:
	li	a0,40
	call	chapush
	j	.L39
.L39:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,94
	lw	a0,0(a0)
	beq	a0,a1, .L40
	j	.L42
.L40:
	li	a0,94
	call	chapush
	j	.L42
.L42:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,get
	addi	a1,a1,0
	add	a0,a0,a1
	li	a1,41
	lw	a0,0(a0)
	beq	a0,a1, .L43
	j	.L45
.L43:
	call	chapop
	mv	a1,a0
	la	a0,c
	sw	a1,0(a0)
	j	.L46
.L46:
	li	a1,40
	la	a0,c
	lw	a0,0(a0)
	bne	a0,a1, .L47
	j	.L45
.L47:
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,32
	sw	a1,0(a0)
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,1
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a1,a1,a0
	la	a0,c
	lw	a0,0(a0)
	sw	a0,0(a1)
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,2
	la	a1,ii
	sw	a0,0(a1)
	call	chapop
	la	a1,c
	sw	a0,0(a1)
	j	.L46
.L45:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,get
	addi	a1,a1,0
	add	a0,a0,a1
	li	a1,43
	lw	a0,0(a0)
	beq	a0,a1, .L52
	j	.L51
.L52:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,43
	lw	a1,0(a1)
	beq	a1,a0, .L53
	j	.L59
.L53:
	call	find
	beqz	a0, .L54
	j	.L52
.L54:
	li	a0,43
	call	chapush
	j	.L51
.L51:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,45
	lw	a0,0(a0)
	beq	a0,a1, .L66
	j	.L65
.L66:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,43
	lw	a0,0(a0)
	beq	a0,a1, .L67
	j	.L73
.L67:
	call	find
	beqz	a0, .L68
	j	.L66
.L68:
	li	a0,45
	call	chapush
	j	.L65
.L65:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,42
	lw	a0,0(a0)
	beq	a0,a1, .L80
	j	.L79
.L80:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,42
	lw	a0,0(a0)
	beq	a0,a1, .L81
	j	.L85
.L81:
	call	find
	beqz	a0, .L82
	j	.L80
.L82:
	li	a0,42
	call	chapush
	j	.L79
.L79:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,47
	lw	a0,0(a0)
	beq	a0,a1, .L92
	j	.L91
.L92:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,chas
	addi	a1,a1,0
	add	a1,a0,a1
	li	a0,42
	lw	a1,0(a1)
	beq	a1,a0, .L93
	j	.L97
.L93:
	call	find
	beqz	a0, .L94
	j	.L92
.L94:
	li	a0,47
	call	chapush
	j	.L91
.L91:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,37
	lw	a1,0(a1)
	beq	a1,a0, .L104
	j	.L103
.L104:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,chas
	addi	a1,a1,0
	add	a0,a0,a1
	li	a1,42
	lw	a0,0(a0)
	beq	a0,a1, .L105
	j	.L109
.L105:
	call	find
	beqz	a0, .L106
	j	.L104
.L106:
	li	a0,37
	call	chapush
	j	.L103
.L103:
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,32
	sw	a1,0(a0)
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,1
	la	a1,ii
	sw	a0,0(a1)
	j	.L36
.L109:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,chas
	addi	a1,a1,0
	add	a0,a0,a1
	li	a1,47
	lw	a0,0(a0)
	beq	a0,a1, .L105
	j	.L108
.L108:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,chas
	addi	a1,a1,0
	add	a1,a0,a1
	li	a0,37
	lw	a1,0(a1)
	beq	a1,a0, .L105
	j	.L107
.L107:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,94
	lw	a1,0(a1)
	beq	a1,a0, .L105
	j	.L106
.L97:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,47
	lw	a1,0(a1)
	beq	a1,a0, .L93
	j	.L96
.L96:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,37
	lw	a0,0(a0)
	beq	a0,a1, .L93
	j	.L95
.L95:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,94
	lw	a1,0(a1)
	beq	a1,a0, .L93
	j	.L94
.L85:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,47
	lw	a1,0(a1)
	beq	a1,a0, .L81
	j	.L84
.L84:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,37
	lw	a0,0(a0)
	beq	a0,a1, .L81
	j	.L83
.L83:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,94
	lw	a0,0(a0)
	beq	a0,a1, .L81
	j	.L82
.L73:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,45
	lw	a1,0(a1)
	beq	a1,a0, .L67
	j	.L72
.L72:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,42
	lw	a1,0(a1)
	beq	a1,a0, .L67
	j	.L71
.L71:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,47
	lw	a0,0(a0)
	beq	a0,a1, .L67
	j	.L70
.L70:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,37
	lw	a0,0(a0)
	beq	a0,a1, .L67
	j	.L69
.L69:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,94
	lw	a1,0(a1)
	beq	a1,a0, .L67
	j	.L68
.L59:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,chas
	addi	a1,a1,0
	add	a1,a0,a1
	li	a0,45
	lw	a1,0(a1)
	beq	a1,a0, .L53
	j	.L58
.L58:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,42
	lw	a0,0(a0)
	beq	a0,a1, .L53
	j	.L57
.L57:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,chas
	addi	a1,a1,0
	add	a0,a0,a1
	li	a1,47
	lw	a0,0(a0)
	beq	a0,a1, .L53
	j	.L56
.L56:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,chas
	addi	a1,a1,0
	add	a1,a0,a1
	li	a0,37
	lw	a1,0(a1)
	beq	a1,a0, .L53
	j	.L55
.L55:
	la	a0,chat
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,chas
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,94
	lw	a0,0(a0)
	beq	a0,a1, .L53
	j	.L54
.L113:
	li	a0,0
	la	a1,chat
	lw	a1,0(a1)
	bgt	a1,a0, .L114
	j	.L115
.L114:
	call	chapop
	la	a1,ii
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a2,a1,2
	la	a1,get2
	addi	a2,a2,0
	add	a2,a1,a2
	li	a1,32
	sw	a1,0(a2)
	la	a1,ii
	lw	a1,0(a1)
	addi	a1,a1,1
	addi	a1,a1,0
	slli	a2,a1,2
	la	a1,get2
	addi	a2,a2,0
	add	a1,a1,a2
	sw	a0,0(a1)
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,2
	mv	a1,a0
	la	a0,ii
	sw	a1,0(a0)
	j	.L113
.L115:
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a0,a1,a0
	li	a1,64
	sw	a1,0(a0)
	li	a0,1
	la	a1,i
	sw	a0,0(a1)
	j	.L116
.L116:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,get2
	addi	a1,a1,0
	add	a1,a0,a1
	li	a0,64
	lw	a1,0(a1)
	bne	a1,a0, .L117
	j	.L118
.L117:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,43
	lw	a1,0(a1)
	beq	a1,a0, .L119
	j	.L126
.L119:
	call	intpop
	mv	s1,a0
	call	intpop
	la	a1,i
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a2,a1,2
	la	a1,get2
	addi	a2,a2,0
	add	a2,a1,a2
	li	a1,0
	mv	a3,a1
	li	a1,43
	lw	a2,0(a2)
	beq	a2,a1, .L127
	j	.L129
.L127:
	add	a1,s1,a0
	mv	a3,a1
	j	.L129
.L129:
	la	a1,i
	lw	a1,0(a1)
	addi	a1,a1,0
	slli	a2,a1,2
	la	a1,get2
	addi	a2,a2,0
	add	a2,a1,a2
	mv	a1,a3
	li	a3,45
	lw	a2,0(a2)
	beq	a2,a3, .L130
	j	.L132
.L130:
	sub	a1,a0,s1
	j	.L132
.L132:
	la	a2,i
	lw	a2,0(a2)
	addi	a2,a2,0
	slli	a2,a2,2
	la	a3,get2
	addi	a2,a2,0
	add	a2,a3,a2
	li	a3,42
	lw	a2,0(a2)
	beq	a2,a3, .L133
	j	.L135
.L133:
	mul	a1,s1,a0
	j	.L135
.L135:
	la	a2,i
	lw	a2,0(a2)
	addi	a2,a2,0
	slli	a3,a2,2
	la	a2,get2
	addi	a3,a3,0
	add	a2,a2,a3
	li	a3,47
	lw	a2,0(a2)
	beq	a2,a3, .L136
	j	.L138
.L136:
	div	a1,a0,s1
	j	.L138
.L138:
	la	a2,i
	lw	a2,0(a2)
	addi	a2,a2,0
	slli	a3,a2,2
	la	a2,get2
	addi	a3,a3,0
	add	a2,a2,a3
	li	a3,37
	lw	a2,0(a2)
	beq	a2,a3, .L139
	j	.L141
.L139:
	rem	a1,a0,s1
	j	.L141
.L141:
	la	a2,i
	lw	a2,0(a2)
	addi	a2,a2,0
	slli	a3,a2,2
	la	a2,get2
	addi	a3,a3,0
	add	a2,a2,a3
	li	a3,94
	lw	a2,0(a2)
	beq	a2,a3, .L142
	j	.L144
.L142:
	mv	a1,s1
	call	power
	mv	a1,a0
	j	.L144
.L144:
	mv	a0,a1
	call	intpush
	j	.L121
.L121:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,1
	la	a1,i
	sw	a0,0(a1)
	j	.L116
.L126:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,45
	lw	a1,0(a1)
	beq	a1,a0, .L119
	j	.L125
.L125:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,42
	lw	a1,0(a1)
	beq	a1,a0, .L119
	j	.L124
.L124:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,47
	lw	a1,0(a1)
	beq	a1,a0, .L119
	j	.L123
.L123:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a1,a0,2
	la	a0,get2
	addi	a1,a1,0
	add	a1,a0,a1
	li	a0,37
	lw	a1,0(a1)
	beq	a1,a0, .L119
	j	.L122
.L122:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,94
	lw	a1,0(a1)
	beq	a1,a0, .L119
	j	.L120
.L120:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,32
	lw	a1,0(a1)
	bne	a1,a0, .L145
	j	.L121
.L145:
	la	a0,i
	lw	a0,0(a0)
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a0,a1,a0
	lw	a0,0(a0)
	addi	a0,a0,-48
	call	intpush
	li	a0,1
	la	a1,ii
	sw	a0,0(a1)
	j	.L148
.L148:
	la	a0,ii
	lw	a0,0(a0)
	la	a1,i
	lw	a1,0(a1)
	add	a0,a1,a0
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a1,a1,a0
	li	a0,32
	lw	a1,0(a1)
	bne	a1,a0, .L149
	j	.L150
.L149:
	la	a0,ii
	lw	a0,0(a0)
	la	a1,i
	lw	a1,0(a1)
	add	a0,a1,a0
	addi	a0,a0,0
	slli	a0,a0,2
	la	a1,get2
	addi	a0,a0,0
	add	a0,a1,a0
	lw	a0,0(a0)
	addi	a0,a0,-48
	call	intadd
	la	a0,ii
	lw	a0,0(a0)
	addi	a0,a0,1
	la	a1,ii
	sw	a0,0(a1)
	j	.L148
.L150:
	la	a0,ii
	lw	a0,0(a0)
	la	a1,i
	lw	a1,0(a1)
	add	a0,a1,a0
	addi	a0,a0,-1
	mv	a1,a0
	la	a0,i
	sw	a1,0(a0)
	j	.L121
.L118:
	la	a0,ints
	addi	a0,a0,4
	lw	a0,0(a0)
	call	putint
	j	.L151
.L151:
	addi	sp,sp,8
	ld	s1,0(sp)
	ld	s0,8(sp)
	ld	ra,16(sp)
	addi	sp,sp,24
	li	a0,0
	ret
