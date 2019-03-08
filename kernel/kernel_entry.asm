; Jump into kernel's entry function
[bits 32]
[extern main]           ; declares usage of external symbol main

call main               ; invoke main() in kernel
jmp $                   ; hang forever on returning
