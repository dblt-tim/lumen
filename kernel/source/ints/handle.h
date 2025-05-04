#include <stdint.h>

#ifndef INTERRUPTS_HANDLE_H
#define INTERRUPTS_HANDLE_H
typedef struct {
  uint64_t number;
  uint64_t err_code;

  uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
  uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
} isr_frame_t;

void display_int_info(const isr_frame_t *frame);

#endif
