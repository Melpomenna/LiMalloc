#pragma once

/**
 * @file type.h
 * @brief Defines memory-related type aliases for the memory module.
 */

/**
 * @typedef mem_size_t
 * @brief Unsigned integer type for representing memory sizes.
 *
 * This type is used to specify the size of memory blocks in bytes.
 */
typedef unsigned long long mem_size_t;

/**
 * @typedef mem_ptr_t
 * @brief Generic pointer type for memory operations.
 *
 * This type is used to represent a pointer to a memory block.
 */
typedef void* mem_ptr_t;
