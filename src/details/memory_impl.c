#include <memory/__details/internal.h>
#include <memory/__details/linked_list.h>
#include <memory/export.h>
#include <memory/type.h>

static mem_size_t getAlignedBytes(mem_size_t alignment, mem_size_t bytes)
{
    MEMORY_UNUSED(alignment);
    MEMORY_UNUSED(bytes);
    return 0;
}

void MACHINE_MEMORY_IMPL(defragmentation)(void);

mem_ptr_t MACHINE_MEMORY_IMPL(malloc)(mem_size_t bytes)
{
    Area_t* area = __getArena();
    area->kernelMutex.lock();
    if (bytes > area->root->freeSpace)
        __overCommit(bytes);
    area->kernelMutex.unlock();
    LinkedList_t* begin = area->root->begin;
    int needMerge = 0;
    needMerge = bytes % MEMORY_SPACE_SMALL == 0 && bytes != MEMORY_SPACE_SMALL;
    needMerge = bytes % MEMORY_SPACE_MEDIUM == 0 && bytes != MEMORY_SPACE_MEDIUM;
    needMerge = bytes % MEMORY_SPACE_LARGE == 0 && bytes != MEMORY_SPACE_LARGE;
    needMerge = bytes % MEMORY_SPACE_HUGE == 0 && bytes != MEMORY_SPACE_HUGE;
    if (needMerge)
    {
        MACHINE_MEMORY_IMPL(defragmentation)();
    }
    DEBUG_LOG("malloc(): trying to allocate %llu bytes, begin:%p end:%p\n", bytes, begin, area->root->end);
    for (; begin; begin = begin->next)
    {
        DEBUG_LOG("malloc(): checking node at %p with space %d and isFree %d\n", (void*)begin, begin->space, begin->isFree);
        area->kernelMutex.lock();
        if (begin->isFree && (mem_size_t)begin->space >= bytes)
        {
            begin->isFree = 0;
            area->root->freeSpace -= bytes;
            removeNode(area->root, begin);
            addNode(area->root, begin);
            area->kernelMutex.unlock();
            DEBUG_LOG("malloc(): allocated %llu bytes at %p\n", bytes, (void*)((char*)begin + sizeof(LinkedList_t)));
            return (void*)((char*)begin + sizeof(LinkedList_t));
        }
        area->kernelMutex.unlock();
    }
    return 0;
}

mem_ptr_t MACHINE_MEMORY_IMPL(aligned_alloc)(mem_size_t alignment, mem_size_t bytes)
{
    return MACHINE_MEMORY_IMPL(malloc)(getAlignedBytes(alignment, bytes));
}

mem_ptr_t MACHINE_MEMORY_IMPL(realloc)(mem_ptr_t ptr, mem_size_t bytes)
{
    MEMORY_UNUSED(ptr);
    MEMORY_UNUSED(bytes);
    return 0;
}

mem_ptr_t MACHINE_MEMORY_IMPL(malloc_onlyfree)(mem_size_t bytes)
{
    return MACHINE_MEMORY_IMPL(malloc)(bytes);
}

mem_ptr_t MACHINE_MEMORY_IMPL(realloc_onlyfree)(mem_ptr_t ptr, mem_size_t bytes)
{
    return MACHINE_MEMORY_IMPL(realloc)(ptr, bytes);
}

void MACHINE_MEMORY_IMPL(free)(mem_ptr_t ptr)
{
    Area_t* area = __getArena();
    LinkedList_t* node = (LinkedList_t*)((char*)ptr - sizeof(LinkedList_t));
    area->kernelMutex.lock();
    if (MEMORY_UNLIKY(node->isFree))
    {
        area->kernelMutex.unlock();
        return;
    }
    area->root->freeSpace += node->space;
    node->isFree = 1;
    removeNode(area->root, node);
    addFront(area->root, node);
    area->kernelMutex.unlock();
}

void MACHINE_MEMORY_IMPL(free_onlyfree)(mem_ptr_t ptr)
{
    MACHINE_MEMORY_IMPL(free)(ptr);
}

void MACHINE_MEMORY_IMPL(defragmentation)(void)
{

    
}
