[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "tomo_getmouse.nas"]

		GLOBAL	_tomo_getmouse

[SECTION .text]

_tomo_getmouse:	; void tomo_getmouse(int win, struct MOUSE_INFO *info);
		PUSH	EBX
		MOV		EDX,0x1000
		MOV		EBX,[ESP+ 8]	; win
		MOV		ECX,[ESP+12]	; info
		INT		0x40
		POP		EBX
		RET
