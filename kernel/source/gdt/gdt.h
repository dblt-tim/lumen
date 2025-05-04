#include <stdint.h>

#ifndef GDT_GDT_H
#define GDT_GDT_H

typedef struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_mid;
  uint8_t access;
  uint8_t limit_high_and_flags;
  uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
  uint16_t limit;
  uint64_t base;
} __attribute__((packed)) gdtr_t;

typedef struct {
  gdt_entry_t entries[3];
} __attribute__((packed)) gdt_t;

void init_gdt(void);

#endif
