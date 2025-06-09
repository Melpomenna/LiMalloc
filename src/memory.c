#include <memory/memory.h>

extern void* memset(void*, int, long unsigned int);
extern mem_ptr_t MACHINE_MEMORY_IMPL(malloc)(mem_size_t);
extern mem_ptr_t MACHINE_MEMORY_IMPL(aligned_alloc)(mem_size_t, mem_size_t);
extern mem_ptr_t MACHINE_MEMORY_IMPL(realloc)(mem_ptr_t, mem_size_t);
extern mem_ptr_t MACHINE_MEMORY_IMPL(malloc_onlyfree)(mem_size_t);
extern mem_ptr_t MACHINE_MEMORY_IMPL(realloc_onlyfree)(mem_ptr_t, mem_size_t);
extern void MACHINE_MEMORY_IMPL(free)(mem_ptr_t);
extern void MACHINE_MEMORY_IMPL(free_onlyfree)(mem_ptr_t);
extern void MACHINE_MEMORY_IMPL(defragmentation)(void);

mem_ptr_t MACHINE(malloc)(mem_size_t bytes)
{
    MEMORY_UNUSED(bytes);
    if (MEMORY_UNLIKY(bytes == 0))
        return 0;
    return MACHINE_MEMORY_IMPL(malloc)(bytes);
}

void* MACHINE(calloc)(mem_size_t count, mem_size_t size)
{
    if (MEMORY_UNLIKY(count == 0 || size == 0))
        return 0;
    mem_ptr_t ptr = MACHINE(malloc)(count * size);
    if (MEMORY_UNLIKY(!ptr))
        return ptr;
    memset(ptr, 0, (unsigned long)(count * size));
    return ptr;
}

mem_ptr_t MACHINE(realloc)(mem_ptr_t ptr, mem_size_t bytes)
{
    return MACHINE_MEMORY_IMPL(realloc)(ptr, bytes);
}

mem_ptr_t MACHINE(aligned_alloc)(mem_size_t alignment, mem_size_t bytes)
{
    return MACHINE_MEMORY_IMPL(aligned_alloc)(alignment, bytes);
}

mem_ptr_t MACHINE(malloc_onlyfree)(mem_size_t bytes)
{
    return MACHINE_MEMORY_IMPL(malloc_onlyfree)(bytes);
}

mem_ptr_t MACHINE(calloc_onlyfree)(mem_size_t count, mem_size_t size)
{
    if (MEMORY_UNLIKY(count == 0 || size == 0))
        return 0;
    mem_ptr_t ptr = MACHINE(malloc_onlyfree)(count * size);
    if (MEMORY_UNLIKY(!ptr))
        return ptr;
    memset(ptr, 0, (unsigned long)(count * size));
    return ptr;
}

mem_ptr_t MACHINE(realloc_onlyfree)(mem_ptr_t ptr, mem_size_t bytes)
{
    return MACHINE_MEMORY_IMPL(realloc_onlyfree)(ptr, bytes);
}

void MACHINE(free)(mem_ptr_t ptr)
{
    if (MEMORY_UNLIKY(!ptr))
        return;
    MACHINE_MEMORY_IMPL(free)(ptr);
}

void MACHINE(free_onlyfree)(mem_ptr_t ptr)
{
    if (MEMORY_UNLIKY(!ptr))
        return;
    MACHINE_MEMORY_IMPL(free_onlyfree)(ptr);
}

void MACHINE(defragmentation)(void)
{
    MACHINE_MEMORY_IMPL(defragmentation)();
}
