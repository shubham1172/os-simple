[bits 16]
; create a delay of three seconds
delay:
  pusha

  mov al, 0
  mov ah, 0x86      ; BIOS function for delay
                    ; CX:DX - microseconds
  mov cx, 0x002d
  mov dx, 0xc6c0
  int 0x15          ; interrupt

  popa

  ret
