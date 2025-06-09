#pragma once

#include <memory/export.h>
#include <memory/type.h>

typedef struct LinkedList
{
    struct LinkedList* next;
    struct LinkedList* back;
    int space;
    int isFree;
} LinkedList_t;

typedef struct ComprassedPair
{
    LinkedList_t* begin;
    LinkedList_t* end;
    mem_size_t freeSpace;
} ComprassedPair_t;

#if defined(__cplusplus)
extern "C" {
#endif

MEMORY_NODISCARD MEMORY_API LinkedList_t* MEMORY_CALL  createNode(void* ptr, int space);
MEMORY_API void MEMORY_CALL addNode(ComprassedPair_t* root, LinkedList_t* node);
MEMORY_API void MEMORY_CALL addFront(ComprassedPair_t* root, LinkedList_t* node);
MEMORY_API void MEMORY_CALL removeNode(ComprassedPair_t* root, LinkedList_t* node);
MEMORY_NODISCARD MEMORY_API LinkedList_t* MEMORY_CALL mergeNode(ComprassedPair_t* root, LinkedList_t* first, LinkedList_t* second);

#if defined(__cplusplus)
}
#endif
