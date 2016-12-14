[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "bayos_thread_kill.nas"]

		GLOBAL	_bayos_thread_kill

[SECTION .text]

_bayos_thread_kill:	; int bayos_thread_kill(int id);
		MOV		EDX,0x3002
		MOV		EAX,[ESP+4]			; id
		INT		0x40
		RET
