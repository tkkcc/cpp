.586
.MODEL flat, STDCALL
.STACK 4096
option casemap : none;  ��Сд����


; Ϊ�ⲿ�ṩ�Ķ������������
public C qo,qi,qp,buf,n,chr,pi,po
; �ⲿ�ı������������


modd=000FH
; �����������ⶼ���������
qo		PROTO C	:PTR BYTE,:PTR DWORD,:PTR BYTE
qi		PROTO C	:DWORD,:PTR DWORD,:PTR BYTE
qp		PROTO C :DWORD,:DWORD,:PTR BYTE
incp	PROTO C :PTR DWORD
printf	PROTO C : ptr byte, : vararg
_getche	PROTO C

chr$ MACRO any_text : vararg
	LOCAL textname
	.const
		textname db any_text, 0
	ALIGN 4
	.code
		EXITM <OFFSET textname>
ENDM

.data
	 buf	BYTE	16 dup (0ffh)
	 pi		DWORD	0
	 po		DWORD	0
	 n		DWORD	0
	 chr	BYTE	0

 .code

	qi		PROC C	USES EBX ECX eaxx:DWORD ,pii :PTR DWORD, buff:PTR BYTE
				CMP		n,16
				JNZ		noful
				MOV		EAX,0	;NULL��asciiΪ0 
				JMP		over
		noful:	
				
				INC		n
				MOV		EBX, buff
				MOV		ECX, pii
				MOV		ECX, [ECX]
				MOV		EAX,eaxx
				MOV		[EBX+ECX],AL
				INVOKE	incp, pii
				MOV		EAX,1
		over:	
				
				RET 
				qi ENDP

		qo		PROC C	USES EBX ECX EDX chrr:PTR BYTE,pii:PTR DWORD,buff:PTR BYTE
				CMP		n,0
				JNZ		nemp
				MOV		EAX,0
				JMP		over
		nemp:	
				MOV		EAX,1
				DEC		n
				mov		ebx, buff
				mov		ecx, pii
				MOV		ECX, [ECX]
				mov		EBX, [ebx+ecx];
				mov		ecx, chrr
				mov		[ecx],BL
				INVOKE	incp, pii
		over:	RET 
				qo ENDP


qp		PROC C USES EBX ECX EDX poo:DWORD,pii:DWORD,buff:PTR BYTE
				INVOKE	printf,chr$(0DH,0AH,"��ǰ�������ݣ�")
				CMP		n,0
				JZ		over
				MOV		EBX, poo
				MOV		EDX, EBX
				MOV		ECX, n
				MOV		EBX, buff
				ADD		EBX, EDX;��ʼ����
				MOV		EDX, buff
				ADD		EDX, 16
		L:		PUSH	ECX
				PUSH	EDX
				INVOKE	printf,chr$("%c"),BYTE PTR [EBX]
				POP		EDX
				POP		ECX
				INC		EBX
				CMP		EBX, EDX
				JNZ		nsub
				SUB		EBX, 16
		nsub:	LOOP	L
		over:	
				MOV		EAX,n
				MOV		EBX,poo
				MOV		ECX,pii
				INVOKE	printf,chr$(09H,"�����±꣺%d ��β�±꣺%d Ԫ�ظ�����%d",0DH,0AH),EBX,ECX,n
				RET 
				qp ENDP
			END