; load DH sectors to ES:BX from drive DL
[bits 16]

disk_load:
	push dx				; store the number of sectors to be written
	mov ah, 0x02		; BIOS read sector function
	mov al, dh			; read dh sectors
	mov ch, 0x00		; cylinder 0
	mov dh, 0x00		; head 0
	mov cl, 0x02		; start reading from second sector

	int 0x13			; BIOS interrupt

	jc disk_error		; Jump if error (carry flag set)

	pop dx				; restore dx from stack
	cmp dh, al			; al(sectors actually read)
						; dh(sectors to be read)
	jne disk_error

	mov bx, DISK_READ_MSG
	call print_string

	ret

disk_error:
	mov bx, DISK_ERROR_MSG
	call print_string	; print error msg
	mov dh, ah			; copy error code
	mov dl, 0			; remove disk number
	call print_hex		; print error code
	jmp $

; data
DISK_ERROR_MSG db "Disk read error!", 0
DISK_READ_MSG db "Disk read!", 0
