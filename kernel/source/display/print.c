
#include "print.h"
#include "framebuffer.h"

#include <stddef.h>

void kprint(const char* msg)
{
    size_t pos = 0;
    while (msg[pos] != '\0')
        write_char(msg[pos++]);

    write_char('\n');
}