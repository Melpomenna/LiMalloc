/**
 * @file internal.h
 * @brief Internal memory management definitions and platform-specific abstractions.
 *
 * This header provides platform-specific types, constants, and function pointer typedefs
 * for memory allocation, protection, and deallocation. It also defines structures and
 * enums used by the memory management subsystem, including page access flags, mapping flags,
 * and allocator interfaces. Debug logging macros and initialization attributes are also provided.
 *
 * @note This file is intended for internal use within the memory subsystem.
 */

#pragma once

#include <memory/export.h>
#include <memory/type.h>

#if OS_LINUX || OS_MAC
#include <sys/mman.h>

/**
 * @typedef func_allocate
 * @brief Function pointer type for memory allocation on POSIX systems.
 */
typedef mem_ptr_t (*func_allocate)(mem_ptr_t, mem_size_t, int, int, int, int);

/**
 * @typedef func_protect
 * @brief Function pointer type for memory protection on POSIX systems.
 */
typedef int (*func_protect)(mem_ptr_t, mem_size_t, int);

/**
 * @typedef func_deallocate
 * @brief Function pointer type for memory deallocation on POSIX systems.
 */
typedef int (*func_deallocate)(mem_ptr_t, mem_size_t);

/**
 * @enum PageAccess
 * @brief Page access permissions for memory pages (POSIX).
 */
typedef enum PageAccess
{
    MEMORY_PAGE_READ = PROT_READ,                /**< Read access */
    MEMORY_PAGE_WRITE = PROT_WRITE,              /**< Write access */
    MEMORY_PAGE_EXEC = PROT_EXEC,                /**< Execute access */
    MEMORY_PAGE_NONE = PROT_NONE,                /**< No access */
    MEMORY_PAGE_READ_WRITE = PROT_READ | PROT_WRITE /**< Read and write access */
} PageAccess_t;

/**
 * @enum MemoryMapFlags
 * @brief Memory mapping flags for mmap (POSIX).
 */
typedef enum MemoryMapFlags
{
    MEMORY_MAP_FIXED = MAP_FIXED,                /**< Map at fixed address */
    MEMORY_MAP_SHARED = MAP_SHARED,              /**< Share changes */
    MEMORY_MAP_PRIVATE = MAP_PRIVATE,            /**< Private mapping */
    MEMORY_MAP_ANONYMOUS = MAP_ANONYMOUS         /**< Anonymous mapping */
} MemoryMapFlags_t;

#else
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/**
 * @typedef func_allocate
 * @brief Function pointer type for memory allocation on Windows.
 */
typedef mem_ptr_t (*func_allocate)(LPVOID, SIZE_T, DWORD, DWORD);

/**
 * @typedef func_protect
 * @brief Function pointer type for memory protection on Windows.
 */
typedef int (*func_protect)(LPVOID, SIZE_T, DWORD, PDWORD);

/**
 * @typedef func_deallocate
 * @brief Function pointer type for memory deallocation on Windows.
 */
typedef int (*func_deallocate)(LPVOID, SIZE_T, DWORD);

/**
 * @enum PageAccess
 * @brief Page access permissions for memory pages (Windows).
 */
typedef enum PageAccess
{
    MEMORY_PAGE_READ = PAGE_READONLY,            /**< Read-only access */
    MEMORY_PAGE_WRITE = PAGE_WRITECOPY,          /**< Write-copy access */
    MEMORY_PAGE_EXEC = PAGE_EXECUTE,             /**< Execute access */
    MEMORY_PAGE_NONE = PAGE_NOACCESS,            /**< No access */
    MEMORY_PAGE_READ_WRITE = PAGE_READWRITE      /**< Read and write access */
} PageAccess_t;

/**
 * @enum MemAllocFreeType
 * @brief Memory allocation and free types for Windows VirtualAlloc/VirtualFree.
 */
typedef enum MemAllocFreeType
{
    MEMORY_COMMIT = MEM_COMMIT,                          /**< Commit memory */
    MEMORY_RESERVE = MEM_RESERVE,                        /**< Reserve memory */
    MEMORY_REPLACE_PLACEHOLDER = MEM_REPLACE_PLACEHOLDER,/**< Replace placeholder */
    MEMORY_RESERVE_PLACEHOLDER = MEM_RESERVE_PLACEHOLDER,/**< Reserve placeholder */
    MEMORY_RESET = MEM_RESET,                            /**< Reset memory */
    MEMORY_TOP_DOW = MEM_TOP_DOWN,                       /**< Top-down allocation */
    MEMORY_WRITE_WATCH = MEM_WRITE_WATCH,                /**< Write-watch */
    MEMORY_PHYSICAL = MEM_PHYSICAL,                      /**< Physical memory */
    MEMORY_ROTATE = MEM_ROTATE,                          /**< Rotate memory */
    MEMORY_DIFFERENT_IMAGE_BASE_OK = MEM_DIFFERENT_IMAGE_BASE_OK, /**< Different image base OK */
    MEMORY_RESET_UNDO = MEM_RESET_UNDO,                  /**< Undo reset */
    MEMORY_LARGE_PAGES = MEM_LARGE_PAGES,                /**< Large pages */
    MEMORY_4MB_PAGES = MEM_4MB_PAGES,                    /**< 4MB pages */
    MEMORY_64K_PAGES = MEM_64K_PAGES,                    /**< 64K pages */
    MEMORY_UNMAP_WITH_TRANSIENT_BOOST = MEM_UNMAP_WITH_TRANSIENT_BOOST, /**< Unmap with boost */
    MEMORY_COALESCE_PLACEHOLDERS = MEM_COALESCE_PLACEHOLDERS,          /**< Coalesce placeholders */
    MEMORY_PRESERVE_PLACEHOLDER = MEM_PRESERVE_PLACEHOLDER,            /**< Preserve placeholder */
    MEMORY_DECOMMIT = MEM_DECOMMIT,                      /**< Decommit memory */
    MEMORY_RELEASE = MEM_RELEASE,                        /**< Release memory */
    MEMORY_FREE = MEM_FREE                               /**< Free memory */
} MemAllocFreeType_t;

#endif

#ifndef NDEBUG
#if defined(ENABLE_TESTING_LOG_OUT)
#include <stdio.h>
/**
 * @def DEBUG_LOG
 * @brief Debug logging macro for testing.
 */
#define DEBUG_LOG(__format, ...) printf(__format, __VA_ARGS__)
#else
#define DEBUG_LOG(...)
#endif
#else
#define DEBUG_LOG(...)
#endif

#if OS_LINUX || OS_MAC
/**
 * @def MEMORY_INIT
 * @brief Attribute for memory initialization (POSIX).
 */
#define MEMORY_INIT __attribute__((constructor))
/**
 * @def MEMORY_DESTRUCTOR
 * @brief Attribute for memory destruction (POSIX).
 */
#define MEMORY_DESTRUCTOR __attribute__((destructor))
#else
#define MEMORY_INIT
#define MEMORY_DESTRUCTOR
#endif

/**
 * @typedef func_lock
 * @brief Function pointer type for locking a kernel mutex.
 */
typedef void(MEMORY_CALL* func_lock)(void);

/**
 * @typedef func_unlock
 * @brief Function pointer type for unlocking a kernel mutex.
 */
typedef void(MEMORY_CALL* func_unlock)(void);

/**
 * @enum PageSpace
 * @brief Page size categories for memory management.
 */
typedef enum PageSpace
{
    MEMORY_SPACE_SMALL = 8,      /**< Small page size */
    MEMORY_SPACE_MEDIUM = 64,    /**< Medium page size */
    MEMORY_SPACE_LARGE = 128,    /**< Large page size */
    MEMORY_SPACE_HUGE = 512      /**< Huge page size */
} PageSpace_t;

/** @def MEMORY_HUGE_PAGES_COUNT
 *  @brief Number of huge pages.
 */
/** @def MEMORY_LARGE_PAGES_COUNT
 *  @brief Number of large pages.
 */
/** @def MEMORY_MEDIUM_PAGES_COUNT
 *  @brief Number of medium pages.
 */
/** @def MEMORY_SMALL_PAGES_COUNT
 *  @brief Number of small pages.
 */
#define MEMORY_HUGE_PAGES_COUNT 256
#define MEMORY_LARGE_PAGES_COUNT 512
#define MEMORY_MEDIUM_PAGES_COUNT 1024
#define MEMORY_SMALL_PAGES_COUNT 2048

struct LinkedList;
struct ComprassedPair;

/**
 * @def MEMORY_HUGE_PAGE_SPACE
 * @brief Total space for huge pages.
 */

#define MEMORY_HUGE_PAGE_SPACE MEMORY_HUGE_PAGES_COUNT*(MEMORY_SPACE_HUGE + sizeof(struct LinkedList))

/**
 * @def MEMORY_LARGE_PAGE_SPACE
 * @brief Total space for large pages.
 */
#define MEMORY_LARGE_PAGE_SPACE MEMORY_LARGE_PAGES_COUNT*(MEMORY_SPACE_LARGE + sizeof(struct LinkedList))

/**
 * @def MEMORY_MEDIUM_PAGE_SPACE
 * @brief Total space for medium pages.
 */
#define MEMORY_MEDIUM_PAGE_SPACE MEMORY_MEDIUM_PAGES_COUNT*(MEMORY_SPACE_MEDIUM + sizeof(struct LinkedList))

/**
 * @def MEMORY_SMALL_PAGE_SPACE
 * @brief Total space for small pages.
 */
#define MEMORY_SMALL_PAGE_SPACE MEMORY_SMALL_PAGES_COUNT*(MEMORY_SPACE_SMALL + sizeof(struct LinkedList))

/**
 * @def MEMORY_DEFAULT_SPACE
 * @brief Default total memory space.
 */
#define MEMORY_DEFAULT_SPACE \
    MEMORY_SMALL_PAGE_SPACE + MEMORY_MEDIUM_PAGE_SPACE + MEMORY_LARGE_PAGE_SPACE + MEMORY_HUGE_PAGE_SPACE

/**
 * @struct Allocator
 * @brief Structure holding function pointers for memory allocation, protection, and deallocation.
 */
typedef struct Allocator
{
    func_allocate allocate;  /**< Allocation function */
    func_protect protect;    /**< Protection function */
    func_deallocate deallocate; /**< Deallocation function */
} Allocator_t;

/**
 * @struct KernelMutex
 * @brief Structure holding function pointers for locking and unlocking a kernel mutex.
 */
typedef struct KernelMutex
{
    func_lock lock;      /**< Lock function */
    func_unlock unlock;  /**< Unlock function */
} KernelMutex_t;

/**
 * @struct Area
 * @brief Memory area structure containing allocator, mutex, and root node.
 */
typedef struct Area
{
    Allocator_t allocator;                /**< Allocator functions */
    KernelMutex_t kernelMutex;            /**< Kernel mutex functions */
    struct ComprassedPair* root;          /**< Root of the memory area */
    mem_size_t isInited;                  /**< Initialization flag */
} Area_t;

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief Get the global memory arena.
 * @return Pointer to the global Area_t structure.
 */
MEMORY_API Area_t* MEMORY_CALL __getArena();

/**
 * @brief Overcommit a specified number of bytes in the memory arena.
 * @param bytes Number of bytes to overcommit.
 */
MEMORY_API void MEMORY_CALL __overCommit(mem_size_t bytes);

#if defined(__cplusplus)
}
#endif
