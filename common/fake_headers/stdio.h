#ifndef FAKE_STDIO_H
#define FAKE_STDIO_H

#ifdef __KERNEL__
#include <opencn/strings.h>
#define printf(...) opencn_printf(__VA_ARGS__)
#define fflush(stream)


#endif

#endif
