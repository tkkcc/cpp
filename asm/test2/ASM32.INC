.386						; ָ����ͼ��ݵ�CPU
.MODEL        FLAT, STDCALL	; ָ���洢ģʽ����������ȱʡ�淶
.STACK        1024			; �����ջ�Σ�ָ���δ�С��ȱʡ4K
INCLUDELIB	"e:\hlbc\Documents\vs2015\ASM\lib\MSVCRT.LIB"; ����C������
ExitProcess  PROTO    :DWORD
printf		 PROTO C : DWORD, : VARARG; C����������
scanf		 PROTO C : DWORD, : VARARG
getchar		 PROTO C

chr$ MACRO any_text : VARARG; Ŀǰ����, ��ʱ��
	LOCAL txtname
	.DATA
	txtname db any_text, 0
	ALIGN 4
	.code
	EXITM <OFFSET txtname>
ENDM

