#include <memory/__details/linked_list.h>
#if COMPILER_MSVC
#pragma warning(disable : 4245 6326 4081 26439 26495)
#endif

#include <gtest/gtest.h>

class LinkedListTest : public ::testing::Test
{
public:
    LinkedListTest() = default;
    ~LinkedListTest() override = default;
};


TEST_F(LinkedListTest, InsertItems10)
{
    constexpr int count = 10;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, 200);
        addNode(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, 200);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    free(mem);
}

TEST_F(LinkedListTest, InsertItems100)
{
    constexpr int count = 100;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, 200);
        addNode(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, 200);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    free(mem);
}

TEST_F(LinkedListTest, InsertItems1000)
{
    constexpr int count = 1000;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, 200);
        addNode(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, 200);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    free(mem);
}

TEST_F(LinkedListTest, InsertItemsFront50)
{
    constexpr int count = 50;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, i);
        addFront(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    int needly = count - 1;
    while (begin)
    {
        ASSERT_EQ(begin->space, needly--);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    free(mem);
}

TEST_F(LinkedListTest, InsertItemsFront100)
{
    constexpr int count = 100;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, i);
        addFront(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    int needly = count - 1;
    while (begin)
    {
        ASSERT_EQ(begin->space, needly--);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    free(mem);
}

TEST_F(LinkedListTest, InsertItemsFront1000)
{
    constexpr int count = 1000;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, i);
        addFront(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    int needly = count - 1;
    while (begin)
    {
        ASSERT_EQ(begin->space, needly--);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    free(mem);
}

TEST_F(LinkedListTest, RemoveItemsFromBegin1000)
{
    constexpr int count = 1000;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, 200);
        addNode(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, 200);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, 200);
        ASSERT_TRUE(begin != nullptr);
        removeNode(&root, begin);
        begin = begin->next;
    }

    ASSERT_TRUE(root.begin == 0);
    ASSERT_TRUE(root.end == 0);

    free(mem);
}

TEST_F(LinkedListTest, RemoveItemsFromEnd1000)
{
    constexpr int count = 1000;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, 200);
        addNode(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, 200);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    while (root.begin)
    {
        removeNode(&root, root.end);
    }

    ASSERT_TRUE(root.begin == 0);
    ASSERT_TRUE(root.end == 0);

    free(mem);
}

TEST_F(LinkedListTest, RemoveItemsFromCenter1000)
{
    constexpr int count = 1000;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, 200);
        addNode(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, 200);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    int tmp = 0;
    begin = root.begin;
    while (tmp < count / 2)
    {
        ++tmp;
        begin = begin->next;
    }

    removeNode(&root, begin);

    int totalCount = 0;
    begin = root.begin;
    while (begin)
    {
        begin = begin->next;
        ++totalCount;
    }

    ASSERT_EQ(totalCount, count - 1);

    free(mem);
}

TEST_F(LinkedListTest, MergeAllItems1000TotalSize500FailedTest)
{
    constexpr int count = 1000;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc(sizeof(LinkedList_t) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, 200);
        addNode(&root, node);
        ptr += sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, 200);
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    begin = root.begin;
    while (begin)
    {
        LinkedList_t* res = mergeNode(&root, begin, begin->next);
        ASSERT_TRUE(res == nullptr);
        begin = begin->next;
    }

    free(mem);
}

TEST_F(LinkedListTest, MergeAllItems1000TotalSizeByStructAccpetMerge)
{
    constexpr int count = 1000;
    ComprassedPair_t root = {};
    root.begin = 0;
    root.end = 0;
    void* mem = malloc((sizeof(LinkedList_t) + sizeof(LinkedList_t)) * count);
    char* ptr = (char*)mem;
    for (int i = 0; i < count; ++i)
    {
        LinkedList_t* node = createNode(ptr, sizeof(LinkedList_t));
        addNode(&root, node);
        ptr += sizeof(LinkedList_t) + sizeof(LinkedList_t);
    }

    LinkedList_t* begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, sizeof(LinkedList_t));
        ASSERT_TRUE(begin != nullptr);
        begin = begin->next;
    }

    begin = root.begin;
    while (begin && begin->next)
    {
        LinkedList_t* unused = mergeNode(&root, begin, begin->next);
        ASSERT_TRUE(unused != nullptr);
        MEMORY_UNUSED(unused);
        begin = begin->next;
    }

    int totalCount = 0;
    begin = root.begin;
    while (begin)
    {
        ASSERT_EQ(begin->space, sizeof(LinkedList_t) * 2 + sizeof(LinkedList_t));
        begin = begin->next;
        ++totalCount;
    }

    ASSERT_EQ(totalCount, count / 2);

    free(mem);
}
