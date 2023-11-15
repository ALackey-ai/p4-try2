#include <lab.h>
#include <gtest/gtest.h>

// Delete this test before submitting
TEST(VersionTest, PositiveNos)
{
    char *version = fooVersion();
    ASSERT_STREQ("0.1", version);
    free(version);
}

// Delete this test before submitting
TEST(AddTest, PositiveNos)
{
    int actual = add(1, 1);
    int expected = 2;
    ASSERT_EQ(expected, actual);
}

// Delete this test before submitting
TEST(SegFaultTest, asan)
{
    ASSERT_DEATH(segfault(), ".*");
}

// This tests are disabled because they will fail they are used to make sure
// that the sanitizer is working correctly. You can run them with the
// --gtest_also_run_disabled_tests flag
// ./out/build/x64-ASan/test-lab --gtest_filter=DISABLED_OutOfBoundsTest.fail --gtest_also_run_disabled_tests
// ./out/build/x64-ASan/test-lab --gtest_filter=DISABLED_LeakTest.fail --gtest_also_run_disabled_tests
// Delete this test before submitting
TEST(DISABLED_OutOfBoundsTest, fail)
{
    outOfBounds();
}
// Delete this test before submitting
TEST(DISABLED_LeakTest, fail)
{
    int *actual = leak(2);
    ASSERT_EQ(2, *actual);
    free(actual);
}

// Delete this test before submitting
TEST(DISABLED_TimeoutTest, fail)
{
    while (true)
    {
    }
}
