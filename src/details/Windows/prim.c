#include <memory/__details/internal.h>

static CRITICAL_SECTION cs;
static int initialized = 0;

extern void abort();

func_allocate getAllocateFunction(void* handle)
{
    func_allocate allocFunc = (func_allocate)GetProcAddress(handle, "VirtualAlloc");
    if (!allocFunc)
        abort();
    return allocFunc;
}

func_protect getProtectFunction(void* handle)
{
    func_protect protectFunc = (func_protect)GetProcAddress(handle, "VirtualProtect");
    if (!protectFunc)
        abort();
    return protectFunc;
}

func_deallocate getDeallocateFunction(void* handle)
{
    func_deallocate deallocateFunc = (func_deallocate)GetProcAddress(handle, "VirtualFree");
    if (!deallocateFunc)
        abort();
    return deallocateFunc;
}

void* getKernelLibHandle()
{
    void* handle = LoadLibraryA("kernel32.dll");
    if (!handle)
        abort();
    return handle;
}

void freeKernleLibHandle(void* handle)
{
    FreeLibrary((HMODULE)handle);
}

void MEMORY_CALL lockSection()
{
    if (!initialized)
    {
        InitializeCriticalSection(&cs);
        initialized = 1;
    }

    EnterCriticalSection(&cs);
}

void MEMORY_CALL unlockSection()
{
    if (initialized)
        LeaveCriticalSection(&cs);
}
