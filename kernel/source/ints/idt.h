
#include <stdint.h>

#ifndef INTERRUPTS_IDT_H
#define INTERRUPTS_IDT_H

typedef struct {
  uint16_t offset_low;
  uint16_t selector;
  uint8_t ist;
  uint8_t gt_dpl_p;
  uint16_t offset_mid;
  uint32_t offset_high;
  uint32_t reserved;
} __attribute__((packed)) idt_entry_t;

typedef struct {
  idt_entry_t entries[32];
} __attribute__((packed)) idt_t;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idtr_t;

void init_idt(void);

#endif
