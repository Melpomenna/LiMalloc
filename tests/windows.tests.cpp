#include <memory/export.h>
#pragma warning(disable : 4245 6326 4081 26439 26495)

#include <gtest/gtest.h>
#include <memory/__details/internal.h>

class WindowsMallocTest : public ::testing::Test
{
public:
};


TEST_F(WindowsMallocTest, InitTestAreaAllocateFunctionTest)
{
    [[maybe_unused]] Area_t* area = __getArena();
    ASSERT_TRUE(area->allocator.allocate != nullptr);
    void* ptr = area->allocator.allocate(0, 1024, MEMORY_COMMIT | MEMORY_RESERVE, MEMORY_PAGE_READ_WRITE);
    ASSERT_TRUE(ptr != nullptr);
    area->allocator.deallocate(ptr, 1024, MEMORY_RELEASE);
}
