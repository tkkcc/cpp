.386						; ָ����ͼ��ݵ�CPU
.MODEL        FLAT, STDCALL	; ָ���洢ģʽ����������ȱʡ�淶
.STACK        1024			; �����ջ�Σ�ָ���δ�С��ȱʡ4K
INCLUDELIB	 MSVCRT.LIB		; ����C������
ExitProcess  PROTO    :DWORD
printf		 PROTO C : PTR BYTE , : VARARG; C����������
scanf		 PROTO C : PTR BYTE , : VARARG
getchar		 PROTO C
strlen	     PROTO C : PTR BYTE 
_getche		 PROTO C


chr$ MACRO any_text : VARARG; Ŀǰ����, ��ʱ��
	LOCAL txtname
	.DATA
	txtname db any_text, 0
	ALIGN 4
	.code
	EXITM <OFFSET txtname>
ENDM

