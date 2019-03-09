[bits 32]
; Constants
	VIDEO_MEMORY equ 0xb8000
	WHITE_ON_BLACK equ 0x0f

;
; Print a null terminated string pointer to by EBX
;
print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY			; set EDX to the start of vid memory

print_string_pm_loop:
	mov al, [ebx]					; store char at EBX in AL
	mov ah, WHITE_ON_BLACK			; store attributes in AH

	cmp al, 0						; compare to null
	je print_string_pm_done			; jump to done

	mov [edx], ax					; store AH and AL at current cell
	inc ebx							; read next character
	add edx, 2						; jump to next cell in vid mem

	jmp print_string_pm_loop		; loop

print_string_pm_done:
	popa
	ret
