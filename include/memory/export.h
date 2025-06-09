#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define OS_WIN 1
#define OS_LINUX 0
#define OS_MAC 0
#elif defined(__linux__)
#define OS_WIN 0
#define OS_LINUX 1
#define OS_MAC 0
#elif defined(__APPLE__)
#define OS_WIN 0
#define OS_LINUX 0
#define OS_MAC 1
#else
#error "Unsupported operating system"
#endif

#if defined(__GNUC__)
#define COMPILER_GCC 1
#define COMPILER_CLANG 0
#define COMPILER_MSVC 0
#elif defined(__clang__)
#define COMPILER_GCC 0
#define COMPILER_CLANG 1
#define COMPILER_MSVC 0
#elif defined(_MSC_VER)
#define COMPILER_GCC 0
#define COMPILER_CLANG 0
#define COMPILER_MSVC 1
#else
#error "Unsupported compiler"
#endif

#if !defined(MEMORY_API)
#if OS_WIN
#define MEMORY_API __declspec(dllexport)
#elif OS_LINUX || OS_MAC
#define MEMORY_API __attribute__((__visibility__("default")))
#endif
#else
#if OS_WIN
#define MEMORY_API __declspec(dllimport)
#elif OS_LINUX || OS_MAC
#define MEMORY_API __attribute__((__visibility__("default")))
#endif
#endif

#if OS_WIN
#define MEMORY_NODISCARD
#define MEMORY_ALLOC __declspec(allocator)
#define MEMORY_CHECK_SIZE(...)
#define MEMORY_CALL __stdcall
#else
#define MEMORY_CALL
#define MEMORY_ALLOC __attribute__((malloc))
#define MEMORY_NODISCARD __attribute__((warn_unused_result))
#define MEMORY_CHECK_SIZE(...) __attribute__((alloc_size(__VA_ARGS__)))
#endif

#if !COMPILER_MSVC
#if __has_builtin(__builtin_expect)
#define MEMORY_LIKELY(__condition) __builtin_expect(((__condition)), 1)
#else
#define MEMORY_LIKELY(__condition) (__condition)
#endif
#else
#define MEMORY_LIKELY(__condition) (__condition)
#endif

#if !COMPILER_MSVC
#if __has_builtin(__builtin_expect)
#define MEMORY_UNLIKY(__condition) __builtin_expect(((__condition)), 0)
#else
#define MEMORY_UNLIKY(__condition) (__condition)
#endif
#else
#define MEMORY_UNLIKY(__condition) (__condition)
#endif

#if !defined(MEMORY_UNUSED)
#define MEMORY_UNUSED(__x) (void)__x
#endif

#define __PREFIX li
#define __MACHINE_IMPL(__prefix, __name) __prefix##__name
#define MACHINE_IMPL(__prefix, __name) __MACHINE_IMPL(__prefix, __name)
#define MACHINE(__name) MACHINE_IMPL(__PREFIX, __name)
#define MACHINE_PREFIX_IMPL(__prefix, __name) MACHINE_IMPL(__prefix, __name)
#define MACHINE_PREFIX(__prefix, __name) MACHINE_PREFIX_IMPL(__prefix, MACHINE(__name))
#define MACHINE_MEMORY_IMPL(__name) MACHINE_PREFIX(__, __name##_impl)
