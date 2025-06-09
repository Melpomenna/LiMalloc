#pragma once

#include <memory/export.h>
#include <memory/type.h>

#if defined(__cplusplus)
#include <stdexcept>
extern "C" {
#endif

MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(malloc)(mem_size_t bytes) MEMORY_NODISCARD MEMORY_CHECK_SIZE(1);
MEMORY_API mem_ptr_t MACHINE(calloc)(mem_size_t count, mem_size_t size) MEMORY_NODISCARD MEMORY_CHECK_SIZE(1, 2);
MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(realloc)(mem_ptr_t ptr, mem_size_t bytes) MEMORY_NODISCARD
    MEMORY_CHECK_SIZE(2);
MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(aligned_alloc)(mem_size_t alignment, mem_size_t bytes) MEMORY_NODISCARD
    MEMORY_CHECK_SIZE(1, 2);
MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(malloc_onlyfree)(mem_size_t bytes) MEMORY_NODISCARD MEMORY_CHECK_SIZE(1);
MEMORY_API mem_ptr_t MACHINE(calloc_onlyfree)(mem_size_t count, mem_size_t size) MEMORY_NODISCARD
    MEMORY_CHECK_SIZE(1, 2);
MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(realloc_onlyfree)(mem_ptr_t ptr, mem_size_t bytes) MEMORY_NODISCARD
    MEMORY_CHECK_SIZE(2);
MEMORY_API void MACHINE(free)(mem_ptr_t ptr);
MEMORY_API void MACHINE(free_onlyfree)(mem_ptr_t ptr);
MEMORY_API void MACHINE(defragmentation)(void);
MEMORY_API void MACHINE(hook)(void);
MEMORY_API void MACHINE(unhook)(void);

#if defined(__cplusplus)
}
#endif

#if defined(DISABLED)
#if defined(__cplusplus)
[[nodiscard]] void* operator new(std::size_t bytes)
{
    bytes += bytes == 0;
    mem_ptr_t ptr = MACHINE(malloc)(bytes);
    if (!ptr)
    {
        throw std::bad_alloc();
    }
    return ptr;
}

[[nodiscard]] void* operator new[](std::size_t bytes)
{
    bytes += bytes == 0;
    mem_ptr_t ptr = MACHINE(malloc)(bytes);
    if (!ptr)
    {
        throw std::bad_alloc();
    }
    return ptr;
}

void operator delete(void* ptr) noexcept
{
    MACHINE(free)(ptr);
}

void operator delete[](void* ptr) noexcept
{
    MACHINE(free)(ptr);
}

#endif
#endif

#if defined(malloc)
#undef malloc
#endif

#if defined(calloc)
#undef calloc
#endif

#if defined(realloc)
#undef realloc
#endif

#if defined(free)
#undef free
#endif

#if defined(malloc_onlyfree)
#undef malloc_onlyfree
#endif

#if defined(calloc_onlyfree)
#undef calloc_onlyfree
#endif

#if defined(realloc_onlyfree)
#undef realloc_onlyfree
#endif

#if defined(free_onlyfree)
#undef free_onlyfree
#endif

#if defined(aligned_alloc)
#undef aligned_alloc
#endif

#if defined(defragmentation)
#undef defragmentation
#endif

#define malloc(bytes) MACHINE(malloc)(bytes)
#define calloc(count, size) MACHINE(calloc)(count, size)
#define realloc(ptr, bytes) MACHINE(realloc)(ptr, bytes)
#define free(ptr) MACHINE(free)(ptr)
#define aligned_alloc(alignment, bytes) MACHINE(aligned_alloc)(alignment, bytes)
#define malloc_onlyfree(bytes) MACHINE(malloc_onlyfree)(bytes)
#define calloc_onlyfree(count, size) MACHINE(calloc_onlyfree)(count, size)
#define realloc_onlyfree(ptr, bytes) MACHINE(realloc_onlyfree)(ptr, bytes)
#define defragmentation() MACHINE(defragmentation)()
