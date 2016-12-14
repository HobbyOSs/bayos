[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "tomo_rdmsr.nas"]

		GLOBAL	_tomo_rdmsr

[SECTION .text]

_tomo_rdmsr:	; void tomo_rdmsr(int id_ecx, int *eax, int *edx);
		PUSHAD
		MOV		EDX,0x1002
		MOV		ECX,[ESP+36]
		INT		0x40
		MOV		EBP,[ESP+40]
		MOV		[EBP],EAX
		MOV		EBP,[ESP+44]
		MOV		[EBP],EDX
		POPAD
		RET
