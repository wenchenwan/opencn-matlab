/*FILE FORMAT:
struct timespec prof_tstart, prof_tend
number of profile blocks
array of blocks*/

#ifndef TIME_PROF_H
#define TIME_PROF_H

#ifndef __KERNEL__
#include <assert.h>
#include <dlfcn.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#ifndef PROF_LOG_ENTRIES
#define PROF_LOG_ENTRIES 1000
#endif

#ifndef PROF_STRING_MAX_ADDRESS
#define PROF_STRING_MAX_ADDRESS 0xd80000
#endif

#ifdef PROF_DEBUG
#define PROF_PRINT(...) fprintf(stderr, __VA_ARGS__);
#define PROF_PRINT_OFFSET(off)                                                                                         \
    {                                                                                                                  \
        for (int i = 0; i < off; ++i) {                                                                                \
            fprintf(stderr, "  ");                                                                                     \
        }                                                                                                              \
    }
#else
#define PROF_PRINT(...)
#define PROF_PRINT_OFFSET(off)
#endif

/* zone ids are the addresses of the static strings used for zone names,
they should fit into 32 bits*/
typedef uint32_t zone_id_t;

typedef enum { LOG_ZONE, LOG_END } LOG_TYPE;

#pragma pack(push, 1)
typedef struct profile_log {
    struct timespec t;
    zone_id_t zone_id;
    pid_t thread_id;
    LOG_TYPE type;
} profile_log_t;
#pragma pack(pop)

#ifdef PROF_ACTIVE

profile_log_t *prof_get_log_ptr();
pid_t prof_get_thread_id();
zone_id_t prof_get_zone_id(const char *zone_name);

void PROF_START(const char *filename);
void PROF_END();
void PROF_DUMP(profile_log_t *log_ptr);

extern profile_log_t *prof_log;
extern struct timespec prof_tstart, prof_tend;
extern int prof_start_was_called;
extern int prof_end_was_called;
extern uint8_t *rodata_string_addr;

#define PROF_IN(name)                                                                                                  \
    {                                                                                                                  \
        profile_log_t *p_log = prof_get_log_ptr();                                                                     \
        p_log->thread_id = prof_get_thread_id();                                                                       \
        p_log->zone_id = prof_get_zone_id(#name);                                                                      \
        p_log->type = LOG_ZONE;                                                                                        \
        rodata_string_addr[p_log->zone_id] = 1;                                                                        \
        clock_gettime(CLOCK_MONOTONIC, &p_log->t);                                                                     \
        PROF_PRINT("PROF_IN (thread_id=%d, name=%s, zone_id=%p, entry=%p)\n", p_log->thread_id, #name, p_log->zone_id, \
                   p_log);                                                                                             \
    }

#define PROF_OUT(name)                                                                                                 \
    {                                                                                                                  \
        struct timespec t2;                                                                                            \
        clock_gettime(CLOCK_MONOTONIC, &t2);                                                                           \
        profile_log_t *p_log = prof_get_log_ptr();                                                                     \
        p_log->thread_id = prof_get_thread_id();                                                                       \
        p_log->zone_id = prof_get_zone_id(#name);                                                                      \
        p_log->type = LOG_END;                                                                                         \
        p_log->t = t2;                                                                                                 \
        PROF_PRINT("PROF_OUT(thread_id=%d, name=%s, zone_id=%p, entry=%p)\n", p_log->thread_id, #name, p_log->zone_id, \
                   p_log);                                                                                             \
    }

#define PROF_IN_STR(name)                                                                                              \
    {                                                                                                                  \
        profile_log_t *p_log = prof_get_log_ptr();                                                                     \
        p_log->thread_id = prof_get_thread_id();                                                                       \
        p_log->zone_id = prof_get_zone_id(name);                                                                       \
        p_log->type = LOG_ZONE;                                                                                        \
        rodata_string_addr[p_log->zone_id] = 1;                                                                        \
        clock_gettime(CLOCK_MONOTONIC, &p_log->t);                                                                     \
        PROF_PRINT("PROF_IN_STR (thread_id=%d, name=%s, zone_id=%p, entry=%p)\n", p_log->thread_id, name,              \
                   p_log->zone_id, p_log);                                                                             \
    }

#define PROF_OUT_STR(name)                                                                                             \
    {                                                                                                                  \
        struct timespec t2;                                                                                            \
        clock_gettime(CLOCK_MONOTONIC, &t2);                                                                           \
        profile_log_t *p_log = prof_get_log_ptr();                                                                     \
        p_log->thread_id = prof_get_thread_id();                                                                       \
        p_log->zone_id = prof_get_zone_id(name);                                                                       \
        p_log->type = LOG_END;                                                                                         \
        p_log->t = t2;                                                                                                 \
        PROF_PRINT("PROF_OUT_STR(thread_id=%d, name=%s, zone_id=%p, entry=%p)\n", p_log->thread_id, name,              \
                   p_log->zone_id, p_log);                                                                             \
    }

#ifdef __cplusplus
struct prof_block_t {
    prof_block_t(const char *zone_name) : zone_name_(zone_name) { PROF_IN_STR(zone_name_); }
    ~prof_block_t() { PROF_OUT_STR(zone_name_); }
    const char *zone_name_;
};
#ifdef PROF_ACTIVE
#define PROF_BLOCK(name)                                                                                               \
    PROF_PRINT("PROF_BLOCK(%s)\n", #name);                                                                             \
    prof_block_t __prof_block_##name{#name};

#define PROF_FUNC                                                                                                      \
    PROF_PRINT("PROF_FUNC(%s)\n", __FUNCTION__);                                                                       \
    prof_block_t __prof_block_func{__FUNCTION__};
#endif /* PROF_ACTIVE */
#endif /* __cplusplus */

#ifdef PROF_IMPLEMENTATION

/* returns elapsed time in nanoseconds */
uint64_t prof_get_time_diff(struct timespec *t1, struct timespec *t2) {
    return (t2->tv_sec - t1->tv_sec) * 1000000000 + t2->tv_nsec - t1->tv_nsec;
}
uint32_t prof_last_log_index = 0;
uint32_t prof_total_log_count = 0;
profile_log_t prof_log_rot1[PROF_LOG_ENTRIES];
profile_log_t prof_log_rot2[PROF_LOG_ENTRIES];
profile_log_t *prof_log = prof_log_rot1;
struct timespec prof_tstart, prof_tend;
int prof_start_was_called = 0;
int prof_end_was_called = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *base_address = 0;
size_t last_file_write_position = 0;

uint8_t *rodata_string_addr;

uint32_t last_zone_name = 0;

FILE *prof_file_handle = 0;

pid_t prof_get_thread_id() { return syscall(__NR_gettid); }

zone_id_t prof_get_zone_id(const char *zone_name) { return (zone_id_t)(size_t)(zone_name - (char *)base_address); }

profile_log_t *prof_get_log_ptr() {
    pthread_mutex_lock(&mutex);
    if (prof_last_log_index >= PROF_LOG_ENTRIES) {
        PROF_DUMP(prof_log);
        prof_total_log_count += prof_last_log_index;
        prof_last_log_index = 0;
        prof_log = prof_log == prof_log_rot1 ? prof_log_rot2 : prof_log_rot1;
        /* fprintf(stderr, "Swapping log queues\n"); */
    }
    pthread_mutex_unlock(&mutex);
    return prof_log + prof_last_log_index++;
}

extern char __etext;

void PROF_START(const char *filename) {
    rodata_string_addr = (uint8_t *)malloc(PROF_STRING_MAX_ADDRESS);
    fprintf(stderr, "PROFILING STARTED\n");

    prof_file_handle = fopen(filename, "w");

    printf(".text: 0x%lx\n", (unsigned long)&__etext);

    /* Dl_info info;
    int result = dladdr((void *)PROF_START, &info);
    printf("fname: %s\nfbase: %p\nsname: %s\nsaddr: %p\n", info.dli_fname,
           info.dli_fbase, info.dli_sname, info.dli_saddr);*/

    base_address = (void *)(size_t)&__etext;

    clock_gettime(CLOCK_MONOTONIC, &prof_tstart);
    fwrite(&prof_tstart, sizeof(prof_tstart), 1, prof_file_handle);
    fwrite(&prof_tstart, sizeof(prof_tstart), 1, prof_file_handle);
    fwrite(&prof_total_log_count, sizeof(prof_total_log_count), 1, prof_file_handle);
}

void PROF_END() {
    clock_gettime(CLOCK_MONOTONIC, &prof_tend);
    prof_total_log_count += prof_last_log_index;
    PROF_DUMP(prof_log);

    fseek(prof_file_handle, 1 * sizeof(struct timespec), SEEK_SET);
    fwrite(&prof_tend, sizeof(prof_tend), 1, prof_file_handle);
    fwrite(&prof_total_log_count, sizeof(prof_total_log_count), 1, prof_file_handle);

    uint64_t time_max = prof_get_time_diff(&prof_tstart, &prof_tend);

    fprintf(stderr, "total log count: %lu\n", prof_total_log_count);
    fprintf(stderr, "total profiling time: %llu ms\n", time_max / 1000000);
    fprintf(stderr, "PROFILING ENDED\n");

    fseek(prof_file_handle, last_file_write_position, SEEK_SET);
    uint32_t string_count = 0;
    fwrite(&string_count, sizeof(string_count), 1, prof_file_handle);

    for (int i = 0; i < PROF_STRING_MAX_ADDRESS; i++) {
        if (rodata_string_addr[i]) {
            const char *addr = (const char *)(i + (uint64_t)base_address);
            printf("found name: '%s' at %p\n", addr, i);
            fwrite(&i, sizeof(uint32_t), 1, prof_file_handle);
            fwrite(addr, strlen(addr), 1, prof_file_handle);
            fputc('\n', prof_file_handle); /* needed for fgets */
            ++string_count;
        }
    }

    fseek(prof_file_handle, last_file_write_position, SEEK_SET);
    fwrite(&string_count, sizeof(string_count), 1, prof_file_handle);

    fclose(prof_file_handle);

    free(rodata_string_addr);
}

void PROF_DUMP(profile_log_t *log_ptr) {
    /* write log
       fprintf(stderr, "dumping %d entries\n", prof_last_log_index); */
    fwrite(log_ptr, sizeof(profile_log_t) * prof_last_log_index, 1, prof_file_handle);
    last_file_write_position = ftell(prof_file_handle);
}

#endif /* PROF_IMPLEMENTATION */

#else
#define PROF_IN(name)
#define PROF_OUT(name)
#define PROF_START(filename)
#define PROF_END()
#define PROF_DUMP(log_ptr)
#define PROF_BLOCK(name)
#define PROF_FUNC
#endif /* PROF_ACTIVE */

#else /* __KERNEL__ */
#define PROF_IN(name)
#define PROF_OUT(name)
#define PROF_START(filename)
#define PROF_END()
#define PROF_DUMP(log_ptr)
#define PROF_BLOCK(name)
#define PROF_FUNC
#endif /* __KERNEL__ */

#endif /* TIME_PROF_H */
