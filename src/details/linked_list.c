#include <memory/export.h>
#if COMPILER_MSVC
#pragma warning(disable : 4245 6326 4081 26439 26495)
#endif

#include <memory/__details/linked_list.h>

LinkedList_t* createNode(void* ptr, int space)
{
    if (MEMORY_UNLIKY(!ptr || space <= 0))
        return 0;
    LinkedList_t* node = (LinkedList_t*)ptr;
    node->isFree = 1;
    node->next = 0;
    node->back = 0;
    node->space = space;
    return node;
}

void addNode(ComprassedPair_t* root, LinkedList_t* node)
{
    if (MEMORY_UNLIKY(!root || !node))
        return;
    if (MEMORY_UNLIKY(root->begin == 0 && root->end == 0))
    {
        root->begin = node;
        root->end = node;
    }
    else
    {
        LinkedList_t* end = root->end;
        end->next = node;
        node->back = end;
        root->end = node;
    }
}

void addFront(ComprassedPair_t* root, LinkedList_t* node)
{
    if (MEMORY_UNLIKY(!root || !node))
        return;
    if (MEMORY_UNLIKY(root->begin == 0 || root->end == 0))
    {
        root->begin = node;
        root->end = node;
    }
    else
    {
        LinkedList_t* begin = root->begin;
        begin->back = node;
        node->next = begin;
        root->begin = node;
    }
}

void removeNode(ComprassedPair_t* root, LinkedList_t* node)
{
    if (MEMORY_UNLIKY(!root || !node || !root->begin || !root->end))
        return;
    if (node == root->begin)
    {
        root->begin = node->next;
        if (root->begin)
        {
            root->begin->back = 0;
        }
        else
        {
            root->end = 0;
        }
    }
    else if (node == root->end)
    {
        root->end = node->back;
        if (root->end)
        {
            root->end->next = 0;
        }
        else
        {
            root->begin = 0;
        }
    }
    else
    {
        node->back->next = node->next;
        if (node->next)
        {
            node->next->back = node->back;
        }
    }
}

LinkedList_t* mergeNode(ComprassedPair_t* root, LinkedList_t* first, LinkedList_t* second)
{
    if (MEMORY_UNLIKY(!root || !first || !second || (first->next != second) ||
                      (first == root->begin && second == root->end) ||
                      ((char*)first + first->space + sizeof(LinkedList_t) != (char*)second)))
        return 0;
    int totalSpace = first->space + second->space + sizeof(LinkedList_t);
    first->space = totalSpace;
    removeNode(root, second);
    return first;
}


void insertAfter(ComprassedPair_t* root, LinkedList_t* it, LinkedList_t* node)
{
    if (MEMORY_UNLIKY(!root || !node || !it))
        return;
    if (MEMORY_UNLIKY(root->begin == 0 && root->end == 0))
    {
        root->begin = node;
        root->end = node;
        return;
    }

    LinkedList_t* next = it->next;
    node->back = it;
    node->next = next;
    next->back = node;
    it->next = node;
}
