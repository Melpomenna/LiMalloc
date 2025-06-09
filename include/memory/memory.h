/**
 * @file memory.h
 * @brief Memory management API for custom allocation, deallocation, and memory utilities.
 *
 * This header provides a set of memory management functions and macros for allocation,
 * deallocation, and memory utilities. It supports custom memory hooks, defragmentation,
 * and aligned allocation. The API is designed to be used in both C and C++ environments.
 *
 * Macros are provided to redirect standard memory functions (malloc, calloc, realloc, free, etc.)
 * to their custom implementations. C++ operator new/delete overloads are optionally provided
 * when DISABLED is defined.
 *
 * @note All functions are exported with MEMORY_API and may use custom attributes for allocation
 *       and size checking.
 */

#pragma once

#include <memory/export.h>
#include <memory/type.h>

#if defined(__cplusplus)
#include <stdexcept>
extern "C" {
#endif

/**
 * @brief Allocates a block of memory of the specified size.
 * @param bytes Number of bytes to allocate.
 * @return Pointer to the allocated memory, or nullptr on failure.
 */
MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(malloc)(mem_size_t bytes) MEMORY_NODISCARD MEMORY_CHECK_SIZE(1);

/**
 * @brief Allocates memory for an array of elements and initializes them to zero.
 * @param count Number of elements.
 * @param size Size of each element in bytes.
 * @return Pointer to the allocated memory, or nullptr on failure.
 */
MEMORY_API mem_ptr_t MACHINE(calloc)(mem_size_t count, mem_size_t size) MEMORY_NODISCARD MEMORY_CHECK_SIZE(1, 2);

/**
 * @brief Changes the size of the memory block pointed to by ptr.
 * @param ptr Pointer to the previously allocated memory block.
 * @param bytes New size in bytes.
 * @return Pointer to the reallocated memory, or nullptr on failure.
 */
MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(realloc)(mem_ptr_t ptr, mem_size_t bytes) MEMORY_NODISCARD MEMORY_CHECK_SIZE(2);

/**
 * @brief Allocates a block of memory with the specified alignment.
 * @param alignment Alignment in bytes.
 * @param bytes Number of bytes to allocate.
 * @return Pointer to the allocated memory, or nullptr on failure.
 */
MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(aligned_alloc)(mem_size_t alignment, mem_size_t bytes) MEMORY_NODISCARD MEMORY_CHECK_SIZE(1, 2);

/**
 * @brief Allocates a block of memory using the onlyfree allocator.
 * @param bytes Number of bytes to allocate.
 * @return Pointer to the allocated memory, or nullptr on failure.
 */
MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(malloc_onlyfree)(mem_size_t bytes) MEMORY_NODISCARD MEMORY_CHECK_SIZE(1);

/**
 * @brief Allocates zero-initialized memory for an array using the onlyfree allocator.
 * @param count Number of elements.
 * @param size Size of each element in bytes.
 * @return Pointer to the allocated memory, or nullptr on failure.
 */
MEMORY_API mem_ptr_t MACHINE(calloc_onlyfree)(mem_size_t count, mem_size_t size) MEMORY_NODISCARD MEMORY_CHECK_SIZE(1, 2);

/**
 * @brief Changes the size of the memory block using the onlyfree allocator.
 * @param ptr Pointer to the previously allocated memory block.
 * @param bytes New size in bytes.
 * @return Pointer to the reallocated memory, or nullptr on failure.
 */
MEMORY_API MEMORY_ALLOC mem_ptr_t MACHINE(realloc_onlyfree)(mem_ptr_t ptr, mem_size_t bytes) MEMORY_NODISCARD MEMORY_CHECK_SIZE(2);

/**
 * @brief Frees a previously allocated memory block.
 * @param ptr Pointer to the memory block to free.
 */
MEMORY_API void MACHINE(free)(mem_ptr_t ptr);

/**
 * @brief Frees a memory block allocated with the onlyfree allocator.
 * @param ptr Pointer to the memory block to free.
 */
MEMORY_API void MACHINE(free_onlyfree)(mem_ptr_t ptr);

/**
 * @brief Performs memory defragmentation.
 */
MEMORY_API void MACHINE(defragmentation)(void);

/**
 * @brief Installs memory hooks for custom allocation tracking.
 */
MEMORY_API void MACHINE(hook)(void);

/**
 * @brief Removes memory hooks.
 */
MEMORY_API void MACHINE(unhook)(void);

#if defined(__cplusplus)
}
#endif

#if defined(DISABLED)
#if defined(__cplusplus)
/**
 * @brief Overloads operator new to use custom memory allocation.
 * @param bytes Number of bytes to allocate.
 * @throws std::bad_alloc if allocation fails.
 */
[[nodiscard]] void* operator new(std::size_t bytes);

/**
 * @brief Overloads operator new[] to use custom memory allocation.
 * @param bytes Number of bytes to allocate.
 * @throws std::bad_alloc if allocation fails.
 */
[[nodiscard]] void* operator new[](std::size_t bytes);

/**
 * @brief Overloads operator delete to use custom memory deallocation.
 * @param ptr Pointer to the memory block to free.
 */
void operator delete(void* ptr) noexcept;

/**
 * @brief Overloads operator delete[] to use custom memory deallocation.
 * @param ptr Pointer to the memory block to free.
 */
void operator delete[](void* ptr) noexcept;

#endif
#endif

// Undefine standard memory function macros if already defined
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

/**
 * @def malloc(bytes)
 * @brief Macro to use the custom malloc implementation.
 */
#define malloc(bytes) MACHINE(malloc)(bytes)

/**
 * @def calloc(count, size)
 * @brief Macro to use the custom calloc implementation.
 */
#define calloc(count, size) MACHINE(calloc)(count, size)

/**
 * @def realloc(ptr, bytes)
 * @brief Macro to use the custom realloc implementation.
 */
#define realloc(ptr, bytes) MACHINE(realloc)(ptr, bytes)

/**
 * @def free(ptr)
 * @brief Macro to use the custom free implementation.
 */
#define free(ptr) MACHINE(free)(ptr)

/**
 * @def aligned_alloc(alignment, bytes)
 * @brief Macro to use the custom aligned_alloc implementation.
 */
#define aligned_alloc(alignment, bytes) MACHINE(aligned_alloc)(alignment, bytes)

/**
 * @def malloc_onlyfree(bytes)
 * @brief Macro to use the custom malloc_onlyfree implementation.
 */
#define malloc_onlyfree(bytes) MACHINE(malloc_onlyfree)(bytes)

/**
 * @def calloc_onlyfree(count, size)
 * @brief Macro to use the custom calloc_onlyfree implementation.
 */
#define calloc_onlyfree(count, size) MACHINE(calloc_onlyfree)(count, size)

/**
 * @def realloc_onlyfree(ptr, bytes)
 * @brief Macro to use the custom realloc_onlyfree implementation.
 */
#define realloc_onlyfree(ptr, bytes) MACHINE(realloc_onlyfree)(ptr, bytes)

/**
 * @def defragmentation()
 * @brief Macro to use the custom defragmentation implementation.
 */
#define defragmentation() MACHINE(defragmentation)()
