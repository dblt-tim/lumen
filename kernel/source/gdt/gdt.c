#include <stdint.h>

#include "gdt.h"
#include "../fbuffer.h"

gdt_entry_t mk_gdt_entry(uint32_t base, uint32_t limit, uint16_t access_and_flags) {
  gdt_entry_t entry = {
    (uint16_t)(limit & 0xFFFF),
    (uint16_t)(base & 0xFFFF),
    (uint8_t)((base >> 16) & 0xFF),
    (uint8_t)(access_and_flags & 0xFF),
    (uint8_t)((access_and_flags & 0xF00) >> 4) | ((limit >> 16) & 0xF),
    (uint8_t)((base >> 24) & 0xFF)
  };
  return entry;
}

gdt_t gdt;

gdtr_t gdtr;

extern void load_gdt(void);

void init_gdt() {
  // null
  gdt.entries[0] = mk_gdt_entry(0, 0, 0);

  // kernel code seg
  gdt.entries[1] = mk_gdt_entry(
    0x00000000,
    0xFFFFFFFF,
    0b101010011011
  );
  // kernel data seg
  gdt.entries[2] = mk_gdt_entry(
    0x00000000,
    0xFFFFFFFF,
    0b110010010011
  );

  gdtr.limit = sizeof(gdt) - 1;
  gdtr.base = (uint64_t)&gdt;
  
  kprintf("gdtr values :\n");
  kprintf("base : %X\n", gdtr.base);
  kprintf("limit : %d\n\n", gdtr.limit);
  
  kprintf("gdt null entry :\nlimit_low: %X\nbase_low: %X\nbase_mid: %X\naccess: %X\nlimit and flags: %X\nbase_high: %X\n\n"
      , gdt.entries[0].limit_low, gdt.entries[0].base_low, gdt.entries[0].base_mid, gdt.entries[0].access, gdt.entries[0].limit_high_and_flags, gdt.entries[0].base_high);

  kprintf("gdt code seg entry :\nlimit_low: %X\nbase_low: %X\nbase_mid: %X\naccess: %X\nlimit and flags: %X\nbase_high: %X\n\n"
      , gdt.entries[1].limit_low, gdt.entries[1].base_low, gdt.entries[1].base_mid, gdt.entries[1].access, gdt.entries[1].limit_high_and_flags, gdt.entries[1].base_high);

  kprintf("gdt data seg entry :\nlimit_low: %X\nbase_low: %X\nbase_mid: %X\naccess: %X\nlimit and flags: %X\nbase_high: %X\n"
      , gdt.entries[2].limit_low, gdt.entries[2].base_low, gdt.entries[2].base_mid, gdt.entries[2].access, gdt.entries[2].limit_high_and_flags, gdt.entries[2].base_high);
  load_gdt();
}
