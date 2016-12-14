[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "tomo_wrmsr.nas"]

		GLOBAL	_tomo_wrmsr

[SECTION .text]

_tomo_wrmsr:	; void tomo_wrmsr(int id_ecx, int eax, int edx);
		PUSHAD
		MOV		EDX,0x1006
		MOV		ECX,[ESP+36]
		MOV		EAX,[ESP+40]
		MOV		EBX,[ESP+44]	; NOT EDX!!
		INT		0x40
		POPAD
		RET
