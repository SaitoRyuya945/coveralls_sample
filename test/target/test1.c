#include "unity_fixture.h"

TEST_GROUP(test1_sample);

TEST_SETUP(test1_sample)
{
}

TEST_TEAR_DOWN(test1_sample)
{
}

TEST(test1_sample, test1_test)
{
    TEST_ASSERT_EQUAL(0, 1);
}
