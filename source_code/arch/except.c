#include "except.h"
#include "../kern/vga/vga.h"

void do_ri(unsigned int errArg, unsigned int errPc, unsigned int *regs)
{
	unsigned int inst = *((unsigned int *) errArg);
	unsigned int rs, rt;
	unsigned int va, mem, byte;
	
	rs = _STACK_OFFSET(_RS_(inst), regs);
	rt = _STACK_OFFSET(_RT_(inst), regs);
	va = rs + _OFFSET_(inst);
	byte = va & 3;

	switch (_CODE_(inst)) {
		case _CODE_LWL:
			mem = *(unsigned int *) (va - byte);
			mem = mem << multiply(3 - byte, 8);
			rt = (rt & ~(-1 << multiply(3 - byte, 8))) | mem;
			_STACK_OFFSET(_RT_(inst), regs) = rt;
			break;
		case _CODE_LWR:
			mem = *(unsigned int  *)(va - byte);
			mem = mem >> multiply(byte, 8);
			rt = (rt & ~(-1 >> multiply(byte, 8))) | mem;
			_STACK_OFFSET(_RT_(inst), regs) = rt;
			break;
		case _CODE_SWL:
			mem = *(unsigned int  *)(va - byte);
			mem = mem & ~(-1 >> multiply(3 - byte, 8));
			rt = (rt >> multiply(3 - byte, 8)) | mem;
			*((unsigned int  *)(va - byte)) = rt;
			break;
		case _CODE_SWR:
			mem = *(unsigned int  *)(va - byte);
			mem = mem & ~(-1 << multiply(byte, 8));
			rt = (rt << multiply(byte, 8)) | mem;
			*((unsigned int  *)(va - byte)) = rt;
			break;
		default:
			while (1) ;
			break;
	}
	errPc += 4;
	_STACK_EPC(regs) = errPc;
}

void do_exception(unsigned int  status, unsigned int  errArg, unsigned int  errPc, unsigned int  *regs)
{		
	if (!(status & _EXCEPT_FLAG))
		return;

	switch ((status & 0x0000f800) >> 11) {
		case _RESERVE_INST:
			do_ri(errArg, errPc, regs);
			break;
		default:
			printk("@");
			while(1) ;
			break;
	}
}

