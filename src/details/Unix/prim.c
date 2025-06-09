#include <dlfcn.h>
#include <memory/__details/internal.h>
#include <pthread.h>
#include <sys/sysctl.h>

extern void abort();

static pthread_mutex_t kernelMutex = PTHREAD_MUTEX_INITIALIZER;

func_allocate getAllocateFunction(void* lib)
{
    func_allocate allocFunc = dlsym(lib, "mmap");
    DEBUG_LOG("allocFunc:%p\n", allocFunc);
    if (MEMORY_UNLIKY(!allocFunc))
        abort();
    return allocFunc;
}

func_protect getProtectFunction(void* lib)
{
    func_protect protectFunc = dlsym(lib, "mprotect");
    DEBUG_LOG("protectFunc:%p\n", protectFunc);
    if (MEMORY_UNLIKY(!protectFunc))
        abort();
    return protectFunc;
}

func_deallocate getDeallocateFunction(void* lib)
{
    func_deallocate deallocateFunc = dlsym(lib, "munmap");
    DEBUG_LOG("func_deallocate:%p\n", deallocateFunc);
    if (MEMORY_UNLIKY(!deallocateFunc))
        abort();
    return deallocateFunc;
}

void* getKernelLibHandle()
{
#if OS_MAC
    char libName[] = "libc.dylib";
#elif OS_LINUX
    char libName[] = "libc.so.6";
#endif
    void* lib = dlopen(libName, RTLD_LAZY);
    DEBUG_LOG("OpenLib:%p\n", lib);
    if (MEMORY_UNLIKY(!lib))
        abort();
    return lib;
}

void freeKernleLibHandle(void* lib)
{
    dlclose(lib);
}

void lockSection()
{
    pthread_mutex_lock(&kernelMutex);
}

void unlockSection()
{
    pthread_mutex_unlock(&kernelMutex);
}
