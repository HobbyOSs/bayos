[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "tomo_rdtsc.nas"]

		GLOBAL	_tomo_rdtsc

[SECTION .text]

_tomo_rdtsc:	; void tomo_rdtsc(int *high, int *low);
		PUSHAD
		DB		0x0F, 0x31		; RDTSC
		MOV		EBP,[ESP+36]
		MOV		[EBP],EDX
		MOV		EBP,[ESP+40]
		MOV		[EBP],EAX
		POPAD
		RET
