INCLUDE		 f:\desktop\ASM32.INC

putchar		PROTO	C

.DATA
		 buf		BYTE	16 dup (0ffh)
		 pi			DWORD	0
		 po			DWORD	0
		 n			DWORD	0
		 chr		BYTE	0
.CODE 

	main		PROC
					invoke	printf,chr$("请haah择：ESC 退出；- 从队列提取元素显示 +打印当前队列；0-9A-Z进入队列，其他抛弃。",0dh,0ah)
		start:		invoke _getche		;注意用scanf后一定要有这个调用，去掉键盘缓冲区的回车符。
					cmp		al,1BH   ;  ESC 退出
					jz		over
					cmp		al, '+'
					jz		printq
					cmp		al,'-'
					jnz		insert

					push	offset chr
					push	offset po
					push	offset buf
					;call	qo				
					add		esp,12
	
					cmp		eax,0
					jz		empty
					invoke	printf,chr$("提取的元素为：%c",0dh,0ah),chr
					jmp		start
		empty:
					invoke	printf,chr$(" EMPTY!",0dh,0ah)
					jmp		start
		insert:
					cmp		al,'0'
					jb		start
					cmp		al,'9'
					jbe		il
					cmp		al,'A'
					jb		start
					cmp		al,'Z'
					jbe		il
					;cmp	al,'a'
					;jb		start
					;cmp	al,'z'
					;ja		start
					JMP		start
		il:			push	eax
					push	offset pi
					push	offset buf
					;call	qi		
					add		esp,12
					cmp		eax,0
					jnz		start		
					invoke	printf,chr$(0dh, 0ah," FULL!",0dh,0ah)
					jmp		start
		printq: 
					push	po
					push	pi
					push	offset buf
					;call	qp
					add		esp,12
					jmp		start
		over:		invoke	ExitProcess,0
	main			ENDP
		END main 