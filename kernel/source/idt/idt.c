

#include "idt.h"

idt_entry_t mk_idt_entry(uint64_t offset, uint16_t selector, uint16_t flags) {
  idt_entry_t entry = {
    (offset & 0xFFFF),
    selector,
    (flags & 0xFF),
    (flags >> 8),
    ((offset >> 16) & 0xFFFF),
    ((offset >> 32) & 0xFFFFFFFF),
    0x00000000
  };
  return entry;
}

idt_t idt;
idtr_t idtr;

extern void load_idt(void);

void init_idt() {
  
  

  idtr.limit = sizeof(idt) - 1;
  idtr.base = (uint64_t)&idt;

  load_idt();
}
