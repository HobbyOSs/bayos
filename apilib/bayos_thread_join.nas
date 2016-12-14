[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "bayos_thread_join.nas"]

		GLOBAL	_bayos_thread_join

[SECTION .text]

_bayos_thread_join:	; int bayos_thread_join(dword function);
		MOV		EDX,0x3001
		MOV		EAX,[ESP+4]			; function
		INT		0x40
		RET
