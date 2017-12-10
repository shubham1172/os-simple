;
;	ASM utility for print_string
;

; Prints the string in bx 
print_string:
	pusha			; Push all register values to stack		
	mov ah, 0x0e	; BIOS routine teletype	
	
	mov si, bx		; SI <- BX
	
loop:
	lodsb			; Load one byte into AL
	cmp al, 0		; compare with null terminator of string
	je end_loop		
	int 0x10		; print
	jmp loop		

end_loop:
	popa			; Restore registers
	ret
	

; Prints the value of dx as hex	
print_hex:
	pusha
	mov bx, 5		; counter

	
loop_hex:
	mov cx, dx		; copy dx into cx
	and cx, 0xf		; take last nibble
	cmp cx, 0x9		; compare to 9
	jbe final_hex
	add cx, 0x7		; add 7 for A-F
	
final_hex:
	add cx, '0'		; convert to ascii
					; copy character into bx
	mov byte [HEX_OUT+bx], cl
	ror dx, 4 		; rotate dx by 4 bits	
	dec bx			; counter++
	cmp bx, 1		; end of loop
	jne loop_hex	
	
	mov bx, HEX_OUT	; copy to bx
	call print_string
	popa
	ret
	
; hex_out string
HEX_OUT: db '0x0000',0
