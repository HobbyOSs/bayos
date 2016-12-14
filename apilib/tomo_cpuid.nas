[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]
[FILE "tomo_cpuid.nas"]

		GLOBAL	_tomo_cpuid

[SECTION .text]

_tomo_cpuid:	; void tomo_cpuid(int id_eax, int id_ecx, int *eax, int *ebx, int *ecx, int *edx);
		PUSHAD
		MOV		EAX,[ESP+36]
		MOV		ECX,[ESP+40]
		DB		0x0F, 0xA2		; CPUID
		MOV		EBP,[ESP+44]
		MOV		[EBP],EAX	
		MOV		EBP,[ESP+48]
		MOV		[EBP],EBX	
		MOV		EBP,[ESP+52]
		MOV		[EBP],ECX	
		MOV		EBP,[ESP+56]
		MOV		[EBP],EDX	
		POPAD
		RET
