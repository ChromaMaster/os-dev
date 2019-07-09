#ifndef IDT_H
#define IDT_H

#include "../libc/types.h"

#define KERNEL_SEGMENT_SELECTOR 0x08

// A IA-32 struct describing an interrupt gate.
typedef struct {
    u16 base_lo;  // The lower 16 bits of the address to jump to when this interrupt fires.
    u16 sel;      // Kernel segment selector.
    u8 always0;   // Unused. This must always be zero.
    u8 flags;     // First byte
                  // Bit 7: "Interrupt is present"
                  // Bits 6-5: privilege level we expect to be called from (0=kernel..3=user)
                  // Bit 4: Set to 0 for interrupt and trap gates
                  // Bits 3-0:
                  //      0b0101 0x5 5  80386 32 bit task gate
                  //      0b0110 0x6 6  80286 16-bit interrupt gate
                  //      0b0111 0x7 7  80286 16-bit trap gate
                  //      0b1110 0xE 14 80386 32-bit interrupt gate
                  //      0b1111 0xF 15 80386 32-bit trap gate
    u16 base_hi;  // The upper 16 bits of the address to jump to.
} __attribute__((packed)) idt_gate_t;

// This is in a format suitable for giving to 'lidt'.
typedef struct {
    u16 limit;
    u32 base;  // The address of the first element in our idt_gate_t array.
} __attribute__((packed)) idt_ptr_t;

// There are 256 interrupts (0..255), so IDT should have 256 entries,
// each entry corresponding to a specific interrupt.
#define IDT_ENTRIES 256
idt_gate_t idt_entries[IDT_ENTRIES];
idt_ptr_t idt_reg;

/**
 * init_idt - initializes the idt base address and sets the his limit
 */
void init_idt();

/**
 * set_idt_gate - assign a idt entry to a specific handler
 * @paran n idt entry index
 * @param handler address of the handler for that specific entry
 */
void set_idt_gate(int n, u32 handler);

#endif  // !IDT_H