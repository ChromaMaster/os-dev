[bits 16]
; Fully explained here
; http://www.osdever.net/tutorials/view/the-world-of-protected-mode
gdt_start:  ; don't remove the labels, they're needed to compute sizes and jumps
            ; the GDT starts with a null 8-byte
    dd 0x0  ; 4 byte
    dd 0x0  ; 4 byte

; GDT for code segment. 
; for flags, refer to os-dev.pdf document, page 36\
; base = 0x0000, length = 0xffff
gdt_code: 
    ; 1 st flags : (present)1 (privilege)00 (descriptor type)1 -> 1001 b
    ; type flags : (code)1 (conforming)0 (readable)1 (accessed)0 -> 1010 b
    ; 2 nd flags : (granularity)1 (32 - bit default)1 (64 - bit seg)0 (AVL)0 -> 1100 b
    dw 0xffff       ; segment length, bits 0-15
    dw 0x0          ; segment base, bits 0-15
    db 0x0          ; segment base, bits 16-23
    db 10011010b    ; flags (8 bits)
    db 11001111b    ; flags (4 bits) + segment length, bits 16-19
    db 0x0          ; segment base, bits 24-31

; GDT for data segment. base and length identical to code segment
; some flags changed, again, refer to os-dev.pdf
; base = 0x0000, length = 0xffff
gdt_data:
    ; Same as code segment except for the type flags :
    ; 1 st flags : (present)1 (privilege)00 (descriptor type)1 -> 1001 b
    ; type flags : (code)0 (expand down)0 (writable)1 (accessed)0 -> 0010 b
    dw 0xffff       ; segment length, bits 0-15;
    dw 0x0          ; segment base, bits 0-15
    db 0x0          ; segment base, bits 16-23
    db 10010010b    ; flags (8 bits)
    db 11001111b    ; flags (4 bits) + segment length, bits 16-19
    db 0x0          ; segment base, bits 24-31

gdt_end:            ; The reason for putting a label at the end of the
                    ; GDT is so we can have the assembler calculate
                    ; the size of the GDT for the GDT decriptor (below)

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; size (16 bit), always one less of its true size
    dd gdt_start                ; address (32 bit)

; Define some handy constants for the GDT segment descriptor offsets, which
; are what segment registers must contain when in protected mode. For example,
; when we set DS = 0x10 in PM, the CPU knows that we mean it to use the
; segment described at offset 0x10 (i.e. 16 bytes) in our GDT, which in our
; case is the DATA segment (0x0 -> NULL ; 0x08 -> CODE ; 0x10 -> DATA)
; define some constants for later use
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start