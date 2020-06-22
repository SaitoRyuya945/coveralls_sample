#define RUN_TEST(TestFunc, TestLineNum) \
{ \
    Unity.CurrentTestName = #TestFunc; \
    Unity.CurrentTestLineNumber = TestLineNum; \
    Unity.NumberOfTests++; \
    if (TEST_PROTECT()) \
    { \
        setUp(); \
        TestFunc(); \
    } \
    if (TEST_PROTECT()) \
    { \
        tearDown(); \
    } \
    UnityConcludeTest(); \
}

#include "unity/unity.h"

extern void setUp(void);
extern void tearDown(void);
extern void test_sample1(void);

void resetTest(void);
void resetTest(void) {
    tearDown();
    setUp();
}

int main(void)
{
    UnityBegin("test/test1.c");
    RUN_TEST(test_sample1, 20);
    return (UnityEnd());
}
