[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "bayos_thread_id.nas"]

		GLOBAL	_bayos_thread_id

[SECTION .text]

_bayos_thread_id:	; int bayos_thread_id(void);
		MOV		EDX,0x3000
		INT		0x40
		RET
