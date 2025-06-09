/**
 * @file linked_list.h
 * @brief Internal linked list structures and functions for memory management.
 *
 * This header defines the data structures and function prototypes used for managing
 * a doubly-linked list of memory blocks, as well as operations for manipulating
 * these lists. It is intended for internal use within the memory management module.
 */

#pragma once

#include <memory/export.h>
#include <memory/type.h>

/**
 * @struct LinkedList
 * @brief Node structure for a doubly-linked list representing memory blocks.
 *
 * Each node represents a block of memory, with pointers to the next and previous nodes,
 * the size of the memory block, and a flag indicating if the block is free.
 */
typedef struct LinkedList
{
    struct LinkedList* next; /**< Pointer to the next node in the list. */
    struct LinkedList* back; /**< Pointer to the previous node in the list. */
    int space;               /**< Size of the memory block. */
    int isFree;              /**< Flag indicating if the block is free (non-zero if free). */
} LinkedList_t;

/**
 * @struct ComprassedPair
 * @brief Structure representing a pair of pointers to the beginning and end of a linked list,
 *        along with the total free space.
 */
typedef struct ComprassedPair
{
    LinkedList_t* begin;     /**< Pointer to the first node in the list. */
    LinkedList_t* end;       /**< Pointer to the last node in the list. */
    mem_size_t freeSpace;    /**< Total free space in the list. */
} ComprassedPair_t;

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief Creates a new linked list node.
 * @param ptr Pointer to the memory block.
 * @param space Size of the memory block.
 * @return Pointer to the newly created LinkedList_t node.
 */
MEMORY_NODISCARD MEMORY_API LinkedList_t* MEMORY_CALL  createNode(void* ptr, int space);

/**
 * @brief Adds a node to the end of the linked list.
 * @param root Pointer to the ComprassedPair_t representing the list.
 * @param node Pointer to the LinkedList_t node to add.
 */
MEMORY_API void MEMORY_CALL addNode(ComprassedPair_t* root, LinkedList_t* node);

/**
 * @brief Adds a node to the front of the linked list.
 * @param root Pointer to the ComprassedPair_t representing the list.
 * @param node Pointer to the LinkedList_t node to add.
 */
MEMORY_API void MEMORY_CALL addFront(ComprassedPair_t* root, LinkedList_t* node);

/**
 * @brief Removes a node from the linked list.
 * @param root Pointer to the ComprassedPair_t representing the list.
 * @param node Pointer to the LinkedList_t node to remove.
 */
MEMORY_API void MEMORY_CALL removeNode(ComprassedPair_t* root, LinkedList_t* node);

/**
 * @brief Merges two adjacent nodes in the linked list.
 * @param root Pointer to the ComprassedPair_t representing the list.
 * @param first Pointer to the first LinkedList_t node.
 * @param second Pointer to the second LinkedList_t node.
 * @return Pointer to the merged LinkedList_t node.
 */
MEMORY_NODISCARD MEMORY_API LinkedList_t* MEMORY_CALL mergeNode(ComprassedPair_t* root, LinkedList_t* first, LinkedList_t* second);

#if defined(__cplusplus)
}
#endif
