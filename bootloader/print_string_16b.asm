[bits 16]
print:
    pusha   ; store the registers
    mov ah, 0x0e

print_loop:
    mov cx, [bx] ; get the data of @bx
    
    ; compare if cx is 0
    cmp cl, 0x0  ; Must be cl because mov loads 16bit little endian
    je print_end ; if cx = 0, end of string
    
    add bx, 0x1
    mov al, cl  ; get the lowe byte
    int 0x10    ; print

    jmp print_loop

print_end:
    popa    ; restore the resgisters
    ret