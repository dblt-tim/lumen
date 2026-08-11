
#include "framebuffer.h"
#include "../util.h"
#include <flanterm_backends/fb.h>
#include <flanterm.h>
#include <stdbool.h>
#include <limine.h>
#include <stdint.h>
#include <stddef.h>

struct flanterm_context* flanterm_ctx;

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_flanterm_fb_init_params_request fb_params_request = {
    .id = LIMINE_FLANTERM_FB_INIT_PARAMS_REQUEST_ID,
    .revision = 0
};

size_t length(const char* buf) {
    size_t s = 0;
    while (buf[s] != '\0') s++;
    return s;
}

void setup_display()
{
    // first get our framebuffer
    struct limine_framebuffer_response* fb_response = framebuffer_request.response;

    if (fb_response == NULL || fb_response->framebuffer_count < 1)
        hcf(); // just hang for now

    struct limine_framebuffer* framebuffer = fb_response->framebuffers[0];

    // then get the default parameters for flanterm
    struct limine_flanterm_fb_init_params_response* params_response = fb_params_request.response;
    
    if (params_response == NULL || params_response->entry_count < 1)
        hcf(); // just hang for now

    struct limine_flanterm_fb_init_params* params = params_response->entries[0];

    // finally initialize a flanterm context
    flanterm_ctx = flanterm_fb_init(
        NULL, NULL, // we don't have an allocator yet
        framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch,
        framebuffer->red_mask_size, framebuffer->red_mask_shift,
        framebuffer->green_mask_size, framebuffer->green_mask_shift,
        framebuffer->blue_mask_size, framebuffer->blue_mask_shift,
        params->canvas,
        params->ansi_colours, params->ansi_bright_colours,
        &params->default_bg,
        &params->default_fg,
        &params->default_bg_bright,
        &params->default_fg_bright,
        params->font, params->font_width, params->font_height, params->font_spacing,
        params->font_scale_x, params->font_scale_y,
        params->margin,
        params->rotation,
        true
    );
}

void write_char(const char c) {
    switch (c) {
        case '\n':
            flanterm_write(flanterm_ctx, &c, 1);
            size_t x, y;
            flanterm_get_cursor_pos(flanterm_ctx, &x, &y);
            flanterm_set_cursor_pos(flanterm_ctx, 0, y);
            break;
        default:
            flanterm_write(flanterm_ctx, &c, 1);
    }
}