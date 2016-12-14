[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "bayos_msg_receive.nas"]

		GLOBAL	_bayos_msg_receive

[SECTION .text]

_bayos_msg_receive:	; int bayos_msg_receive(MSG_INFO* info);
		MOV		EDX,0x3005
		MOV		EAX,[ESP+4]			; info
		INT		0x40
		RET
