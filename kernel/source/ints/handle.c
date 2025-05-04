#include <stdint.h>

#include "handle.h"
#include "../fbuffer.h"


const char* exception_messages[] = {
    "Divide by Zero",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Security Exception",
    "Reserved"
};

void display_int_info(const isr_frame_t *frame) {
  kprintf("\n\n===. CPU EXCEPTION .===\n\n");
  kprintf("Exception : %s (%d)\n", exception_messages[frame->number], frame->number);
  kprintf("Register dump :\n");
  kprintf("rax : %X\nrbx : %X\nrcx : %X\nrdx : %X\n", frame->rax, frame->rbx, frame->rcx, frame->rdx);
  kprintf("rsi : %X\nrdi : %X\nrbp : %X\n", frame->rsi, frame->rdi, frame->rbp);
  kprintf("r8  : %X\nr9  : %X\nr10 : %X\nr11 : %X\n", frame->r8, frame->r9, frame->r10, frame->r11);
  kprintf("r12 : %X\nr13 : %X\nr14 : %X\nr15 : %X\n", frame->r12, frame->r13, frame->r14, frame->r15);
}
