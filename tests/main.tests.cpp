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


TEST_F(MallocTest, MallocAllocate100BytesPassed)
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

TEST_F(MallocTest, MallocAllocate0BytesPassed)
{
    int* ptr = (int*)malloc(0);
    ASSERT_TRUE(ptr == nullptr);
}

TEST_F(MallocTest, MallocAllocateNegativeBytesPassed)
{
    int* ptr = (int*)malloc(-1);
    ASSERT_TRUE(ptr == nullptr);
}

TEST_F(MallocTest, MallocAllocateMaxBytesPassed)
{
    int* ptr = (int*)malloc(SIZE_MAX);
    ASSERT_TRUE(ptr == nullptr);
}

TEST_F(MallocTest, MallocAllocateInThread)
{
    auto threadFunc = []() {
        int* ptr = (int*)malloc(100);
        ASSERT_TRUE(ptr != nullptr);
        for (int i = 0; i < 25; ++i)
        {
            ptr[i] = i;
        }
        for (int i = 0; i < 25; ++i)
        {
            ASSERT_EQ(ptr[i], i);
        }
        free(ptr);
    };
    
    std::thread worker(threadFunc);
    std::thread worker2(threadFunc);
    worker.join();
    worker2.join();
}


TEST_F(MallocTest, MallocAllocateLarge10KBytes)
{
    size_t largeSize = 1024 * 10; // 10 KB
    int* ptr = (int*)malloc(largeSize);
    ASSERT_TRUE(ptr != nullptr);
    for (size_t i = 0; i < largeSize / sizeof(int); ++i)
    {
        ptr[i] = i;
    }
    for (size_t i = 0; i < largeSize / sizeof(int); ++i)
    {
        ASSERT_EQ(ptr[i], i);
    }
    free(ptr);
}


TEST_F(MallocTest, MallocAllocateSmallBytesNotAlignedBy8Bytes)
{
    constexpr int arrSize = 10;
    size_t smallSize = 19; // ~2 bytes
    int* ptr = (int*)malloc(smallSize * arrSize);
    ASSERT_TRUE(ptr != nullptr);
    for (size_t i = 0; i < arrSize; ++i)
    {
        ptr[i] = i;
    }
    for (size_t i = 0; i < arrSize; ++i)
    {
        ASSERT_EQ(ptr[i], i);
    }
    free(ptr);
}
