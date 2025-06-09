#include <gtest/gtest.h>
#include <memory/__details/internal.h>

class UnixMallocTest : public ::testing::Test
{
public:
};


TEST_F(UnixMallocTest, InitTestAreaAllocateFunctionTest)
{
    [[maybe_unused]] Area_t* area = __getArena();
    ASSERT_TRUE(area->allocator.allocate != nullptr);
    void* ptr = area->allocator.allocate(0, 1024, MEMORY_PAGE_READ | MEMORY_PAGE_WRITE, MEMORY_MAP_SHARED, 0, 0);
    ASSERT_TRUE(ptr != nullptr);
    area->allocator.deallocate(ptr, 1024);
}
