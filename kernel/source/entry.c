
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

#include "util.h"

#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
/* BOOTLOADER ATTR
 * */
__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

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
  
  if (framebuffer_request.response == NULL
  || framebuffer_request.response->framebuffer_count < 1) {
    hcf();
  }
  // get the framebuffer
  struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
  
  struct flanterm_context *ft_ctx = flanterm_fb_init(
    NULL,
    NULL,
    // framebuffer vars
    framebuffer->address, // framebuffer ptr
    framebuffer->height, framebuffer->height, framebuffer->pitch, // framebuffer video size
    framebuffer->red_mask_size, framebuffer->red_mask_shift, // red
    framebuffer->green_mask_size, framebuffer->green_mask_shift, // green
    framebuffer->blue_mask_size, framebuffer->blue_mask_shift, // blue
    // ;;
    NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, 0, 0, 1,
    0, 0,
    0
  );
  char msg[] = "Hello world !\n";
  flanterm_write(ft_ctx, msg, sizeof(msg));
  // hang
  hcf();
}
