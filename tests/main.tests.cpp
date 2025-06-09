#include <gtest/gtest.h>
#include <memory/__details/internal.h>
#include <memory/memory.h>
class MallocTest : public ::testing::Test
{
public:
};

TEST_F(MallocTest, InitTestInitLibraryAreaFromSegment)
{
    [[maybe_unused]] Area_t* area = __getArena();
    ASSERT_TRUE(area->allocator.allocate != nullptr);
    ASSERT_TRUE(area->allocator.deallocate != nullptr);
    ASSERT_TRUE(area->allocator.protect != nullptr);
}


TEST_F(MallocTest, MallocAllocate100Bytes)
{
    int* ptr = (int*)malloc(100);
    int count = 100 / sizeof(int);
    ASSERT_TRUE(ptr != nullptr);
    for (int i = 0; i < count; ++i)
    {
        ptr[i] = i;
    }
    for (int i = 0; i < count; ++i)
    {
        ASSERT_EQ(ptr[i], i);
    }
    free(ptr);
}