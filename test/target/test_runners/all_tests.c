#include "unity.h"
#include "unity_fixture.h"

void Uart0_send(char data);

static void RunAllTests(void)
{
    RUN_TEST_GROUP(test1_sample);
}

int main(int argc, const char *argv[])
{
    UnityMain(argc, argv, RunAllTests);
}

void Uart0_send(char data)
{
    return;
}

void (*outputChar)(char) = Uart0_send;
