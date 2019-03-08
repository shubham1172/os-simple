; GDT

gdt_start:					; start of GDT

gdt_null: 					; mandatory null descriptor
	dd 0x0					; next 8 bytes will be null
	dd 0x0					;
	
gdt_code: 					; code segment descriptor
	dw 0xffff 				; limit (0 -15)
	dw 0x0					; base (0 -15)
	db 0x0	 				; base (16 -23)
	db 10011010b 			; 1st flags , type flags
	db 11001111b			; 2nd flags, seg limit
	db 0x0					; base
	
gdt_data:					; data segment descriptor
	dw 0xffff 				; limit (0 -15)
	dw 0x0					; base (0 -15)
	db 0x0	 				; base (16 -23)
	db 10010010b 			; 1st flags , type flags
	db 11001111b			; 2nd flags, seg limit
	db 0x0					; base
	
gdt_end:					; label to calculate size of GDT

gdt_descriptor:				; GDT descriptor
							; size
	dw gdt_end - gdt_start - 1
	dd gdt_start			; address of start
	
; constants
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
