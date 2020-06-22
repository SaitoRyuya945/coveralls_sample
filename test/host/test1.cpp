#include "gtest/gtest.h"
#include <ctime>
#include <numeric>
extern "C" {
#include "mymath.h"
}

TEST(GooleTest, test1)
{ 
    int a;
    a = mysum(SAMPLE, 2);
    EXPECT_EQ(12, a);
}

TEST(GooleTest, test_name)
{
    enum Status status = UPDATE;
    EXPECT_EQ(UPDATE, status);
}
