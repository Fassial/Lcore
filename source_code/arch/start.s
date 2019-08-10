#
# start.s
#

.extern init_kernel
.global start

.set noreorder
.set noat
.align 2

start:
	li	$sp, 0x3000
	la	$gp, _gp
	jal	init_kernel
	nop
loop:
	j	loop
	nop

