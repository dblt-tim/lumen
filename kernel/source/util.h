// util.h
// 
//
#include <stddef.h>
#include <stdint.h>

#ifndef UTIL_H
#define UTIL_H
/// copy the values to an address to another
void *memcpy (
    void *dest, // destination ptr
    const void *src, // source ptr
    size_t n // size
);

/// set values to an address
void *memset (
    void *s, // destination ptr
    int c, // value
    size_t n // size
);

/// move values from an address to another
void *memmove (
    void *dest, // destination ptr
    const void *src, // source ptr
    size_t n // size
);

/// compare two addresses
int memcmp (
    const void *s1, // LHS
    const void *s2, // RHS
    size_t n // size
);
void hcf(void);

/// klog function
// types :
// - 0 : info
// - 1 : error
void klog(int type, char* msg);
#endif
