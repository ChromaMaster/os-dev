#include "idt.h"

void init_idt() {
    // Sets the base at the idt_entries array
    idt_reg.base = (u32)&idt_entries;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    // Load the IDT pointer.
    __asm__ __volatile__("lidt (%0)"
                         :
                         : "r"(&idt_reg));
}

void set_idt_gate(int n, u32 handler) {
    idt_entries[n].base_lo = (handler & 0xFFFF);
    idt_entries[n].sel = KERNEL_SEGMENT_SELECTOR;
    idt_entries[n].always0 = 0;
    idt_entries[n].flags = 0x8E;  // 1    -> Interrupt is present_kernel
                                  // 00   -> Kernel privilege level
                                  // 0    -> interrupt and trap gates
                                  // 1110 -> 80386 32-bit interrupt gate
    idt_entries[n].base_hi = ((handler >> 16) & 0xFFFF);
}