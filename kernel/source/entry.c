
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

#include "util.h"
#include "fbuffer.h"

#include "mem/init.h"

#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"

/* BOOTLOADER ATTR
 * */
__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;
// --------------------------


void kmain(void)
{
  if (LIMINE_BASE_REVISION_SUPPORTED == false) {
    hcf();
  }
  
  switch (init_fbuffer()) {
    case -1:
      hcf();
      break;
    default:
      break;
  }
  kprintf("Hello world !\n");
  kprintf("printing 145 in dec : %d\n", 145);
  kprintf("printing 145 in hex : %X\n", 145);
  // hang
  hcf();
}
