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

static mem_size_t getNearestBytes(mem_size_t bytes)
{
    return (bytes % MEMORY_SPACE_HUGE == 0 && bytes != MEMORY_SPACE_HUGE) || (bytes > MEMORY_SPACE_LARGE && bytes <= MEMORY_SPACE_HUGE) || bytes > MEMORY_SPACE_HUGE? MEMORY_SPACE_HUGE
        : (bytes % MEMORY_SPACE_LARGE == 0 && bytes != MEMORY_SPACE_LARGE) || (bytes > MEMORY_SPACE_MEDIUM && bytes <= MEMORY_SPACE_LARGE)? MEMORY_SPACE_LARGE
        : (bytes % MEMORY_SPACE_MEDIUM == 0 && bytes != MEMORY_SPACE_MEDIUM) || (bytes > MEMORY_SPACE_SMALL && bytes <= MEMORY_SPACE_MEDIUM)? MEMORY_SPACE_MEDIUM
                                                                             : MEMORY_SPACE_SMALL;
}

static LinkedList_t* getNearestFirstFreeNodeBySize(LinkedList_t* root, mem_size_t bytes)
{
    LinkedList_t* begin = root;

    while (begin && (begin->space < bytes || !begin->isFree))
    {
        begin = begin->next;
    }

    return begin;
}

void MACHINE_MEMORY_IMPL(defragmentation)(void);

mem_ptr_t MACHINE_MEMORY_IMPL(malloc)(mem_size_t bytes)
{
    Area_t* area = __getArena();
    area->kernelMutex.lock();
    if (bytes > area->root->freeSpace)
    {
        __overCommit(bytes);
        if (bytes > area->root->freeSpace)
        {
            area->kernelMutex.unlock();
            return 0;
        }

    }
    area->kernelMutex.unlock();
    LinkedList_t* begin = area->root->begin;
    int needMergeBySmallSpace = bytes % MEMORY_SPACE_SMALL == 0 && bytes != MEMORY_SPACE_SMALL;
    int needMergeByMediumSpace = bytes % MEMORY_SPACE_MEDIUM == 0 && bytes != MEMORY_SPACE_MEDIUM;
    int needMergeByLargeSpace = bytes % MEMORY_SPACE_LARGE == 0 && bytes != MEMORY_SPACE_LARGE;
    int needMergeByHugeSpace = bytes % MEMORY_SPACE_HUGE == 0 && bytes != MEMORY_SPACE_HUGE;
    if (needMergeBySmallSpace || needMergeByHugeSpace || needMergeByMediumSpace || needMergeByLargeSpace)
    {
        MACHINE_MEMORY_IMPL(defragmentation)();
        mem_size_t nearestBytes = getNearestBytes(bytes);
        area->kernelMutex.lock();
        LinkedList_t* nearest = getNearestFirstFreeNodeBySize(begin, nearestBytes);
        area->kernelMutex.unlock();

        if (nearest)
        {
            mem_size_t totalBytes = nearest->space;
            while (totalBytes < bytes)
            {
                area->kernelMutex.lock();
                LinkedList_t* node = mergeNode(area->root, nearest, nearest->next);
                if (!node)
                {
                    area->kernelMutex.unlock();
                    break; // TODO: what to do here?
                }
                totalBytes = node->space;
                area->kernelMutex.unlock();
            }
            begin = nearest;
        }
        else
        {
            // TODO: what to do here?
        }
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
