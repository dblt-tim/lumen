#include <stddef.h>

#include "../limine.h"

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request memmap_request = {
  .id = LIMINE_MEMMAP_REQUEST,
  .revision = 0
};

int init_mem() {
  if (memmap_request.response == NULL ||
     memmap_request.response->entry_count < 1) {
    return -1;
  }
  for (size_t i = 0; i < memmap_request.response->entry_count; i++) {
    struct limine_memmap_entry *memmap_entry = memmap_request.response->entries[i];

    uint64_t base = memmap_entry->base;
    uint64_t length = memmap_entry-> length;
    uint64_t type = memmap_entry->type;

  }
}
