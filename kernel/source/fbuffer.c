#include <stddef.h>
#include <stdarg.h>

#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"

#include "limine.h"

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request fbuffer_req = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

static struct flanterm_context *ft_ctx = NULL;

int init_fbuffer() {
  if (fbuffer_req.response == NULL
  || fbuffer_req.response->framebuffer_count < 1) {
    return -1;
  }
  struct limine_framebuffer *fbuffer = fbuffer_req.response->framebuffers[0];
  ft_ctx = flanterm_fb_init(
    NULL,
    NULL,
    fbuffer->address, fbuffer->width, fbuffer->height, fbuffer->pitch,
    fbuffer->red_mask_size, fbuffer->red_mask_shift,
    fbuffer->green_mask_size, fbuffer->green_mask_shift,
    fbuffer->blue_mask_size, fbuffer->blue_mask_shift,
    NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, NULL,
    NULL, 0, 0, 1,
    0, 0,
    0
  );
  return 0;
}


void kprintc(char c) {
  if (ft_ctx) flanterm_write(ft_ctx, &c, 1);
}

void kprinti(int value, int base) {
  char str[32];
  char temp[32];
  const char *digits = "0123456789ABCDEF";
  int i = 0;
  if (value == 0) {
    str[0] = '0';
    str[1] = '\0';
  } else {
    while (value && i < 31) {
      temp[i++] = digits[value % base];
      value /= base;
    }
    for (int j = 0; j < i; j++) {
      str[j] = temp[i - j - 1];
    }
    str[i] = '\0';
  }
  switch (base) {
    case 10:
      break;
    case 16:
      kprintc('0'); kprintc('x');
      break;
  }
  for (int k = 0; str[k] != '\0'; k++) {
    kprintc(str[k]);
  }
}

void kprintf(const char *msg, ...) {
  if (!ft_ctx) return;
  va_list args;
  va_start(args, msg);

  for (size_t i = 0; msg[i] != '\0'; i++) {
    if (msg[i] == '%') {
      i++;
      switch (msg[i]) {
        case '%':
          kprintc('%');
          break;
        case 's':
          const char * s = va_arg(args, const char*);
          for (int j = 0; s[j] != '\0'; j++) {
            kprintc(s[j]);
          }
          break;
        case 'd':
        case 'i':
          kprinti(va_arg(args, int), 10);
          break;
        case 'X':
          kprinti(va_arg(args, int), 16);
          break;
        default:
          break;
      }
      continue;
    }
    kprintc(msg[i]);
  }

  va_end(args);
}
