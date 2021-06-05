#include <iostream>
#include "../../include/log.h"

using namespace std;

int64_t get_current_millis(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (int64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main()
{
    LOG_INIT("log", "test", 3);
    uint64_t start_ts = get_current_millis();
    for (int i = 0; i < 1e6; ++i)
    {
        LOG_ERROR("this test is no.%d", i);
    }
    uint64_t end_ts = get_current_millis();
    printf("time use %lus\n", end_ts - start_ts);
    return 0;
}