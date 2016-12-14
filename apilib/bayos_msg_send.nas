[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "bayos_msg_send.nas"]

		GLOBAL	_bayos_msg_send

[SECTION .text]

_bayos_msg_send:	; void bayos_msg_send(int to, MSG_INFO* info);
		PUSH	EBX
		MOV		EDX,0x3004
		MOV		EBX,[ESP+ 8]	; to
		MOV		ECX,[ESP+12]	; info
		INT		0x40
		POP		EBX
		RET
