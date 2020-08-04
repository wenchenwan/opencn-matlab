#ifndef FAKE_STDLIB_H
#define FAKE_STDLIB_H

#ifdef __KERNEL__
#include <linux/types.h>
void* calloc(size_t nmemb, size_t size);
void* malloc(size_t size);
void free(void* ptr);
#endif

#endif /* FAKE_STDLIB_H */
