title 汇编冒泡 2016.10.20 by kkcckc

include  f:\\desktop\\asm\\ASM32.INC
.DATA
	n DWORD ?
	v DWORD 100 DUP(?)
.CODE
	start	PROC
			INVOKE	printf,chr$("输入数的个数:",0Ah,0dh)
			INVOKE	scanf,chr$("%d"),offset n
			INVOKE	getchar
			CMP		 n, 0								;0元素处理
			JE		 over
			INVOKE	printf,chr$("输入%d个数:",0Ah,0dh),n

	;读入元素

			MOV		ECX, n
			MOV		ESI, 0
	read:	PUSH	ECX
			LEA		EAX,v[ESI*4] ;[v+ESI*4];
			INVOKE	scanf,chr$("%d"),EAX
			POP		ECX
			INC		ESI
			LOOP	read
			INVOKE	getchar

	;冒泡
			MOV		ECX, n
			DEC		ECX
			CMP		ECX, 0
			JE		print							;单元素处理
	sort0:
			MOV		ESI, 0
			PUSH	ECX
	sort:			
			MOV		EAX,v[ESI*4+4]
			CMP		v[ESI*4],EAX;[v+ESI*4];v[ESI*4]
			JL		no_swap							;<就不交换
			XCHG	v[ESI*4],EAX		
			MOV		v[ESI*4+4],EAX
	no_swap:
			INC		ESI
			LOOP	sort
			POP		ECX
			LOOP	sort0

	;输出
	print:
			MOV		ECX, n
			MOV		ESI, 0
	write:	PUSH	ECX
			INVOKE	printf, chr$("%10d"),v[ESI*4]
			POP		ECX
			INC		ESI
			LOOP	write
			INVOKE	getchar
	over:	INVOKE	EXITPROCESS,0
	start	endp
			end		start