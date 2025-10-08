[bits 32]
[extern main]
global _start

_start:
	; Set up a basic 32-bit stack (matches what mbr set, but ensure sane value)
	mov ebp, 0x90000
	mov esp, ebp

	; Print 'K' directly to VGA memory to show we reached the kernel
	mov byte [0xB8000 + 160], 'K'  ; Row 1, column 0
	mov byte [0xB8001 + 160], 0x0F ; White on black

	call main
	jmp $