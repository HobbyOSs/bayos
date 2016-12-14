[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "bayos_get_wstr_info.nas"]

		GLOBAL	_bayos_get_wstr_info

[SECTION .text]

_bayos_get_wstr_info:	; void bayos_get_wstr_info(char* str, WSTR_INFO* info);
		PUSH	EBX
		MOV		EDX,0x3006
		MOV		EBX,[ESP+ 8]	; str
		MOV		ECX,[ESP+12]	; info
		INT		0x40
		POP		EBX
		RET
