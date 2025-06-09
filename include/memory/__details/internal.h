#pragma once

#include <memory/export.h>
#include <memory/type.h>

#if OS_LINUX || OS_MAC
#include <sys/mman.h>
typedef mem_ptr_t (*func_allocate)(mem_ptr_t, mem_size_t, int, int, int, int);
typedef int (*func_protect)(mem_ptr_t, mem_size_t, int);
typedef int (*func_deallocate)(mem_ptr_t, mem_size_t);

typedef enum PageAccess
{
    MEMORY_PAGE_READ = PROT_READ,
    MEMORY_PAGE_WRITE = PROT_WRITE,
    MEMORY_PAGE_EXEC = PROT_EXEC,
    MEMORY_PAGE_NONE = PROT_NONE,
    MEMORY_PAGE_READ_WRITE = PROT_READ | PROT_WRITE,
} PageAccess_t;

typedef enum MemoryMapFlags
{
    MEMORY_MAP_FIXED = MAP_FIXED,
    MEMORY_MAP_SHARED = MAP_SHARED,
    MEMORY_MAP_PRIVATE = MAP_PRIVATE,
    MEMORY_MAP_ANONYMOUS = MAP_ANONYMOUS
} MemoryMapFlags_t;

#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef mem_ptr_t (*func_allocate)(LPVOID, SIZE_T, DWORD, DWORD);
typedef int (*func_protect)(LPVOID, SIZE_T, DWORD, PDWORD);
typedef int (*func_deallocate)(LPVOID, SIZE_T, DWORD);
typedef enum PageAccess
{
    MEMORY_PAGE_READ = PAGE_READONLY,
    MEMORY_PAGE_WRITE = PAGE_WRITECOPY,
    MEMORY_PAGE_EXEC = PAGE_EXECUTE,
    MEMORY_PAGE_NONE = PAGE_NOACCESS,
    MEMORY_PAGE_READ_WRITE = PAGE_READWRITE,
} PageAccess_t;

typedef enum MemAllocFreeType
{
MEMORY_COMMIT = MEM_COMMIT                ,    
MEMORY_RESERVE = MEM_RESERVE                 ,  
MEMORY_REPLACE_PLACEHOLDER = MEM_REPLACE_PLACEHOLDER       ,
MEMORY_RESERVE_PLACEHOLDER = MEM_RESERVE_PLACEHOLDER       ,
MEMORY_RESET = MEM_RESET                     ,
MEMORY_TOP_DOW = MEM_TOP_DOWN                  ,
MEMORY_WRITE_WATCH = MEM_WRITE_WATCH               ,
MEMORY_PHYSICAL = MEM_PHYSICAL                  ,
MEMORY_ROTATE = MEM_ROTATE                    ,
MEMORY_DIFFERENT_IMAGE_BASE_OK = MEM_DIFFERENT_IMAGE_BASE_OK   ,
MEMORY_RESET_UNDO = MEM_RESET_UNDO                ,
MEMORY_LARGE_PAGES = MEM_LARGE_PAGES               ,
MEMORY_4MB_PAGES = MEM_4MB_PAGES                 ,
MEMORY_64K_PAGES = MEM_64K_PAGES                 ,
MEMORY_UNMAP_WITH_TRANSIENT_BOOST = MEM_UNMAP_WITH_TRANSIENT_BOOST,
MEMORY_COALESCE_PLACEHOLDERS      = MEM_COALESCE_PLACEHOLDERS     ,
MEMORY_PRESERVE_PLACEHOLDER       = MEM_PRESERVE_PLACEHOLDER      ,
MEMORY_DECOMMIT                   = MEM_DECOMMIT                  ,
MEMORY_RELEASE                    = MEM_RELEASE                   ,
MEMORY_FREE                       = MEM_FREE                      ,
} MemAllocFreeType_t;

#endif

#ifndef NDEBUG
#if defined(ENABLE_TESTING_LOG_OUT)
#include <stdio.h>
#define DEBUG_LOG(__format, ...) printf(__format, __VA_ARGS__)
#else
#define DEBUG_LOG(...)
#endif
#else
#define DEBUG_LOG(...)
#endif

#if OS_LINUX || OS_MAC
#define MEMORY_INIT __attribute__((constructor))
#define MEMORY_DESTRUCTOR __attribute__((destructor))
#else
#define MEMORY_INIT
#define MEMORY_DESTRUCTOR
#endif

typedef void(MEMORY_CALL* func_lock)(void);
typedef void(MEMORY_CALL* func_unlock)(void);

typedef enum PageSpace
{
    MEMORY_SPACE_SMALL = 8,
    MEMORY_SPACE_MEDIUM = 64,
    MEMORY_SPACE_LARGE = 128,
    MEMORY_SPACE_HUGE = 512
} PageSpace_t;


#define MEMORY_HUGE_PAGES_COUNT 256
#define MEMORY_LARGE_PAGES_COUNT 512
#define MEMORY_MEDIUM_PAGES_COUNT 1024
#define MEMORY_SMALL_PAGES_COUNT 2048

struct LinkedList;
struct ComprassedPair;

#define MEMORY_HUGE_PAGE_SPACE MEMORY_HUGE_PAGES_COUNT*(MEMORY_SPACE_HUGE + sizeof(struct LinkedList))
#define MEMORY_LARGE_PAGE_SPACE MEMORY_LARGE_PAGES_COUNT*(MEMORY_SPACE_LARGE + sizeof(struct LinkedList))
#define MEMORY_MEDIUM_PAGE_SPACE MEMORY_MEDIUM_PAGES_COUNT*(MEMORY_SPACE_MEDIUM + sizeof(struct LinkedList))
#define MEMORY_SMALL_PAGE_SPACE MEMORY_SMALL_PAGES_COUNT*(MEMORY_SPACE_SMALL + sizeof(struct LinkedList))
#define MEMORY_DEFAULT_SPACE                                                                                           \
    MEMORY_SMALL_PAGE_SPACE + MEMORY_MEDIUM_PAGE_SPACE + MEMORY_LARGE_PAGE_SPACE + MEMORY_HUGE_PAGE_SPACE

typedef struct Allocator
{
    func_allocate allocate;
    func_protect protect;
    func_deallocate deallocate;
} Allocator_t;

typedef struct KernelMutex
{
    func_lock lock;
    func_unlock unlock;
} KernelMutex_t;

typedef struct Area
{
    Allocator_t allocator;
    KernelMutex_t kernelMutex;
    struct ComprassedPair* root;
    mem_size_t isInited;
} Area_t;


#if defined(__cplusplus)
extern "C" {
#endif

MEMORY_API Area_t* MEMORY_CALL __getArena();
MEMORY_API void MEMORY_CALL __overCommit(mem_size_t bytes);

#if defined(__cplusplus)
}
#endif
