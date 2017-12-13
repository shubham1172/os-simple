; A boot sector that boots a C kernel
[org 0x7c00]
KERNEL_OFFSET equ 0x1000; memory offset to load the kernel

	mov [BOOT_DRIVE], dl	; store boot drive

	mov bp, 0x9000				; set the stack
	mov sp, bp

	mov bx, MSG_REAL_MODE	; announce starting
	call print_string

	call load_kernel			; load kernel

	call switch_to_pm			; switch to protected mode

	jmp $

%include "boot/disk/disk_load.asm"
%include "boot/print/print_string.asm"
%include "boot/print/print_string_pm.asm"
%include "boot/gdt/gdt.asm"
%include "boot/utils/switch_to_pm.asm"

[bits 16]
; load kernel
load_kernel:
	mov bx, MSG_LOAD_KERNEL	; announce kernel load
	call print_string

	mov bx, KERNEL_OFFSET		; set up disk_load params
	mov dh, 2
	mov dl, [BOOT_DRIVE]
	call disk_load

	ret

[bits 32]
; begin protected mode
BEGIN_PM:

	mov ebx, MSG_PROT_MODE	; announce protected mode
	call print_string_pm

	call KERNEL_OFFSET			; jump to the loaded kernel

	jmp $										; hang

; global variables
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode. ", 0
MSG_PROT_MODE db "Switched to 32-bit Protected Mode. ", 0
MSG_LOAD_KERNEL db "Loading kernel into memory. ", 0

; padding
TIMES 510-($-$$) db 0
dw 0xaa55
