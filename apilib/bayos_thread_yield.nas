[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "bayos_thread_yield.nas"]

		GLOBAL	_bayos_thread_yield

[SECTION .text]

_bayos_thread_yield:	; int bayos_thread_yield(void);
		MOV		EDX,0x3003
		INT		0x40
		RET
