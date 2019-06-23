[org 0x7c00]                ; Tell the assembler where this code will be loaded
KERNEL_OFFSET equ 0x1000     ; This is the memory offset to which we will load 
                            ; our kernel 

main:

    mov [BOOT_DRIVE], dl    ; BIOS stores our boot drive in DL, so it’s
                            ; best to remember this for later.


    mov bp, 0x9000          ; Set the stack.
    mov sp, bp

    mov bx, MSG_REAL_MODE   ; Use BX as a parameter to our function, so
    call print              ; we can specify the address of a string.

    call load_kernel        ; Load our kernel

    call switch_to_pm       ; Note that we never return from here.
    
    jmp $                   ; Hang

%include "print_string_16b.asm"
%include "print_hex_16b.asm"
%include "disk_load.asm"
%include "gdt.asm"
%include "print_string_pm.asm"
%include "switch_to_pm.asm"

[bits 16]
; load_kernel
load_kernel:
    mov bx, MSG_LOAD_KERNEL ; Print a message to say we are loading the kernel
    call print

    mov bx, KERNEL_OFFSET   ; Set - up parameters for our disk_load routine, so
    mov dh, 15              ; that we load the first 15 sectors (excluding
    mov dl, [BOOT_DRIVE]    ; the boot sector) from the boot disk (i.e. our
    call disk_load          ; kernel code) to address KERNEL_OFFSET

    ret

[bits 32]
; This is where we arrive after switching to and initialising protected mode.
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_pm           ; Use our 32 - bit print routine.

    call KERNEL_OFFSET      ; Now jump to the address of our loaded
                            ; kernel code, assume the brace position,
                            ; and cross your fingers. Here we go !        

    jmp $   ; Hang.

; Global variables
BOOT_DRIVE: db 0
MSG_LOAD_KERNEL: db "Loading Kernel...", 10, 13, 0
MSG_REAL_MODE: db "Started in 16 - bit Real Mode", 10, 13, 0
MSG_PROT_MODE: db "Successfully landed in 32 - bit Protected Mode", 0

; Boot sector padding
times 510-($ - $$) db 0    ; When compiled, our program must fit into 
                            ; 512 bytes, with the last two bytes being 
                            ; the magic number, so here, tell our 
                            ; assembly compiler to pad out our program 
                            ; with enough zero bytes (db 0) to bring us
                            ; to the 510th byte.                                                                        

dw 0xaa55                   ; Last two bytes (one word) form the magic
                            ; number, so BIOS knows we are a boot sector.