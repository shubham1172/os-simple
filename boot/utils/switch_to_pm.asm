[bits 16]
; Switch to protected mode
switch_to_pm:
	cli							; switch off interrupts
	lgdt [gdt_descriptor]		; load gdt descriptor
	
	mov eax, cr0				; set first bit of cr0 
	or eax, 0x1
	mov cr0, eax
	
	jmp CODE_SEG:init_pm		; make a far jump (new seg)
								; pipeline flushed
								
[bits 32]
; Initialize registers and stack
init_pm:
	mov ax, DATA_SEG			; copy data seg in ax
	mov ds, ax					; update segments
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax	
								; update stack pointers
	mov ebp, 0x90000
	mov esp, ebp
	
call BEGIN_PM					
