#include <memory/__details/internal.h>
#include <memory/__details/linked_list.h>

static Area_t memoryPoolArea;
static ComprassedPair_t comprassedPair;

extern func_allocate getAllocateFunction(void*);
extern func_protect getProtectFunction(void*);
extern func_deallocate getDeallocateFunction(void*);
extern void* getKernelLibHandle();
extern void freeKernleLibHandle(void*);
extern void MEMORY_CALL lockSection();
extern void MEMORY_CALL unlockSection();
extern void abort();

static void* createListSection(ComprassedPair_t* root, void* mem, int count, int space)
{
    void* ptr = mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, space);
        addNode(root, node);
        ptr = (void*)((char*)ptr + (space + sizeof(LinkedList_t)));
    }
    return ptr;
}

void MEMORY_INIT MEMORY_CALL __init()
{
    lockSection();
    DEBUG_LOG("%s\n", "__init()");
    if (MEMORY_UNLIKY(memoryPoolArea.isInited == 1))
    {
        unlockSection();
        return;
    }
    void* lib = getKernelLibHandle();
    memoryPoolArea.allocator.allocate = getAllocateFunction(lib);
    memoryPoolArea.allocator.protect = getProtectFunction(lib);
    memoryPoolArea.allocator.deallocate = getDeallocateFunction(lib);
    memoryPoolArea.kernelMutex.lock = (func_lock)&lockSection;
    memoryPoolArea.kernelMutex.unlock = (func_unlock)&unlockSection;
    comprassedPair.begin = 0;
    comprassedPair.end = 0;
    memoryPoolArea.root = &comprassedPair;
    mem_size_t totalAllocatedSpace = MEMORY_DEFAULT_SPACE;
    memoryPoolArea.root->freeSpace = totalAllocatedSpace;
#if OS_LINUX || OS_MAC
    DEBUG_LOG("__init(): totalSpace:%llu\n", totalAllocatedSpace);
    void* mem = memoryPoolArea.allocator.allocate(0, totalAllocatedSpace, MEMORY_PAGE_READ | MEMORY_PAGE_WRITE,
                                                  MEMORY_MAP_PRIVATE | MEMORY_MAP_ANONYMOUS, 0, 0);

#else
    DEBUG_LOG("__init(): totalSpace:%llu\n", totalAllocatedSpace);
    VirtualAlloc(0, totalAllocatedSpace, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    void* mem = memoryPoolArea.allocator.allocate(0, totalAllocatedSpace, MEMORY_COMMIT | MEMORY_RESERVE, MEMORY_PAGE_READ_WRITE);
#endif
    if (MEMORY_UNLIKY(!mem))
    {
        DEBUG_LOG("Cannot allocate:%llu bytes\n", totalAllocatedSpace);
        abort();
    }
    DEBUG_LOG("__init(): base ptr:%p, end ptr:%p\n", mem, (void*)((char*)mem + totalAllocatedSpace));
    mem = createListSection(memoryPoolArea.root, mem, MEMORY_SMALL_PAGES_COUNT, MEMORY_SPACE_SMALL);
    mem = createListSection(memoryPoolArea.root, mem, MEMORY_MEDIUM_PAGES_COUNT, MEMORY_SPACE_MEDIUM);
    mem = createListSection(memoryPoolArea.root, mem, MEMORY_LARGE_PAGES_COUNT, MEMORY_SPACE_LARGE);
    mem = createListSection(memoryPoolArea.root, mem, MEMORY_HUGE_PAGES_COUNT, MEMORY_SPACE_HUGE);
    memoryPoolArea.isInited = 1;
    unlockSection();
    freeKernleLibHandle(lib);
}

void MEMORY_DESTRUCTOR MEMORY_CALL __exit()
{
    lockSection();
    if (MEMORY_UNLIKY(memoryPoolArea.isInited == 0))
        return;
    DEBUG_LOG("%s\n", "__exit()");
#if OS_WIN
    memoryPoolArea.allocator.deallocate((void*)memoryPoolArea.root, MEMORY_DEFAULT_SPACE, MEMORY_RELEASE);
#else
    memoryPoolArea.allocator.deallocate((void*)memoryPoolArea.root, MEMORY_DEFAULT_SPACE);
#endif
    memoryPoolArea.isInited = 0;
    unlockSection();
}

Area_t* __getArena()
{
    return &memoryPoolArea;
}

void __overCommit(mem_size_t bytes)
{
    MEMORY_UNUSED(bytes);
}

#if OS_WIN
#pragma section(".CRT$XCU", read)
__declspec(allocate(".CRT$XCU")) void(MEMORY_CALL* __init_ptr)(void) = (void(MEMORY_CALL*)(void)) & __init;

#pragma section(".CRT$XPU", read)
__declspec(allocate(".CRT$XPU")) void(MEMORY_CALL* __destructor_ptr)(void) = (void(MEMORY_CALL*)(void)) & __exit;
#endif
